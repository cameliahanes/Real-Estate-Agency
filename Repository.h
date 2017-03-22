/*
* Repository.h
*
*  Created on: 12 mar. 2017
*      Author: Camelia
*/

#pragma once
#include "Offer.h"
#include "DynamicArray.h"

typedef struct {
	DynamicArray* offers;
} OfferRepository;

/// <summary>
/// creates a repository for offers
/// </summary>

OfferRepository* createRepository();

/// <sumary>
/// Destroys the given offer reporitory, frees the memory
/// </summary>

void destroyRepository(OfferRepository* p);

///<summary>
/// Finds th offer with the given address
/// </summary>
/// <param name = "p">pointer to the offer repository </param>
/// <param name = "address" > a string containing the address of the RE </param>
/// <returns> the pointer to the offer having the given address or null if it does not exist </returns>

Offer* find(OfferRepository* p, char* address);

/*
Adds an offer to the reposiroty of offers
Input: the repository and the new offer
Output: 1/0 - the offer was successfully added/not
*/

int findPositionOfOffer(OfferRepository* p, char* address);

int add(OfferRepository* p, Offer* o);

/* deletes an offer with the given address
returns 1/0 regarding the success of the performed execution
*/

int delete_(OfferRepository* p, char* address);
/*
updates the offer price
*/
int updatePrice(OfferRepository* p, char* address, int newPrice);


int getLength(OfferRepository* p);

Offer* getOfferAtIndex(OfferRepository* p, int index);

void testOfferRepository();
