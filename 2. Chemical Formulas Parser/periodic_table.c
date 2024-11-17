#include "periodic_table.h"

/**
 * @brief Sorts the array of ELEMENT structs by atomic number.
 *
 * @param elements An array of ELEMENT structs to be sorted.
 * @param numElements The number of elements in the array.
 */

static void sortPeriodicTable(ELEMENT elements[], int numElements)
{
    if (elements == NULL || numElements == 0)
    {
        // Nothing to sort if the array is NULL or empty
        return;
    }

    for (int i = 0; i < numElements - 1; i++)
    {
        for (int j = 0; j < numElements - i - 1; j++)
        {
            if (elements[j].atomicNumber > elements[j + 1].atomicNumber)
            {
                ELEMENT temp = elements[j];
                elements[j] = elements[j + 1];
                elements[j + 1] = temp;
            }
        }
    }
}

#ifdef PERIODIC_DEBUG

/**
 * @brief Prints the elements and their atomic numbers.
 *
 * @param elements An array of ELEMENT structs to be printed.
 * @param numElements The number of elements in the array.
 */
static void printElements(ELEMENT elements[], int numElements)
{
    if (elements == NULL || numElements == 0)
    {
        printf("No elements to print.\n");
        return;
    }

    for (int i = 0; i < numElements; i++)
    {
        printf("%s %d\n", elements[i].symbol, elements[i].atomicNumber);
    }
}

// Example static test functions
static void unsortedTester()
{
    ELEMENT elements[4] = {
        {"H", 1},
        {"He", 2},
        {"C", 6},
        {"B", 5}};

    printf("Printing before sorting:\n");
    printElements(elements, 4); // This should print H, He, C, B
    sortPeriodicTable(elements, 4);
    printf("Printing after sorting:\n");
    printElements(elements, 4); // This should print H, He, B, C
}

// Example static test functions
static void emptyArrayTester()
{
    ELEMENT *elements = NULL;       // Declare an empty array
    sortPeriodicTable(elements, 0); // Sort an empty array (this should do nothing)
    printf("Printing empty array:\n");
    printElements(elements, 0); // Print an empty array (this should print nothing)
}

static void loadTester()
{
    ELEMENT elements[118]; // Adjust the size based on expected number of elements
    int numElements = 0;

    // Call loadPeriodicTable with the test file
    loadPeriodicTable(elements, &numElements, "periodicTable.txt");

    // Print the loaded elements
    printElements(elements, numElements);
}

static void findAtomicNumberTester()
{
    ELEMENT elements[118]; // Adjust the size based on expected number of elements
    int numElements = 0;

    loadPeriodicTable(elements, &numElements, "periodicTable.txt");
    int atomicNumber = findAtomicNumber("Fr", elements, numElements);
    printf("This should be 87, answer is: %d\n", atomicNumber);
    atomicNumber = findAtomicNumber("Np", elements, numElements);
    printf("This should be 93, answer is: %d\n", atomicNumber);
}

int main(void)
{
    unsortedTester();         // Run test case
    emptyArrayTester();       // Run test case
    loadTester();             // Run test case
    findAtomicNumberTester(); // Run test case
    return 0;
}
#endif

void loadPeriodicTable(ELEMENT elements[], int *numElements, const char *filename)
{
    FILE *file = fopen(filename, "r"); // Open the file in read mode

    // Check if the file was successfully opened
    if (file == NULL)
    {
        perror("Failed to open file"); // Print error message if opening fails
        exit(EXIT_FAILURE);            // Exit the program with failure
    }

    *numElements = 0; // Initialize the number of elements to 0

    // Read elements from the file until no more can be read
    while (fscanf(file, "%4s %d", elements[*numElements].symbol, &elements[*numElements].atomicNumber) == 2)
    {
        (*numElements)++; // Increment the element count after each successful read
    }

    sortPeriodicTable(elements, *numElements); // Sort the elements by atomic number after loading them

    fclose(file); // Close the file after reading is done
}

int findAtomicNumber(char *element, ELEMENT elements[], int numElements)
{
    for (int i = 0; i < numElements; i++)
    { // Iterate through the array of elements
        if (strcmp(elements[i].symbol, element) == 0)
        {
            return elements[i].atomicNumber; // Return the atomic number if a match is found
        }
    }
    return 0; // Return 0 if the element is not found in the array
}
