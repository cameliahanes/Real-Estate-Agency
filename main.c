/*
* main.c
*
*  Created on: 12 mar. 2017
*      Author: Camelia
*/

/// THIS IS THE GOOD VERSION


#include "Repository.h"
#include "UI.h"
#include "DynamicArray.h"
//#include <crtdbg.h>

int main() {
	//testOfferRepository();
	//test_controller();

	testDynamicArray();

	OfferRepository* repository = createRepository();
	OperationsStack* undoStack = createStack();
	OperationsStack* redoStack = createStack();
	Controller* controller = createController2(repository, undoStack, redoStack);
	
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
	

	UI* ui = createUI(controller);
	startUI(ui);
	destroyUI(ui);
	//_CrtDumpMemoryLeaks();
	return 0;
}


