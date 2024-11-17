/**
 * @file parseFormula.c
 * 
 * @brief Entry point for the chemical formula parser console application.
 * 
 * This file processes command-line arguments to perform one of three operations:
 * expanding formulas, validating parentheses, or calculating proton counts. The program 
 * checks the argument structure and validates the command provided, then proceeds with 
 * the appropriate operation. It supports three commands:
 * 
 * - **-ext**: Expands formulas in the input file and writes the extended format to an output file.
 * - **-v**: Verifies that all parentheses in the formulas are balanced.
 * - **-pn**: Calculates the total proton count for each formula using atomic data from a 
 *   periodic table file, then writes the results to an output file.
 * 
 * The function ensures correct usage through error checking and manages memory allocation
 * when loading periodic table data for the proton count operation.
 *
 *
 *
 * @author Spyros Gavriil
 * @since 30/10/2024
 * @bug No known bugs.
 */

#include "formula_parser.h"
#include "periodic_table.h"

int main(int argc, char *argv[]) {

    char *periodicTableFile;
    char *command;
    char *inputFile;
    char *outputFile;

    // Check the number of arguments and assign files/commands
    if (argc == 4) {
        periodicTableFile = argv[1];
        command = argv[2];
        inputFile = argv[3];
        outputFile = NULL;  // No output file for verification command
        if(strcmp(command, "-v") != 0) { printf("Only allowed -p with these arguments!\n"); exit(EXIT_FAILURE); } // Check for right command
    } else if (argc == 5) {
        periodicTableFile = argv[1];
        command = argv[2];
        inputFile = argv[3];
        outputFile = argv[4];
        if(strcmp(command, "-v") == 0) { printf("Only allowed -ext and -pn with these arguments!\n"); exit(EXIT_FAILURE); } // Check for right commands
    } else {
        printf("Usage: %s <periodic_table_file> -cmd <input_file> <output_file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Compare command argument to determine the operation
    if (strcmp(command, "-ext") == 0) { // Check if command is "-ext"
        printf("Compute extended version of formulas in %s\n", inputFile);
        printf("Writing formulas to %s\n", outputFile);
        parseFormula(inputFile, outputFile); // Expand formulas and write to output
    } 
    else if (strcmp(command, "-v") == 0) { // Check if command is "-v" for validation
        printf("Verify balanced parentheses in %s\n", inputFile);
        int invalidLines = parenthesesValidation(inputFile); // Validate parentheses
        if (invalidLines == 0) { // If no invalid lines, print message
            printf("Parentheses are balanced for all chemical formulas\n"); 
        }
    } 
    else if (strcmp(command, "-pn") == 0) { // Check if command is "-pn" for proton count
        // Dynamically allocate memory for elements array
        ELEMENT *elements = (ELEMENT *)malloc(118 * sizeof(ELEMENT)); // Assume max of 118 elements
        if (elements == NULL) { // Check if memory allocation succeeded
            perror("Memory allocation failed for elements");
            return EXIT_FAILURE;
        }

        int numElements = 0; // Initialize number of elements
        loadPeriodicTable(elements, &numElements, periodicTableFile); // Load periodic table data
        printf("Compute total proton number of formulas in %s\n", inputFile);
        printf("Writing formula to %s\n", outputFile);
        
        countProtons(elements, numElements, inputFile, outputFile); // Calculate and write proton counts

        free(elements); // Free dynamically allocated memory for elements array
    } else { // Invalid command given
        printf("Command given is not an allowed command!");
        exit(EXIT_FAILURE);
    }

    return 0;
}
