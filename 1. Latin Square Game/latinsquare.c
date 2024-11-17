/**
 * @file latinsquare.c
 * @brief Function prototypes for the console driver.
 *
 *
 * @author Spyros Gavriil
 * @since 26/09/2024
 * @bug No known bugs.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define N 9 // Maximum size of the array

/**
 * @brief Displays a Latin square in a formatted grid with boundaries.
 *
 * This function prints a Latin square of given size in a well-formatted table.
 * Each element in the square is surrounded by boundaries (| and +) and negative
 * numbers are displayed in parentheses.
 *
 * @param square A 2D array representing the Latin square.
 * @param size The size of the Latin square.
 *
 */
void displayLatinSquare(short square[N][N], int size);
/**
 * @brief Reads a Latin square from the specified file.
 *
 * This function opens the file, reads the size of the Latin square, and fills the array
 * with the values from the file. If the file contains invalid data or cannot be opened,
 * the function prints an error and exits the program.
 *
 * @param square The 2D array where the Latin square will be stored.
 * @param filename The name of the file containing the Latin square.
 * @param size Pointer to an integer that will store the size of the Latin square.
 */
void readLatinSquare(short square[N][N], const char *filename, int *size);
/**
 * @brief Plays a Latin square game where the user can input values into the square.
 *
 * The function repeatedly displays the current state of the Latin square and prompts
 * the user for input to modify the square. The input can either set a value, clear a
 * cell, or end the game. The game ends when the user inputs the command to save and exit
 * or when the Latin square is completely filled with non-zero values.
 *
 * @param square A 2D array representing the Latin square.
 * @param size The size of the Latin square (number of rows and columns).
 * @param filename The name of the file where the Latin square will be saved when the game ends.
 *
 */
void play(short square[N][N], int size, const char *filename);
/**
 * @brief Validates the user's input for modifying the Latin square.
 *
 * This function checks if the indices (i, j) and the value `val` are within the allowed
 * range for the Latin square. It also ensures that clearing a protected cell or inserting
 * a duplicate value in the same row or column is not allowed.
 *
 * @param square A 2D array representing the Latin square.
 * @param size The size of the Latin square (number of rows and columns).
 * @param i The row index (0-based) for the cell to modify.
 * @param j The column index (0-based) for the cell to modify.
 * @param val The value to insert into the cell, or 0 to clear the cell.
 *
 * @return true if the input is valid and can be applied, false otherwise.
 *
 */
bool checkInput(short square[N][N], int size, int i, int j, int val);
/**
 * @brief Checks for duplicates of a given value in the row and column of the Latin square.
 *
 * This function checks whether the given value `val` already exists in the same row or column
 * as the cell (i, j) in the Latin square. Duplicate values are not allowed in any row or column.
 *
 * @param square A 2D array representing the Latin square.
 * @param size The size of the Latin square (number of rows and columns).
 * @param i The row index (0-based) where the value is to be inserted.
 * @param j The column index (0-based) where the value is to be inserted.
 * @param val The value to check for duplicates in the row and column.
 *
 * @return true if a duplicate value is found in the row or column, false otherwise.
 *
 */
void handleInput(short square[N][N], int size, int i, int j, int val, const char *filename);
/**
 * @brief Checks for duplicates of a given value in the row and column of the Latin square.
 *
 * This function checks whether the given value `val` already exists in the same row or column
 * as the cell (i, j) in the Latin square. Duplicate values are not allowed in any row or column.
 *
 * @param square A 2D array representing the Latin square.
 * @param size The size of the Latin square (number of rows and columns).
 * @param i The row index (0-based) where the value is to be inserted.
 * @param j The column index (0-based) where the value is to be inserted.
 * @param val The value to check for duplicates in the row and column.
 *
 * @return true if a duplicate value is found in the row or column, false otherwise.
 *
 */
bool checkDuplicates(short square[N][N], int size, int i, int j, int val);
/**
 * @brief Saves the current Latin square to a file.
 *
 * This function writes the current state of the Latin square to a file. The output filename is
 * prefixed with "out-" and the contents are written in a plain text format with each row of
 * the Latin square on a new line.
 *
 * @param square A 2D array representing the Latin square.
 * @param size The size of the Latin square.
 * @param filename The original filename used as a base to generate the output file name.
 *
 */
void writeLatinSquare(short square[N][N], int size, const char *filename);

/**
 * @brief Main function to execute the Latin square game.
 *
 * This function checks if the correct number of arguments is provided, reads the Latin square from a file,
 * and starts the gameplay. It uses the file specified by the user to initialize the game.
 *
 * @param argc The number of command-line arguments.
 * @param argv An array of command-line arguments. argv[1] should be the filename of the game file.
 * @return 0 on successful execution.
 */
int main(int argc, char *argv[])
{
    // Check if the correct number of arguments is provided
    if (argc != 2)
    {
        printf("Missing arguments\nUsage: %s <game-file>\n", argv[0]);
        return 1;
    }

    short square[N][N]; // Define the array with the maximum size
    int size;           // Size will be dynamically set based on the file

    // Read the Latin square from the file
    readLatinSquare(square, argv[1], &size);

    // Start the game
    play(square, size, argv[1]);

    return 0;
}

/**
 * @brief Reads a Latin square from the specified file.
 *
 * This function opens the file, reads the size of the Latin square, and fills the array
 * with the values from the file. If the file contains invalid data or cannot be opened,
 * the function prints an error and exits the program.
 *
 * @param square The 2D array where the Latin square will be stored.
 * @param filename The name of the file containing the Latin square.
 * @param size Pointer to an integer that will store the size of the Latin square.
 */
void readLatinSquare(short square[N][N], const char *filename, int *size)
{
    FILE *file = fopen(filename, "r");

    // Check if the file was opened successfully
    if (file == NULL)
    {
        perror("Error opening file");
        exit(1); // Exit the program if file can't be opened
    }

    // Read the size from the first line
    if (fscanf(file, "%d", size) != 1 || *size > N || *size <= 0)
    {
        printf("Invalid size in file. Max allowed size is %d\n", N);
        fclose(file);
        exit(EXIT_FAILURE);
    }

    // Read the numbers from the file and fill the square
    for (int i = 0; i < *size; i++)
    {
        for (int j = 0; j < *size; j++)
        {
            if (fscanf(file, "%hd", &square[i][j]) != 1)
            {
                printf("File contains invalid values!\n");
                fclose(file);
                exit(EXIT_FAILURE); // Exit if reading fails
            }

            // Check for valid range of values
            if (square[i][j] < -*size || square[i][j] > *size)
            {
                printf("File contains invalid values\n");
                fclose(file);
                exit(EXIT_FAILURE);
            }
        }
    }

    // Check for extra values in the file
    short temp;
    if (fscanf(file, "%hd", &temp) == 1)
    {
        printf("File contains more data than expected!\n");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    // Close the file
    fclose(file);
}

/**
 * @brief Displays a Latin square in a formatted grid with boundaries.
 *
 * This function prints a Latin square of given size in a well-formatted table.
 * Each element in the square is surrounded by boundaries (| and +) and negative
 * numbers are displayed in parentheses.
 *
 * @param square A 2D array representing the Latin square.
 * @param size The size of the Latin square.
 *
 */
void displayLatinSquare(short square[N][N], int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("+");
        for (int j = 0; j < size; j++)
        {
            printf("-----+");
        }
        printf("\n");
        for (int j = 0; j < size; j++)
        {
            int number = square[i][j];

            // If the number is negative, print with parentheses
            if (number < 0)
            {
                printf("| (%d) ", -number);
            }
            else
            {
                // Print positive number normally
                printf("|  %d  ", number);
            }
        }
        printf("|\n");
    }
    printf("+");
    for (int j = 0; j < size; j++)
    {
        printf("-----+");
    }
    printf("\n");
}

/**
 * @brief Plays a Latin square game where the user can input values into the square.
 *
 * The function repeatedly displays the current state of the Latin square and prompts
 * the user for input to modify the square. The input can either set a value, clear a
 * cell, or end the game. The game ends when the user inputs the command to save and exit
 * or when the Latin square is completely filled with non-zero values.
 *
 * @param square A 2D array representing the Latin square.
 * @param size The size of the Latin square (number of rows and columns).
 * @param filename The name of the file where the Latin square will be saved when the game ends.
 *
 */
void play(short square[N][N], int size, const char *filename)
{
    int i, j, val;
    bool solved = false;
    while (!solved)
    {
        displayLatinSquare(square, size);

        printf("Enter your command in the following format:\n");
        printf("+ i,j=val: for entering val at position (i,j)\n");
        printf("+ i,j=0 : for clearing cell (i,j)\n");
        printf("+ 0,0=0 : for saving and ending the game\n");
        printf("Notice: i, j, val numbering is from [1..%d]\n", size);
        printf(">");

        if (scanf("%d,%d=%d", &i, &j, &val) != 3)
        {
            while (getchar() != '\n')
            {
            }; // Clear the input buffer
            printf("Error: wrong format of command!\n");
        }
        else
        {
            printf("\n");
            handleInput(square, size, i - 1, j - 1, val, filename);
        }

        solved = true;
        for (int row = 0; row < size && solved; row++)
        {
            for (int col = 0; col < size && solved; col++)
            {
                if (square[row][col] == 0)
                {
                    solved = false;
                }
            }
        }
    }

    printf("\nGame completed!!!\n");
    displayLatinSquare(square, size);
    writeLatinSquare(square, size, filename);
}

/**
 * @brief Validates the user's input for modifying the Latin square.
 *
 * This function checks if the indices (i, j) and the value `val` are within the allowed
 * range for the Latin square. It also ensures that clearing a protected cell or inserting
 * a duplicate value in the same row or column is not allowed.
 *
 * @param square A 2D array representing the Latin square.
 * @param size The size of the Latin square (number of rows and columns).
 * @param i The row index (0-based) for the cell to modify.
 * @param j The column index (0-based) for the cell to modify.
 * @param val The value to insert into the cell, or 0 to clear the cell.
 *
 * @return true if the input is valid and can be applied, false otherwise.
 *
 */
bool checkInput(short square[N][N], int size, int i, int j, int val)
{
    if (i < 0 || i >= size || j < 0 || j >= size || val < 0 || val > size)
    {
        printf("Error: i,j or val are outside the allowed range [1..%d]!\n", size);
        return false;
    }
    if (val == 0)
    {
        if (square[i][j] < 0)
        {
            printf("Error: illegal to clear cell!\n");
            return false;
        }
    }
    else
    {
        if (square[i][j] != 0)
        {
            printf("Error: cell is already occupied!\n");
            return false;
        }
        if (checkDuplicates(square, size, i, j, val))
        {
            printf("Error: Illegal value insertion!\n");
            return false;
        }
    }
    return true;
}

/**
 * @brief Handles the user's input to modify the Latin square or save and exit the game.
 *
 * This function processes the user's command by either modifying the Latin square or
 * saving the current game state and exiting if the user inputs the save command.
 *
 * @param square A 2D array representing the Latin square.
 * @param size The size of the Latin square (number of rows and columns).
 * @param i The row index (0-based) for the cell to modify.
 * @param j The column index (0-based) for the cell to modify.
 * @param val The value to insert into the cell, or 0 to clear the cell.
 * @param filename The name of the file where the Latin square will be saved.
 *
 */
void handleInput(short square[N][N], int size, int i, int j, int val, const char *filename)
{
    if (i == -1 && j == -1 && val == 0)
    {
        writeLatinSquare(square, size, filename);
        exit(EXIT_SUCCESS); // Save the game logic if required and then exit
    }

    if (checkInput(square, size, i, j, val))
    {
        square[i][j] = val;
        if (val == 0)
        {
            printf("Value cleared!\n");
        }
        else
        {
            printf("Value inserted!\n");
        }
    }
}

/**
 * @brief Checks for duplicates of a given value in the row and column of the Latin square.
 *
 * This function checks whether the given value `val` already exists in the same row or column
 * as the cell (i, j) in the Latin square. Duplicate values are not allowed in any row or column.
 *
 * @param square A 2D array representing the Latin square.
 * @param size The size of the Latin square (number of rows and columns).
 * @param i The row index (0-based) where the value is to be inserted.
 * @param j The column index (0-based) where the value is to be inserted.
 * @param val The value to check for duplicates in the row and column.
 *
 * @return true if a duplicate value is found in the row or column, false otherwise.
 *
 */
bool checkDuplicates(short square[N][N], int size, int i, int j, int val)
{
    for (int k = 0; k < size; k++)
    {
        if (abs(square[i][k]) == val) // Check for duplicates in the row
        {
            return true;
        }
    }
    for (int k = 0; k < size; k++)
    {
        if (abs(square[k][j]) == val) // Check for duplicates in the column
        {
            return true;
        }
    }
    return false;
}

/**
 * @brief Saves the current Latin square to a file.
 *
 * This function writes the current state of the Latin square to a file. The output filename is
 * prefixed with "out-" and the contents are written in a plain text format with each row of
 * the Latin square on a new line.
 *
 * @param square A 2D array representing the Latin square.
 * @param size The size of the Latin square.
 * @param filename The original filename used as a base to generate the output file name.
 *
 */
void writeLatinSquare(short square[N][N], int size, const char *filename)
{
    // Create a buffer for the output filename
    char outputFile[256]; // Ensure this is large enough for the output file name
    strcpy(outputFile, "out-");
    strcat(outputFile, filename); // Concatenate "out-" with the original filename

    // Open the output file for writing
    FILE *file = fopen(outputFile, "w");
    if (file == NULL)
    {
        perror("Error opening output file");
        exit(EXIT_FAILURE); // Exit if file opening fails
    }

    printf("Saving to %s...\n", outputFile);

    // Write the size first
    fprintf(file, "%d\n", size);

    // Write the square's content row by row
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            fprintf(file, "%d ", square[i][j]); // Write each value with a space separator
        }
        fprintf(file, "\n"); // New line after each row
    }

    printf("Done\n");
    // Close the file
    fclose(file);
}
