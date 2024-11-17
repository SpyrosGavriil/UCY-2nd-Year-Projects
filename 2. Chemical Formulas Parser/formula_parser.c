#include "formula_parser.h"

/**
 * @brief Expands a single element or group by a multiplier, pushing it onto the stack multiple times.
 *
 * @param element The element or group of elements to be pushed onto the stack.
 * @param multiplier The number of times to push the element onto the stack.
 * @param currentStack A pointer to the stack where elements will be pushed.
 */
static void updateStack(char *element, int multiplier, STACK *currentStack)
{
    for (int i = 0; i < multiplier; i++)
    {
        push(currentStack, element); // Push the element onto the stack
    }
}

/**
 * @brief Parses a chemical formula and pushes the elements and groups onto a stack.
 *
 * This function processes each character in the formula string. It recognizes element symbols, multipliers,
 * and groups enclosed in parentheses. When an element symbol is encountered, it extracts the symbol and its multiplier,
 * and pushes it onto the stack `multiplier` times. For groups in parentheses, it temporarily stores the group in a buffer,
 * then multiplies and pushes each element onto the stack.
 *
 * @param formula A string representing the chemical formula to parse. Each character is processed to extract elements and groups.
 * @param stack A pointer to a `STACK` structure where parsed elements and groups are pushed.
 *
 * The function handles the following cases:
 * - Element symbols (e.g., "H", "O", "Ca", "Fe", etc.), which may have one or more lowercase letters.
 * - Multiplier digits (e.g., "H2O" where "H" has a multiplier of 2).
 * - Groups of elements within parentheses, each of which may have its own multiplier.
 *
 * The function uses dynamic memory allocation for temporary buffers to hold extracted elements and groups
 * but frees all allocated memory before finishing.
 *
 * @note The `STACK` structure is expected to have been initialized before calling this function.
 * The function assumes the `updateStack` function is defined to handle multipliers for element symbols.
 * 
 */
static void parseFormulaHelper(char *formula, STACK *stack) {
    int i = 0;
    while (formula[i] != '\0')
        {
            if (isalpha(formula[i])) // Check if current character is alphabetic
            {
                char *elements = (char *)malloc(4 * sizeof(char));
                if(elements == NULL) {
                    perror("Failed to allocate elements memory!");
                    exit(EXIT_FAILURE);
                }
                int j = 0;
                elements[j++] = formula[i++]; // Store first letter of the element
                if (islower(formula[i]))
                {
                    elements[j++] = formula[i++];
                } // Store second letter if lowercase
                if (islower(formula[i]))
                {
                    elements[j++] = formula[i++];
                }                   // Handle any extra lowercase letters
                elements[j] = '\0'; // Null-terminate the element symbol

                int multiplier = 1; // Default multiplier for element
                if (isdigit(formula[i]) && !isdigit(formula[i + 1]))
                {
                    multiplier = formula[i] - '0'; // Single-digit multiplier
                    i++;
                }
                else if (isdigit(formula[i]) && formula[i + 1] != '\n' && isdigit(formula[i + 1]))
                {
                    multiplier = 10 * (formula[i] - '0') + (formula[i + 1] - '0'); // Two-digit multiplier
                    i += 2;
                }

                updateStack(elements, multiplier, stack); // Push element onto stack multiplier times
                free(elements);
            }
            else if (formula[i] == '(')
            {
                push(stack, "(\0"); // Push opening parenthesis onto stack
                i++;
            }
            else if (formula[i] == ')')
            {
                i++;                // Move past closing parenthesis
                int multiplier = 1; // Default multiplier for group
                if (isdigit(formula[i]) && !isdigit(formula[i + 1]))
                {
                    multiplier = formula[i] - '0'; // Single-digit multiplier
                    i++;
                }
                else if (isdigit(formula[i]) && formula[i + 1] != '\n' && isdigit(formula[i + 1]))
                {
                    multiplier = 10 * (formula[i] - '0') + (formula[i + 1] - '0'); // Two-digit multiplier
                    i += 2;
                }

                int tempSize = 64;                                    // Initial size of temp buffer
                int tempLength = 0;                                   // Current used length in temp
                char *temp = (char *)malloc(tempSize * sizeof(char)); // Dynamically allocate memory for temp
                if (temp == NULL)
                {
                    perror("Memory allocation failed!");
                    exit(EXIT_FAILURE);
                }
                temp[0] = '\0'; // Initialize the buffer as an empty string

                char *poppedElement = (char *)malloc(4 * sizeof(char)); // Dynamically allocate memory for poppedElement (increased size)
                if (poppedElement == NULL)
                {
                    perror("Memory allocation failed!");
                    exit(EXIT_FAILURE);
                }
                top(stack, poppedElement);

                while (strcmp(poppedElement, "(") != 0) // While opening parentheses not found
                {
                    pop(stack, poppedElement); // Pop element

                    int poppedLen = strlen(poppedElement);
                    if (tempLength + poppedLen + 1 >= tempSize)
                    {
                        tempSize *= 2; // Double the buffer size
                        temp = (char *)realloc(temp, tempSize * sizeof(char));
                        if (temp == NULL)
                        {
                            perror("Memory reallocation failed!");
                            exit(EXIT_FAILURE);
                        }
                    }

                    strcat(temp, poppedElement); // Append the popped element to temp
                    tempLength += poppedLen;
                    top(stack, poppedElement); // Get the next element
                }
                pop(stack, poppedElement); // Pop the '('

                free(poppedElement); // Free the allocated memory for poppedElement after each use

                // Push elements in temp back to stack `multiplier` times
                for (int k = 0; k < multiplier; k++)
                {
                    for (int j = tempLength - 1; j >= 0; j--)
                    {
                        if (islower(temp[j]) && islower(temp[j - 1]))
                        {
                            char value[4] = {temp[j - 2], temp[j - 1], temp[j], '\0'}; // Handle 3-character symbols
                            j -= 2;
                            push(stack, value);
                        }
                        else if (islower(temp[j]))
                        {
                            char value[3] = {temp[j - 1], temp[j], '\0'}; // Handle 2-character symbols
                            j--;
                            push(stack, value);
                        }
                        else
                        {
                            char value[2] = {temp[j], '\0'}; // Single-character symbol
                            push(stack, value);
                        }
                    }
                }

                free(temp); // Free the dynamically allocated temp buffer
            }
        }
}

#ifdef PARSER_DEBUG

static void testParseFormula() {
    char formula[] = "Co3(Fe(CN)6)2";
    STACK *stack = NULL;
    initStack(&stack);
    parseFormulaHelper(formula, stack);
    // Reverse stack to correct order for output
    STACK *reversedStack = NULL;
    initStack(&reversedStack);
    while (!isEmpty(stack))
    {
        char *element = (char *)malloc(4 * sizeof(char)); // Dynamically allocate element buffer
        pop(stack, element);          // Pop from main stack
        push(reversedStack, element); // Push onto reversed stack
        free(element); // Free the dynamically allocated buffer
    }

    printStack(reversedStack); // This should print the decoded formula
}

static void testParentheses(const char *inputFile) { // You need to provide a valid textfile
    
    parenthesesValidation(inputFile);

}

int main(void) {
    testParseFormula();
}

#endif

void parseFormula(const char *inputFile, const char *outputFile)
{
    if (parenthesesValidation(inputFile) != 0)
    {
        return;
    } // Validate parentheses in input file; exit if invalid

    FILE *input = fopen(inputFile, "r");   // Open input file for reading
    FILE *output = fopen(outputFile, "w"); // Open output file for writing

    if (input == NULL || output == NULL)
    { // Check if files opened successfully
        perror("Error opening files!");
        exit(EXIT_FAILURE);
    }

    char formula[256];                                     // Buffer to store each formula line
    while (fgets(formula, sizeof(formula), input) != NULL) // Read each formula line
    {
        formula[strcspn(formula, "\n")] = '\0'; // Remove newline from formula
        STACK *stack = NULL;
        initStack(&stack); // Initialize stack for parsing formula

        parseFormulaHelper(formula, stack); // Call the helper to parse each formula line

        // Reverse stack to correct order for output
        STACK *reversedStack = NULL;
        initStack(&reversedStack);
        while (!isEmpty(stack))
        {
            char *element = (char *)malloc(4 * sizeof(char)); // Dynamically allocate element buffer
            pop(stack, element);          // Pop from main stack
            push(reversedStack, element); // Push onto reversed stack
            free(element); // Free the dynamically allocated buffer
        }

        while (!isEmpty(reversedStack))
        { // Output elements in correct order
            char *element = (char *)malloc(4 * sizeof(char)); // Dynamically allocate element buffer
            pop(reversedStack, element);
            fprintf(output, "%s ", element); // Write element to output file
            free(element); // Free the dynamically allocated buffer
        }
        fprintf(output, "\n");

        freeStack(stack);         // Free main stack
        freeStack(reversedStack); // Free reversed stack
    }

    fclose(input);  // Close input file
    fclose(output); // Close output file
}
void countProtons(ELEMENT elements[], int numElements, const char *inputFile, const char *outputFile)
{
    if (parenthesesValidation(inputFile) != 0)
    {
        return;
    } // Validate parentheses in input file; exit if invalid

    parseFormula(inputFile, "parsedOutput.txt"); // Parse the formula and write to temporary parsed output file

    FILE *parsedOutput = fopen("parsedOutput.txt", "r"); // Open parsed output file for reading
    FILE *output = fopen(outputFile, "w");               // Open output file for writing proton counts

    if (parsedOutput == NULL || output == NULL)
    { // Check if files opened successfully
        perror("Error opening files in countProtons");
        return;
    }

    char line[2048]; // Buffer to store each line of parsed output
    while (fgets(line, sizeof(line), parsedOutput) != NULL)
    {                                     // Read each line from parsed output
        line[strcspn(line, "\n")] = '\0'; // Remove newline character from line
        int count = 0;                    // Proton count for the current line

        char *element = strtok(line, " "); // Tokenize line by spaces to get each element
        while (element != NULL)
        {
            count += findAtomicNumber(element, elements, numElements); // Add atomic number to current count
            element = strtok(NULL, " ");                               // Get next element in the line
        }

        fprintf(output, "%d\n", count); // Write proton count for the line to output file
    }

    fclose(parsedOutput); // Close parsed output file
    fclose(output);       // Close final output file
}

int parenthesesValidation(const char *inputFile)
{
    FILE *input = fopen(inputFile, "r"); // Open input file for reading
    if (input == NULL)
    { // Check if file opened successfully
        perror("Error opening file in parenthesesValidation function");
        exit(EXIT_FAILURE);
    }

    int invalidLines = 0; // Counter for indalid lines
    STACK *stack = NULL;
    initStack(&stack);  // Initialize the stack
    char line[512];     // Buffer to store each line from the file
    int lineNumber = 0;

    while (fgets(line, sizeof(line), input) != NULL)
    { // Read each line from input
        lineNumber++;
        bool isValid = true; // Flag to track if parentheses in the line are balanced

        // Process each character in the line
        for (int i = 0; line[i] != '\0'; i++)
        {
            char c = line[i];

            if (c != '(' && c != ')')
            { // Skip non-parentheses characters
                continue;
            }

            if (c == '(')
            {
                char str[2] = {c, '\0'}; // Convert '(' to string for pushing
                push(stack, str);        // Push '(' onto the stack
            }
            else if (c == ')')
            {
                if (!isEmpty(stack))
                { // Check if stack has matching '(' to pop
                    char dummy[2];
                    pop(stack, dummy); // Pop matching '(' from stack
                }
                else
                {
                    isValid = false; // Mark as invalid if no matching '(' and break from the loop
                    break;           
                }
            }
        }

        if (!isValid || !isEmpty(stack))
        { // Check for unmatched '(' after the line is processed
            printf("Parentheses NOT balanced in line: %d\n", lineNumber);
            invalidLines++; // Increment counter for lines with invalid parentheses
        }

        // Reset the stack for the next line by popping all elements if any are left
        while (!isEmpty(stack))
        {
            char dummy[2];
            pop(stack, dummy);
        }
    }

    freeStack(stack);    // Free the stack memory
    fclose(input);       // Close the input file after processing
    return invalidLines; // Return the count of invalid lines
}
