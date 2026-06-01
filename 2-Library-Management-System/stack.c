#include "library.h"

// Stack Operations for BookStack

// Procedure InitStack - Initializes the stack
void initStack(BookStack* P) {
    *P = NULL;  // Start with an empty stack (NULL)
}

// Procedure Push - Adds a book to the stack
void Push(BookStack *S, Book b) {
    BookStack V;
    V = malloc(sizeof(BNode));  // Allocate memory for a new node
    V->data = b;      // Set the data of the new node (book)
    V->next = *S;     // Link the new node to the top of the stack
    *S = V;           // Update the stack to point to the new node
}

// Procedure Pop - Removes a book from the stack
void Pop(BookStack *S, Book *b) {
    BookStack V;
    *b = (*S)->data;  // Get the book data from the top node
    V = *S;           // Save the current top node
    *S = (*S)->next;  // Move the stack pointer to the next node
    free(V);          // Free the memory of the old top node
}

// Function isSEmpty - Checks if the stack is empty
int isSEmpty(BookStack *S) {
    if (*S == NULL) return 1;  // Return 1 if the stack is empty (NULL)
    else return 0;  // Return 0 if the stack is not empty
}

// Function Top - Returns the book at the top of the stack
Book Top(BookStack *S) {
    if (*S == NULL) {
        printf("Stack is empty.\n");  // If the stack is empty, print error message
        return;  // Return nothing if stack is empty (could also return a default value)
    }
    return (*S)->data;  // Return the book at the top of the stack
}

// Display the books in the stack
void displayStack(BookStack *stack) {
    if (isSEmpty(stack)) {
        printf("No books.\n");  // If stack is empty, display a message and return
        return;
    }

    Book book;
    BookStack tempStack;  // Declare tempStack as a normal variable

    initStack(&tempStack);  // Initialize tempStack properly

    // Traverse the stack, displaying books and moving them to tempStack
    while (!isSEmpty(stack)) {
        Pop(stack, &book);  // Pop a book from the stack
        printf("Book ID: %d, Title: %s, Author: %s\n", book.bookID, book.title, book.author);  // Print book details
        Push(&tempStack, book);  // Push the book to the temp stack
    }

    // Transfer books back to the original stack (optional)
    while (!isSEmpty(&tempStack)) {
        Pop(&tempStack, &book);  // Pop from tempStack
        Push(stack, book);  // Restore the books to the original stack
    }
}
