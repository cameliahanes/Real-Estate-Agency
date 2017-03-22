#include "OperationsStack.h"
#include <string.h>
#include <stdlib.h>
#include <assert.h>


Operation* createOperation(Offer* o, char* operationType)
{
	Operation* op = (Operation*)malloc(sizeof(Operation));
	op->offer = copyOffer(o);

	if (operationType != NULL)
	{
		op->operationType = (char*)malloc(strlen(operationType) +1);
		strcpy(op->operationType, operationType);
	}
	else
		op->operationType = NULL;

	return op;
}

void destroyOperation(Operation* o)
{
	if (o == NULL)
		return;

	// first destroy the planet
	destroyOffer(o->offer);
	// then the operationType
	//	free(o->operationType);
	// then free the operation
	free(o);
}

Operation* copyOperation(Operation * o)
{
	if (o == NULL)
		return NULL;

	Operation* newOp = createOperation(copyOffer(o->offer), o->operationType);
	return newOp;
}

char* getOperationType(Operation* o)
{
	return o->operationType;
}

Offer* getOffer(Operation* o)
{
	return o->offer;
}

// ---------------------------------------------------------------

OperationsStack* createStack()
{
	OperationsStack* s = (OperationsStack*)malloc(sizeof(OperationsStack));
	s->length = 0;

	return s;
}

void destroyStack(OperationsStack* s)
{
	if (s == NULL)
		return;

	// first deallocate memory of operations (this is allocated when a new operation is pushed onto the stack)
	for (int i = 0; i < s->length; i++)
		destroyOperation(s->operations[i]);

	// then free the stack
	free(s);
}

void push(OperationsStack* s, Operation* o)
{
	if (isFull(s))
		return;
	Operation* op = copyOperation(o);
	s->operations[s->length++] = op;	// copies of operations are added, such that the stask manages its own operations
}

Operation* pop(OperationsStack* s)
{
	if (isEmpty(s))
		return NULL;
	s->length--;
	return s->operations[s->length];
}

int isEmpty(OperationsStack* s)
{
	return (s->length == 0);
}

int isFull(OperationsStack* s)
{
	if (s->length == 100) return 1;
	return 0;
}


