#pragma once

typedef struct {
	char* type;
	char* address;
	int price;
	double surface;
} Offer;

Offer* createOffer(char* type, char* address, double surface, int price);
void destroyOffer(Offer* o); //the memory is freed

Offer* copyOffer(Offer* o);
char* getType(Offer* o);
char* getAddress(Offer* o);
int getPrice(Offer* o);
double getSurface(Offer* o);


void toString(Offer* o, char str[]);
