/**
 * @file formula_parser.h
 * @brief This file contains function declarations for parsing chemical formulas, counting protons, and validating parentheses.
 */

#ifndef FORMULA_PARSER_H
#define FORMULA_PARSER_H

#include "periodic_table.h"
#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

/**
 * @brief Parses the chemical formulas from the input file and writes the expanded format to the output file.
 * 
 * @param inputFile The path to the input file containing chemical formulas.
 * @param outputFile The path to the output file where the expanded formulas will be written.
 */
void parseFormula(const char* inputFile, const char* outputFile);

/**
 * @brief Counts the total number of protons in the chemical formulas from the input file and writes the result to the output file.
 * 
 * @param elements An array of ELEMENT structs representing the periodic table elements.
 * @param numElements The total number of elements in the array.
 * @param inputFile The path to the input file containing chemical formulas.
 * @param outputFile The path to the output file where the proton count results will be written.
 */
void countProtons(ELEMENT elements[], int numElements, const char* inputFile, const char* outputFile);

/**
 * @brief Validates the parentheses in the chemical formulas from the input file.
 * 
 * @param inputFile The path to the input file containing chemical formulas.
 * @return int Returns the number of lines with invalid parentheses. 0 indicates all lines are valid.
 */
int parenthesesValidation(const char* inputFile);

#endif // FORMULA_PARSER_H
