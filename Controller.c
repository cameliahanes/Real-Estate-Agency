/*
* Controller.c
*
*  Created on: 12 mar. 2017
*      Author: Camelia
*/

#include "Controller.h"
#include <string.h>
#include <stdlib.h>
#include <assert.h>

Controller* createController(OfferRepository* p) {
	Controller* c = (Controller*)malloc(sizeof(Controller));
	c->repository = p;
	return c;
}



Controller* createController2(OfferRepository* p, OperationsStack* undos, OperationsStack* redos) {
	Controller* c = (Controller*)malloc(sizeof(Controller));
	c->repository = p;
	c->undoStack = undos;
	c->redoStack = redos;
	return c;
}


void destroyController(Controller* c) {
	//first estroy the repository
	destroyRepository(c->repository);
	//then free the memory
	free(c);
}

void destroyController2(Controller* c) {
	//first estroy the repository
	destroyRepository(c->repository);
	//destroy the stack
	destroyStack(c->undoStack);
	//then free the memory
	destroyStack(c->redoStack);
	free(c);
}



int addOffer(Controller* c, char* type, char* address, double surface, int price) {
	Offer* o = createOffer(type, address, surface, price);
	int result = add(c->repository, o);

	if (result == 1) {
		//if the offer was successfully added
		Operation* op = createOperation(o, "add");
		push(c->undoStack, op);
		//once added the operation can be deleted because a copy of
		//operation was acctually added
		destroyOperation(op);
	}
	//destroy the offer that was added because the repository stored it
	destroyOffer(o);
	return result;
}



int updateOfferPrice(Controller* c, char* address, int price) {
	Offer* aux = find(c->repository, address);
	int result = updatePrice(c->repository, address, price);

	if (result == 1) {
		//if the oofer was successfully added
		Operation* op = createOperation(aux, "update");
		push(c->undoStack, op);
		destroyOffer(aux);
		//once added the operation can be deleted because a copy of
		//operation was acctually added
		destroyOperation(op);
	}


	return result;
}

int deleteOffer(Controller* c, char* address) {
	Offer* aux = find(c->repository, address);

	int result = delete_(c->repository, address);

	if (result == 1) {
		//if the oofer was successfully added
		Operation* op = createOperation(aux, "delete");
		push(c->undoStack, op);
		destroyOffer(aux);
		//once added the operation can be deleted because a copy of
		//operation was acctually added
		destroyOperation(op);
	}
	//destroy the planet that was added because the repository stored it


	return result;
}

int undo(Controller* c) {
	if (isEmpty(c->undoStack)) return 0;
	Operation* operation = pop(c->undoStack);
	Operation* aux = copyOperation(operation);
	push(c->redoStack, aux);
	if (strcmp(getOperationType(operation), "add") == 0) {
		Offer* offer = getOffer(operation);
		char* address = (char*)malloc(strlen(getAddress(offer)) + 1);
		strcpy(address, getAddress(offer));
		delete_(c->repository, address);
	}
	else if (strcmp(getOperationType(operation), "update") == 0) {
		Offer* offer = getOffer(operation);
		char* address = (char*)malloc(strlen(getAddress(offer))+1);
		int price;
		strcpy(address, getAddress(offer));
		updatePrice(c->repository, address, price);
	}
	else if (strcmp(getOperationType(operation), "delete") == 0) {
		Offer* offer = getOffer(operation);
		char* address;
		strcpy(address, getAddress(offer));
		add(c->repository, offer);
	}
	destroyOperation(operation);
	destroyOperation(aux);
	return 1;
}

int redo(Controller* c) {
	if (isEmpty(c->redoStack)) return 0;
	Operation* operation = pop(c->redoStack);
	Operation* aux = copyOperation(operation);
	push(c->undoStack, aux);
	if (strcmp(getOperationType(operation), "add") == 0) {
		Offer* offer = getOffer(operation);
		char* address = (char*)malloc(strlen(getAddress(offer)) + 1);
		strcpy(address, getAddress(offer));
		add(c->repository, offer);
	}
	else if (strcmp(getOperationType(operation), "update") == 0) {
		Offer* offer = getOffer(operation);
		char* address = (char*)malloc(strlen(getAddress(offer)) + 1);
		int price = offer->price;
		strcpy(address, getAddress(offer));
		updatePrice(c->repository, address, price);
	}
	else if (strcmp(getOperationType(operation), "delete") == 0) {
		Offer* offer = getOffer(operation);
		char* address = (char*)malloc(strlen(getAddress(offer)) + 1);
		strcpy(address, getAddress(offer));
		delete_(c, address);
	}
	destroyOperation(operation);
	destroyOperation(aux);
	return 1;
}



/*
sorting function for sorting the displayable list
returns the sorted repository list
*/

OfferRepository* bubbleSort(OfferRepository* repo) {
	int ok = 0;
	do {
		ok = 1;
		for (int i = 0; i < getLength2(repo->offers) - 1; ++i) {
			if (get(repo->offers, i)->price > get(repo->offers, i+1)->price) {
				ok = 0;
				TElement *aux1 = get(repo->offers, i);
				TElement *aux2 = get(repo->offers, i+1);
				update2(repo->offers, i, aux2);
				update2(repo->offers, i + 1, aux1);
			}
		}
	} while (ok == 0);
	return repo;
}

OfferRepository* filterByAddressContents(Controller* c, char particularity[]) {
	OfferRepository* result = createRepository();
	if (strcmp(particularity, "null") == 0) {
		return bubbleSort(c->repository);
	}
	for (int i = 0; i < getLength(c->repository); ++i) {
		Offer* o = getOfferAtIndex(c->repository, i);
		if (strstr(getAddress(o), particularity) != NULL) {
			Offer* newOffer = createOffer(o->type, o->address, o->surface, o->price);
			add(result, newOffer);
		}
	}
	return bubbleSort(result);
}

OfferRepository* filterByPrices(Controller* c, int price1, int price2) {
	OfferRepository* result = createRepository();
	for (int i = 0; i < getLength(c->repository); ++i) {
		Offer* o = getOfferAtIndex(c->repository, i);
		if (o->price >= price1 && o->price <= price2) {
			Offer* newOffer = createOffer(o->type, o->address, o->surface, o->price);
			add(result, newOffer);
		}
	}
	return bubbleSort(result);
}

char* returnType(int i) {
	switch (i) {
	case 0: {
		return "house";
		break; }
	case 1: {
		return "penthouse";
		break;
	} case 2: {
		return "appartment";
		break;
	}
	}
}

OfferRepository* surfaceGreater(Controller* c, double surface, int type) {
	char* tt;
	if (type == 1) tt = "house";
	else if (type == 2) tt = "penthouse";
	else tt = "appartment";
	int length = getLength(c->repository);
	OfferRepository* result = createRepository();
	for (int i = 0; i < length; ++i) {
		Offer* o = getOfferAtIndex(c->repository, i);
		if (o->surface > surface && strcmp(o->type, tt) == 0) {
			Offer* newOffer = createOffer(o->type, o->address, o->surface, o->price);
			add(result, newOffer);
		}
	}
	return bubbleSort(result);
}

/*
function to return the repository containing only filtered entries
*/

OfferRepository* class_work(Controller* c, int price, int type) {
	char* tt;
	if (type == 1) tt = "house";
	else if (type == 2) tt = "penthouse";
	else tt = "appartment";
	int length = getLength(c->repository);
	OfferRepository* result = createRepository();
	for (int i = 0; i < length; ++i) {
		Offer* o = getOfferAtIndex(c->repository, i);
		if (o->price < price && strcmp(o->type, tt) == 0) {
			Offer* newOffer = createOffer(o->type, o->address, o->surface, o->price);
			add(result, newOffer);
		}
	}
	return bubbleSort(result);
}


OfferRepository* getRepo(Controller* c) {
	return c->repository;
}


void test_class_work() {
	OfferRepository* repository = createRepository();
	Controller* controller = createController(repository);
	assert(getLength(controller->repository) == 0);
	addOffer(controller, "house", "Dunarii,19A", 125.8, 2000);
	addOffer(controller, "penthouse", "IntreLacuri", 100.9, 10000);
	addOffer(controller, "appartment", "Dunarii,11B", 70.5, 1000);
	addOffer(controller, "penthouse", "Dunarii,99H", 345.8, 12600);
	addOffer(controller, "appartment", "Riviera,11", 70.6, 5000);
	addOffer(controller, "appartment", "IntreLacuri,8", 100.1, 1980);
	addOffer(controller, "house", "Harghitei,17C", 185.8, 2099);
	addOffer(controller, "house", "Dorobantilor,8HH", 208.123456, 2010);
	addOffer(controller, "appartment", "Crailor,89/1", 120.7, 1030);
	addOffer(controller, "penthouse", "Lacuri,6789", 170.8945, 3456);
	addOffer(controller, "penthouse", "Arabic,70", 200, 6700);
	OfferRepository* rep = class_work(controller, 10000, 1); //price 10000 type penthouse
	assert(getLength(rep) == 3);
	destroyController(controller);
}

void test_surface_greater() {
	OfferRepository* repository = createRepository();
	Controller* controller = createController(repository);
	assert(getLength(controller->repository) == 0);
	addOffer(controller, "house", "Dunarii,19A", 125.8, 2000);
	addOffer(controller, "penthouse", "IntreLacuri", 100.9, 10000);
	addOffer(controller, "appartment", "Dunarii,11B", 70.5, 1000);
	addOffer(controller, "penthouse", "Dunarii,99H", 345.8, 12600);
	addOffer(controller, "appartment", "Riviera,11", 70.6, 5000);
	addOffer(controller, "appartment", "IntreLacuri,8", 100.1, 1980);
	addOffer(controller, "house", "Harghitei,17C", 185.8, 2099);
	addOffer(controller, "house", "Dorobantilor,8HH", 208.123456, 2010);
	addOffer(controller, "appartment", "Crailor,89/1", 120.7, 1030);
	addOffer(controller, "penthouse", "Lacuri,6789", 170.8945, 3456);
	addOffer(controller, "penthouse", "Arabic,70", 200, 6700);
	OfferRepository* rep = surfaceGreater(controller, 100, 1); //price 10000 type penthouse
	assert(getLength(rep) == 3);
	destroyController(controller);
}

void test_delete_offer() {
	OfferRepository* repository = createRepository();
	Controller* controller = createController(repository);
	assert(getLength(controller->repository) == 0);
	addOffer(controller, "house", "Dunarii,19A", 125.8, 2000);
	addOffer(controller, "penthouse", "IntreLacuri", 100.9, 10000);
	addOffer(controller, "appartment", "Dunarii,11B", 70.5, 1000);
	addOffer(controller, "penthouse", "Dunarii,99H", 345.8, 12600);
	addOffer(controller, "appartment", "Riviera,11", 70.6, 5000);
	addOffer(controller, "appartment", "IntreLacuri,8", 100.1, 1980);
	addOffer(controller, "house", "Harghitei,17C", 185.8, 2099);
	addOffer(controller, "house", "Dorobantilor,8HH", 208.123456, 2010);
	addOffer(controller, "appartment", "Crailor,89/1", 120.7, 1030);
	addOffer(controller, "penthouse", "Lacuri,6789", 170.8945, 3456);
	addOffer(controller, "penthouse", "Arabic,70", 200, 6700);
	assert(getLength(controller->repository) == 11);
	assert(deleteOffer(controller, "Dunarii,19A") == 1);
	assert(getLength(controller->repository) == 10);
	destroyController(controller);
}

void test_filter_by_prices() {
	OfferRepository* repository = createRepository();
	Controller* controller = createController(repository);
	assert(getLength(controller->repository) == 0);
	addOffer(controller, "house", "Dunarii,19A", 125.8, 2000);
	addOffer(controller, "penthouse", "IntreLacuri", 100.9, 10000);
	addOffer(controller, "appartment", "Dunarii,11B", 70.5, 1000);
	addOffer(controller, "penthouse", "Dunarii,99H", 345.8, 12600);
	addOffer(controller, "appartment", "Riviera,11", 70.6, 5000);
	addOffer(controller, "appartment", "IntreLacuri,8", 100.1, 1980);
	addOffer(controller, "house", "Harghitei,17C", 185.8, 2099);
	addOffer(controller, "house", "Dorobantilor,8HH", 208.123456, 2010);
	addOffer(controller, "appartment", "Crailor,89/1", 120.7, 1030);
	addOffer(controller, "penthouse", "Lacuri,6789", 170.8945, 3456);
	addOffer(controller, "penthouse", "Arabic,70", 200, 6700);
	assert(getLength(controller->repository) == 11);
	assert(addOffer(controller, "house", "Dunarii,19A", 125.8, 2000) == 0);
	assert(getLength(controller->repository) == 11);
	int i = addOffer(controller, "house", "TeodorMihali", 600.98, 20000);
	assert(i == 1);
	assert(getLength(controller->repository) == 12);
	destroyController(controller);

}

void test_controller() {
	//test_class_work();
	test_surface_greater();
	test_delete_offer();
}