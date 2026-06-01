#ifndef LIBRARY_H
#define LIBRARY_H
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Book structure
typedef struct {
    int bookID;
    char title[50];
    char author[50];
    bool isAvailable;
} Book;

// Stack for books
typedef struct BNode {
    Book data;             // The data of each node is a Book structure
    struct BNode* next;    // Pointer to the next node in the stack
} BNode;

typedef BNode* BookStack;  // BookStack is a pointer to BNode

// Declaration of User structure
typedef struct {
    int userID;            // User ID
    char name[50];         // User Name
    int requestedBookID;   // Requested Book ID
} User;

typedef User TypeElm;  // TypeElm is just an alias for the User structure

// Declaration of a Queue for User requests
typedef struct Element* EQueue;
typedef struct Element {
    TypeElm Data;         // The data for each queue node is a User structure
    EQueue Next;          // Pointer to the next element in the queue
} QNode;

typedef struct {
    EQueue Head, Tail;    // Pointers to the head and tail of the queue
} Queue;

// Function Prototypes
void initStack(BookStack* stack);                      // Initializes the stack
void Push(BookStack* stack, Book book);                 // Pushes a book onto the stack
void Pop(BookStack* stack, Book* book);                 // Pops a book from the stack
int isSEmpty(BookStack* stack);                         // Checks if the stack is empty
Book Top(BookStack* stack);                             // Returns the book at the top of the stack
void displayStack(BookStack* stack);                    // Displays all books in the stack

void InitQueue(Queue* queue);                           // Initializes the queue
void Enqueue(Queue* queue, User data);                  // Adds a user request to the queue
void Dequeue(Queue* queue, User* u);                    // Removes a user request from the queue
void DisplayQueue(Queue* queue);                        // Displays all users in the queue
int isQEmpty(Queue queue);                              // Checks if the queue is empty

int addBook(BookStack* stack);                          // Adds a new book to the stack
void borrowBook(BookStack* allBooksStack, BookStack* borrowedBooksStack, Queue* queue, int userID, int bookID, char name[]);  // Borrows a book
void returnBook(BookStack* stack, int bookID, BookStack* borrowedBooks);  // Returns a borrowed book
void processNextBorrowRequest(Queue* queue, BookStack* allBooks, BookStack* borrowedBooks);  // Processes the next borrow request from the queue
int searchBook(BookStack* stack, int bookID);           // Searches for a book by its ID

#endif
