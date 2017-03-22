#pragma once
#include "Offer.h"
#define CAPACITY 10

typedef Offer* TElement;

typedef struct {
	TElement* elems;
	int length; //actual length of the array
	int capacity; ///maximum capacity of the array
} DynamicArray;

/// <summary>
/// Creates a dynamic array of generic elements, with a given capacity.
/// </summary>
/// <param name="capacity">Integer, maximum capacity for the dynamic array.</param>
/// <returns>A pointer the the created dynamic array.</returns>
DynamicArray* createDynamicArray(int capacity);

/// <summary>
/// Destroys the dynamic array.
/// </summary>
/// <param name="arr">The dynamic array to be destoyed.</param>
/// <returns>A pointer the the created dynamic array.</returns>
void destroy(DynamicArray* arr);

/// <summary>
/// Adds a generic element to the dynamic array.
/// </summary>
/// <param name="arr">The dynamic array.</param>
/// <param name="p">The planet to be added.</param>
void add2(DynamicArray* arr, TElement t);

/// <summary>
/// Deletes an element from a given position in the dynamic array.
/// </summary>
/// <param name="arr">The dynamic array.</param>
/// <param name="pos">The position from which the element must be deleted. The position must be valid.</param>
void delete2(DynamicArray* arr, int pos);

void update2(DynamicArray* arr, int pos, TElement t);

/// <summary>
/// Returns the length of the dynamic array.
/// </summary>
/// <param name="arr">The dynamic array.</param>
int getLength2(DynamicArray* arr);

/// <summary>
/// Returns the element on a given position.
/// </summary>
/// <param name="arr">The dynamic array.</param>
/// <param name="pos">The position - must be a valid position.</param>
/// <returns>The element on the given position.</returns>
TElement get(DynamicArray* arr, int pos);

void testDynamicArray();

