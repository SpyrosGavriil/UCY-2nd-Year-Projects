/**
 * @file stack.h
 * @brief This file contains declarations for a stack data structure that stores strings and provides basic stack operations.
 */

#ifndef STACK_H
#define STACK_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 4 /**< Define the maximum size of the string in a stack node */

/**
 * @brief Represents a node in the stack.
 */
typedef struct node {
    char data[MAX_SIZE];  /**< Data field holds a string */
    struct node *next;    /**< Pointer to the next node */
} NODE;

/**
 * @brief Represents the stack structure.
 */
typedef struct stack {
    NODE *top;  /**< Pointer to the top node in the stack */
    int size;   /**< Number of elements in the stack */
} STACK;

/**
 * @brief Initializes a new stack.
 * 
 * @param stack A double pointer to the stack to be initialized.
 * @return int Returns 0 on success, or an error code on failure.
 */
int initStack(STACK **stack);

/**
 * @brief Checks if the stack is empty.
 * 
 * @param stack A pointer to the stack.
 * @return bool Returns true if the stack is empty, false otherwise.
 */
bool isEmpty(STACK *stack);

/**
 * @brief Retrieves the top element of the stack without removing it.
 * 
 * @param stack A pointer to the stack.
 * @param retValue A buffer to store the top element's value.
 * @return int Returns 0 on success, or an error code on failure.
 */
int top(STACK *stack, char *retValue);

/**
 * @brief Pushes a new element onto the stack.
 * 
 * @param stack A pointer to the stack.
 * @param value The value to be pushed onto the stack.
 * @return int Returns 0 on success, or an error code on failure.
 */
int push(STACK *stack, const char *value);

/**
 * @brief Removes the top element from the stack and retrieves its value.
 * 
 * @param stack A pointer to the stack.
 * @param retValue A buffer to store the popped element's value.
 * @return int Returns 0 on success, or an error code on failure.
 */
int pop(STACK *stack, char *retValue);

/**
 * @brief Prints the entire stack to the console.
 * 
 * @param stack A pointer to the stack.
 */
void printStack(STACK *stack);

/**
 * @brief Frees all memory allocated for the stack.
 * 
 * @param stack A pointer to the stack to be freed.
 */
void freeStack(STACK *stack);

#endif // STACK_H
