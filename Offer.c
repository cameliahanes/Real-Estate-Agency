#include "Offer.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

Offer* createOffer(char* type, char* address, double surface, int price) {
	Offer* o = (Offer*)malloc(sizeof(Offer));
	o->type = (char*)malloc(strlen(type)*sizeof(char)+1);
	strcpy(o->type,type);
	o->address = (char*)malloc(strlen(address)*sizeof(char)+1);
	strcpy(o->address, address);
	o->surface = surface;
	o->price = price;
	return o;
}

void destroyOffer(Offer* o) {
	//free the memory which was allocated for the elements existent in
	//the created data structure
	//free(o->address);
	//free(o->price);
	//free(o->type);
	//free(o->surface);
	//free the memory allocated for the data structure
	free(o);
}

Offer* copyOffer(Offer* o) {
	if (o == NULL) return NULL;
	Offer* newOffer = createOffer(getType(o), getAddress(o), getSurface(o), getPrice(o));
	return newOffer;
}


char* getType(Offer* o) {
	return o->type;
}

char* getAddress(Offer* o) {
	return o->address;
}

int getPrice(Offer* o) {
	return o->price;
}

double getSurface(Offer* o) {
	return o->surface;
}

void toString(Offer* o, char str[]) {
	sprintf(str, "Real estate: \n TYPE: %s, ADDRESS: %s, SURFACE: %.f., PRICE: %d.\n", o->type, o->address, o->surface, o->price);
}


