/**
 * @file periodic_table.h
 * @brief This file contains declarations for handling periodic table elements, including loading, sorting, and searching for elements.
 */

#ifndef PERIODIC_TABLE_H
#define PERIODIC_TABLE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Represents a chemical element with its symbol and atomic number.
 */
typedef struct
{
    char symbol[4];   // The chemical symbol of the element.
    int atomicNumber; // The atomic number of the element.
} ELEMENT;

/**
 * @brief Loads the periodic table from a file into an array of ELEMENT structs.
 *
 * @param elements An array of ELEMENT structs where the loaded elements will be stored.
 * @param numElements A pointer to an integer where the number of loaded elements will be stored.
 * @param filename The path to the file containing periodic table data.
 */
void loadPeriodicTable(ELEMENT elements[], int *numElements, const char *filename);

/**
 * @brief Finds the atomic number of a given element symbol in the periodic table.
 *
 * @param element The symbol of the element to search for.
 * @param elements An array of ELEMENT structs representing the periodic table.
 * @param numElements The number of elements in the array.
 * @return int The atomic number of the element if found, 0 if the element is not found.
 */
int findAtomicNumber(char *element, ELEMENT elements[], int numElements);

#endif // PERIODIC_TABLE_H
