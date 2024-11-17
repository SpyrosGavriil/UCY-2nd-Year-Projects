#include "stack.h"

#ifdef STACK_DEBUG
// Example static test functions
static void tester() {
    STACK *stack = NULL;

    push(stack, "A"); // Should print error message

    initStack(&stack);
    push(stack, "A");
    push(stack, "B");
    push(stack, "C");

    printf("Stack is empty? %d\n", isEmpty(stack)); // Should print 0

    printStack(stack); // Should print C B A

    char poppedElement[4];
    pop(stack, poppedElement);
    printf("Popped element: %s\n", poppedElement); // Should print C;
    pop(stack, poppedElement);
    printf("Popped element: %s\n", poppedElement); // Should print B;
    pop(stack, poppedElement);
    printf("Popped element: %s\n", poppedElement); // Should print A;

    printf("Stack is empty? %d\n", isEmpty(stack)); // Should print 1

    pop(stack, poppedElement); // Should print error message
    printf("\n");
}

int main(void) {
    tester(); // Run test case
    return 0;
}
#endif

// Initialize the stack
int initStack(STACK **stack)
{
    *stack = (STACK *)malloc(sizeof(STACK));
    if ((*stack) == NULL)
        return EXIT_FAILURE;

    (*stack)->top = NULL;
    (*stack)->size = 0;
    return EXIT_SUCCESS;
}

// Check if the stack is empty
bool isEmpty(STACK *stack)
{
    return stack->size == 0;
}

// Get the top element of the stack
int top(STACK *stack, char *retValue)
{
    if (stack == NULL || stack->top == NULL)
    {
        retValue[0] = '\0'; // Return an empty string if the stack is empty
        return EXIT_FAILURE;
    }

    strncpy(retValue, stack->top->data, strlen(stack->top->data));
    retValue[strlen(stack->top->data)] = '\0';
    return EXIT_SUCCESS;
}

// Push a string onto the stack
int push(STACK *stack, const char *value)
{
    if (stack == NULL) {
        printf("Stack is not initialized\n");
        return EXIT_FAILURE;
    }

    NODE *newNode = (NODE *)malloc(sizeof(NODE));
    if (newNode == NULL)
    {
        printf("Cannot allocate space in stack");
        return EXIT_FAILURE;
    }

    // Copy the string value into the new node
    strncpy(newNode->data, value, strlen(value));
    newNode->data[strlen(value)] = '\0'; // Ensure null termination
    newNode->next = stack->top;
    stack->top = newNode;
    stack->size++;

    return EXIT_SUCCESS;
}

// Pop a string from the stack
int pop(STACK *stack, char *retValue)
{
    if (stack == NULL || isEmpty(stack))
    {
        printf("Stack is empty!");
        return EXIT_FAILURE;
    }

    NODE *temp = stack->top;
    int length = strlen(temp->data);
    strncpy(retValue, temp->data, length);
    retValue[length] = '\0'; // Ensure null termination based on the actual string length

    stack->top = temp->next;
    stack->size--;
    free(temp); // Free the memory for the popped node

    return EXIT_SUCCESS;
}

// Print the stack elements from top to bottom
void printStack(STACK *stack)
{
    if (isEmpty(stack))
    {
        printf("Stack is empty!\n");
        return;
    }

    NODE *current = stack->top;
    printf("Stack elements (from top to bottom):\n");
    while (current != NULL)
    {
        printf("%s ", current->data);
        current = current->next;
    }
    printf("\n");
}

// Free the entire stack and its nodes
void freeStack(STACK *stack)
{
    if (stack == NULL)
        return;

    while (!isEmpty(stack))
    {
        char temp[MAX_SIZE];
        pop(stack, temp); // Pop all elements to free nodes
    }

    free(stack); // Free the stack structure itself
}
