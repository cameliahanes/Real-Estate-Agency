#include "DynamicArray.h"
#include <stdlib.h>
#include <assert.h>

DynamicArray* createDynamicArray(int capacity) {
	DynamicArray* da = (DynamicArray*)malloc(sizeof(DynamicArray));
	//make sure the space was allocated
	if (da == NULL) return NULL;

	da->capacity = capacity;
	da->length = 0;

	//allocate space for the elements
	da->elems = (TElement*)malloc(capacity * sizeof(TElement));
	if (da->elems == NULL)
		return NULL;
	return da;
}

void destroy(DynamicArray* arr) {
	if (arr == NULL) {
		return;
	}
	//free the space allocated for the elements first
	free(arr->elems);
	//now free the space allocated for the dynamic array
	free(arr);
	arr = NULL;
}
//resize the array
void resize(DynamicArray* arr) {
	if (arr == NULL) {
		return;
	}
	arr->capacity *= 2;
	arr->elems = (TElement*)realloc(arr->elems, arr->capacity * sizeof(TElement));
}

void add2(DynamicArray* arr, TElement t) {
	if (arr == NULL) return;
	if (arr->elems == NULL) return;
	//resize the array if necessary
	if (arr->length == arr->capacity)
		resize(arr);
	//arr->length = arr->length + 1;
	arr->elems[arr->length++] = t;
	
}

void update2(DynamicArray* arr, int pos, TElement t) {
	if (arr == NULL) return;
	if (arr->elems == NULL) return;
	arr->elems[pos] = t;
}

void delete2(DynamicArray* arr, int pos) {
	if (arr == NULL) return;
	if (arr->elems == NULL) return;
	for (int i = pos; i < arr->length - 1; i++)
		arr->elems[i] = arr->elems[i + 1];
	arr->length--;
}

int getLength2(DynamicArray* arr) {
	if (arr == NULL) return -1;
	return arr->length;
}

TElement get(DynamicArray* arr, int pos) {
	return arr->elems[pos];
}



///------------------------------------tests-----------------------

void testDynamicArray()
{
	DynamicArray* da = createDynamicArray(2);
	if (da == NULL)
		assert(0);

	assert(da->capacity == 2);
	assert(da->length == 0);

	Offer* p1 = createOffer("house", "Gallifrey", 123.5, 25000);
	add2(da, p1);
	assert(da->length == 1);

	Offer* p2 = createOffer("house", "Mjdhs", 723.5, 95000);
	add2(da, p2);
	assert(da->length == 2);

	// capacity must double
	Offer* p3 = createOffer("house", "Garey,12", 103.5, 2000);
	add2(da, p3);
	
	assert(da->length == 3);
	assert(da->capacity == 4);

	// delete planet on position 0
	delete2(da, 0);
	Offer* p = get(da, 0);
	assert((int)strcmp(getAddress(p), "Mjdhs") == 0);
	assert(da->length == 2);

	// destroy the dynamic array
	destroy(da);

	// destroy the planets
	destroyOffer(p1);
	destroyOffer(p2);
	destroyOffer(p3);
}


