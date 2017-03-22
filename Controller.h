#pragma once

#include "Repository.h"
#include "OperationsStack.h"
typedef struct {
	OfferRepository* repository;

	OperationsStack* undoStack;
	OperationsStack* redoStack;

} Controller;
Controller* createController(OfferRepository* p);

Controller* createController2(OfferRepository* p, OperationsStack* undos, OperationsStack* redos);
void destroyController(Controller* c);

///<summary>
/// adds a new offer to the repository of offers
///</summary>
///<param name = "c" > The controller to be modified </param>
///<param name = "address "> The address of the new real estate </param>
///<param name = "type"> The type of the real estate </param>
///<param name = "surface"> The surface of the real estate </param>
///<param name = "price"> The price of the real estate </param>

int addOffer(Controller* c, char* type, char* address, double surface, int price);

///deletes an offer by the given address
int deleteOffer(Controller* c, char* address);

///updates an offer with the given address and the price

int updateOfferPrice(Controller* c, char* address, int price);

OfferRepository* getRepo(Controller* c);

/// <summary>
/// searches for the offers containing a given particularity
///</summary>
/// <param name = "c" > pointer to the controller </param>
/// <param name = "particularity">
/// <returns> A pointer to the repository of offers that hav the given symbol </returns>

OfferRepository* filterByAddressContents(Controller* c, char particularity[]);

///returns the repository object type containing offers with surface greater than the given value
OfferRepository* surfaceGreater(Controller* c, double surface, int type);

///returns a repository which contains all offers with prices in the given interval
OfferRepository* filterByPrices(Controller* c, int price1, int price2);

//return a repository which contains all the entries having the price less than the given value and the given type
//OfferRepository* class_work(Controller* c, int price, int type);

int undo(Controller* c);
int redo(Controller* c);
