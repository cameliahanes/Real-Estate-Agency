/*
* UI.c
*
*  Created on: 12 mar. 2017
*      Author: Camelia
*/

#include "UI.h"
#include <stdio.h>
#include <string.h>

UI* createUI(Controller* c) {
	UI* ui = (UI*)malloc(sizeof(UI));
	ui->controller = c;
	return ui;
}

void destroyUI(UI* ui) {
	//first destroy the controller
	destroyController(ui->controller);
	//then free the memory
	free(ui);
}

/*
print the available menu options
*/

void printMenu() {
	printf("\n\n");
	printf("1 - add a new offer \n");
	printf("2 - update an existing offer \n");
	printf("3 - delete an existing offer \n");
	printf("4 - display offers which have an address particularity \n");
	printf("5 - display all offers of a given type which have the surface greater than a value \n");
	printf("6 - display all offers which have the price between two limits\n");
	printf("7 - list all offers \n");
	printf("8 - undo the last changes made on the database\n");
	printf("9 - redo the last changes made on the database\n");
	printf("0 - exit \n\n");
}

/*
function to check the validity of a command
returns 1 if the command is vali and 0 otherwise
*/
int validCommand(int command) {
	if (command < 0 || command > 10)
		return 0;
	return 1;
}


/*
reads an integer number from the keyboard, asks for number while errors are encountered
input : the message to be displayed while asking the user for input
returns the number
*/
int readIntegerNumber(const char* message) {
	char s[16];
	int res = 0;
	int flag = 0;
	int r = 0;

	while (flag == 0) {
		printf(message);
		scanf("%s", s);
		r = sscanf(s, "%d", &res);
		//reads the data from s and stores it in res if possible
		//returns 1 if successfull
		flag = (r == 1);
		if (flag == 0) {
			printf("Error reading integer number! \n");
		}
		return res;
	}

}


/*
searches for a string in the given list of enums
returns 1/0 if there exists the type or not
*/

char* getEstateType(int i) {
	if (i == 0) {
		return "house";
	}
	if (i == 1) return "penthouse";
	if (i == 2) return "appartment";
}

int is_in_list(char* type) {
	for (int i = 0; i < 3; ++i) {
		if (strcmp(getEstateType(i), type) == 0)
			return 1;
	}
	return 0;
}

int addOfferUI(UI* ui) {
	//read the data for the offer
	char type[50], address[100];
	double surface;
	int price;
	int opt;
	printf("Enter the type of the real-estate: \n1-house\n2-penthouse\n3-appartment \n\n ");
	scanf("%d", &opt);
	if (opt < 1 || opt > 3) {
		printf("Invalid real estate type!\n");
		return 0;
	}
	if (opt == 1) { strcpy(type,"house"); }
	else if (opt == 2) { strcpy(type,"penthouse"); }
	else { strcpy(type,"penthouse"); }
	printf("Enter the address: ");
	scanf("%100s", address);
	printf("Give the price: ");
	scanf("%d", &price);
	printf("Enter the surface: ");
	scanf("%lf", &surface);
	return addOffer(ui->controller, "pp", address, surface, price);
}

int updateOfferPriceUI(UI* ui) {
	int newPrice;
	char address[50];
	printf("Give the address of the real estate to be updated ");
	scanf("%50s", address);
	printf("Give the new price: ");
	scanf("%d", &newPrice);
	return updateOfferPrice(ui->controller, address, newPrice);
}

int deleteOfferUI(UI* ui) {
	char address[50];
	printf("Give the address of the real-estate: ");
	scanf("%50s", address);
	if (strlen(address) == 0) {
		printf("No address provided, can't delete! \n");
		return 0;
	}
	printf("address :   %s", address);
	return deleteOffer(ui->controller, address);
}

void listAllOffers(UI* ui) {
	OfferRepository* repository = getRepo(ui->controller);
	int length = getLength(repository);
	if (length == 0) {
		char* str = "There are no offers.";
		printf("%s \n", str);
	}
	for (int i = 0; i < length; ++i) {
		char str[300];
		toString(getOfferAtIndex(repository, i), str);
		printf("%s\n", str);
	}
}

void listOffersWithParticularity(UI* ui) {
	char addr[30];
	printf("Enter the sequence in the address: ");
	scanf("%s", addr);

	OfferRepository* res = filterByAddressContents(ui->controller, addr);
	int length = getLength(res);
	if (length == 0)
		printf("No offers with that address particularity.\n");
	else {
		for (int i = 0; i < length; ++i) {
			char str[200];
			toString(getOfferAtIndex(res, i), str);
			printf("%s\n", str);
		}
	}
	//now destroy the created repository
	destroyRepository(res);
}

void priceBetween(UI* ui) {
	int price1, price2;
	printf("Enter the lower price bound: ");
	scanf("%d", &price1);
	printf("\nEnter the upper bound price: ");
	scanf("%d", &price2);
	OfferRepository* res = filterByPrices(ui->controller, price1, price2);
	int length = getLength(res);
	if (length == 0)
		printf("No offers with that address particularity.\n");
	else {
		for (int i = 0; i < length; ++i) {
			char str[200];
			toString(getOfferAtIndex(res, i), str);
			printf("%s\n", str);
		}
	}
	//now destroy the created repository
	destroyRepository(res);
}

/*
int undoUI(UI* ui) {
int result = undo(ui->controller);
return result;
}

int redoUI(UI* ui) {
int result = redo(ui->controller);
return result;
}
*/

void surfaceGreaterUI(UI* ui) {
	printf("Enter the code for the type:\n 1-house \n 2-penthouse \n 3-appartment \n\n");
	int type;
	scanf("%d", &type);
	printf("Enter the surface limit : ");
	int surface;
	scanf("%d", &surface);

	int display_type;
	printf("Choose display type: \n1 - ascending by price \n2 - descending by price \n===default ascending===\n\n");
	scanf("%d", &display_type);

	OfferRepository* result = surfaceGreater(ui->controller, surface, type);
	int length = getLength(result);
	if (length == 0) {
		printf("There are no offers with surface greater than the given value. \n\n");
		return;
	}
	if (display_type == 2) {
		for (int i = length - 1; i >= 0; --i) {
			char str[200];
			toString(getOfferAtIndex(result, i), str);
			printf("%s\n", str);
		}
		return;
	}
	for (int i = 0; i < length; ++i) {
		char str[200];
		toString(getOfferAtIndex(result, i), str);
		printf("%s\n", str);
	}
}

void startUI(UI* ui) {
	while (1) {
		printMenu();
		int command = readIntegerNumber("Input command: ");
		while (validCommand(command) == 0) {
			printf("Invalid command! Try again :) \n");
			command = readIntegerNumber("Input command: ");
		}
		if (command == 0) break;
		switch (command) {
		case 1: {
			int ress = addOfferUI(ui);
			if (ress == 1) { printf("Offer successfully added! \n");  break; }
			else printf("There is another real estate at the given address, could not add the offer! \n");
			break;
		} case 2: {
			int res2 = updateOfferPriceUI(ui);
			if (res2 == 1) { printf("Offer successfully updated! \n"); break; }
			else printf("The offer could not be updated! \n");
			break;
		} case 3: {
			int res = deleteOfferUI(ui);
			if (res == 1) { printf("Offer successfully deleted! \n");  break; }
			else printf("Could not delete offer! \n");
			break;
		} case 7: {
			listAllOffers(ui); break;
		} case 4: {
			listOffersWithParticularity(ui); break;
		} case 5: {
			surfaceGreaterUI(ui); break;
		} case 6: {
			priceBetween(ui); break;
		} case 8: {
			if (undo(ui->controller) == 0) {
			printf("Unsuccessfull undo operation, already at first state! \n\n");
			}
			else {
			printf("Successfully executed undo operation! \n\n");
			}
			break;
		} case 9: {
			
			if (redo(ui->controller) == 0) {
			printf("Unsuccessfull redo operation, already at latest state! \n\n");
			}
			else {
			printf("Successfully executed redo operation! \n\n");
			}
			break;

		} case 10: {
			//implement the work to do during the lab
			//class_workUI(ui);
			break;
		}

		}

	}
}



