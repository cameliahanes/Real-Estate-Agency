#pragma once

#include "Offer.h"
#include "DynamicArray.h"
#include <string.h>

typedef struct
{
	Offer* offer;
	char* operationType;
} Operation;

Operation* createOperation(Offer* o, char* operationType);
void destroyOperation(Operation* o);
Operation* copyOperation(Operation* o);
char* getOperationType(Operation* o);
Offer* getOffer(Operation* o);

// ---------------------------------------------------------------
typedef struct
{
	Operation* operations[100];
	int length;
} OperationsStack;

OperationsStack* createStack();
void destroyStack(OperationsStack* s);
void push(OperationsStack* s, Operation* o);
Operation* pop(OperationsStack* s);
int isEmpty(OperationsStack* s);
int isFull(OperationsStack* s);
