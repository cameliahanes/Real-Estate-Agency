/*
* Repository.c
*
*  Created on: 12 mar. 2017
*      Author: Camelia
*/

#include "Repository.h"
#include <stddef.h>
#include <string.h>
#include <assert.h>
#include "DynamicArray.h"


OfferRepository* createRepository() {
	OfferRepository* p = (OfferRepository*)malloc(sizeof(OfferRepository));
	p->offers = createDynamicArray(CAPACITY);
	return p;
}

void destroyRepository(OfferRepository* p) {
	//first destroy all the offers from the repository
	if (p == NULL) return;
	for (int i = 0; i < getLength2(p->offers); ++i) {
		Offer* o = get(p->offers, i);
		destroyOffer(o);
	}
	destroy(p->offers);
	free(p);
}

int findPositionOfOffer(OfferRepository* p, char* address) {
	if (p == NULL) {
		return -1;
	}
	for (int i = 0; i < getLength2(p->offers); ++i) {
		Offer* o = get(p->offers, i);
		if (strcmp(o->address, address) == 0) {
			return i;
		}
	}
	return -1;
}

Offer* find(OfferRepository* p, char* address) {
	if (p == NULL) return NULL;
	int pos = findPositionOfOffer(p, address);
	if (pos == -1) return NULL;
	return get(p->offers, pos);
	return NULL;
}

int add(OfferRepository* p, Offer* o) {
	//use the function to search for an offer with the given
	//data as the offer
	if (p == NULL) return 0;
	if (find(p, o->address) != NULL) return 0;
	//a copy of the offer which was passed will be stored, such that the memory
	//allocated for it can be deallocated
	Offer* copy = copyOffer(o);
	add2(p->offers, copy);
	
	return 1;
}

int updatePrice(OfferRepository* p, char* address, int newPrice) {
	if (p == NULL) return 0;
	int pos = findPositionOfOffer(p, address);
	if (pos == -1) return 0;
	Offer* res = copyOffer(find(p, address));
	update2(p->offers, pos, res);
	return 1;
}

int delete_(OfferRepository* p, char* address) {
	//use the function to search for a given offer which has the
	//given address as parameter and deletes it if it exists
	if (p == NULL) return 0;
	//find the position of the offer in the repository
	int pos = findPositionOfOffer(p, address);
	if (pos == -1) return 0;
	Offer* o = get(p->offers, pos);
	destroyOffer(o);
	delete2(p->offers, pos);
	return 1;
}

int getLength(OfferRepository* p) {
	if (p == NULL) return -1;
	return getLength2(p->offers);
}

Offer* getOfferAtIndex(OfferRepository* p, int index) {
	if (p == NULL) return NULL;
	//if (index < 0 || index >= getLength2(p->offers)) return NULL;
	return get(p->offers, index);
}


//tests
void initializeOfferRepoForTesting(OfferRepository* p) {
	Offer* o = createOffer("house", "dunarii19 a", 151.6, 1200);
	int i = add(p, o);
}

void testAdd() {
	OfferRepository* p = createRepository();
	initializeOfferRepoForTesting(p);
	assert(getLength(p) == 1);
	Offer* o = createOffer("penthouse", "riviera, 10", 120, 9000);
	assert(add(p, o) == 1);
	assert(getLength(p) == 2);
	//try to add at the same address
	//try for the same offer
	assert(add(p, o) == 0);
	//destroy the test repository
	destroyRepository(p);
}

void testOfferRepository() {
	testAdd();
}
