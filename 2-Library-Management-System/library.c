#include "library.h"

// Global variables for books and queues
BookStack returnedBooks;
BookStack allBooks;
BookStack borrowedBooks;
Queue borrowQueue;

// Display the main menu of the library management system
void displayMenu() {
    printf("\n\n  Library Management System\n");
    printf("1. Add New Book\n");
    printf("2. Borrow Book\n");
    printf("3. Return Book\n");
    printf("4. Process Borrow Requests\n");
    printf("5. View Recently Returned Books\n");
    printf("6. Display Borrow Request Queue\n");
    printf("7. Search for a Book\n");
    printf("8. Exit\n");
    printf("Enter your choice: ");
}

// Function to add a new book to the library
int addBook(BookStack *stack) {
    Book book;
    printf("Enter Book ID: ");
    scanf("%d", &book.bookID);
    printf("Enter Book Title: ");
    scanf(" %[^\n]", book.title);
    printf("Enter Author Name: ");
    scanf(" %[^\n]", book.author);
    book.isAvailable = true;  // Mark the book as available
    Push(stack, book);  // Push the book to the allBooks stack
    printf("Book added successfully! ");
    return 1;
}

// Borrow a book: Check if available, then remove from library and add to borrowed books stack
void borrowBook(BookStack *allBooks, BookStack *borrowedBooks, Queue *queue, int userID, int bookID, char name[]) {
    BookStack tempStack = NULL;  // Temporary stack to hold books while searching
    int found = 0;
    Book borrowedBook;
    Book currentBook;

    // Traverse all books stack using temporary stack to find the book
    while (!isSEmpty(allBooks)) {  // Check if the allBooks stack is empty
        Pop(allBooks, &currentBook);  // Pop book from allBooks stack
        if (currentBook.bookID == bookID) {
            // If the book is found
            found = 1;
            if (currentBook.isAvailable) {  // If the book is available
                currentBook.isAvailable = false;  // Mark the book as borrowed
                Push(borrowedBooks, currentBook);  // Push to borrowed books stack
                Push(allBooks, currentBook);  // Push to borrowed books stack (though this seems redundant)
                printf("Book '%s' (ID: %d) has been borrowed successfully by User ID: %d.\n", currentBook.title, currentBook.bookID, userID);
                break;
            } else {
                // If the book is already borrowed, add user to the queue
                User user;
                user.userID = userID;
                strcpy(user.name, name);  // Ensure null-termination for name
                user.requestedBookID = bookID;
                printf("Book not available. Adding you to the borrow queue.\n");
                Enqueue(queue, user);  // Add user to the borrow queue
                break;
            }
        }
        Push(&tempStack, currentBook);  // Push the book back to tempStack if not found
    }

    // Refill the allBooks stack with remaining books from tempStack
    while (!isSEmpty(&tempStack)) {
        Pop(&tempStack, &currentBook);  // Pop from tempStack
        Push(allBooks, currentBook);  // Push back to allBooks
    }

    // If the book is not found in the library
    if (!found) {
        printf("Book not found in the library.\n");
    }
}

// Return a book: Mark as available and move from borrowed books to returned books stack
void returnBook(BookStack *stack, int bookID, BookStack *borrowedBooks) {
    Book book;
    BookStack tempStack;
    initStack(&tempStack);  // Temporary stack to hold books while processing return

    // Traverse the borrowedBooks stack to find the book
    while (!isSEmpty(borrowedBooks)) {
        Pop(borrowedBooks, &book);
        if (book.bookID == bookID) {
            book.isAvailable = true;  // Mark the book as available
            Push(stack, book);  // Add back to the allBooks stack
        } else {
            Push(&borrowedBooks, book);  // Push the book back to borrowedBooks stack if not returned
        }
    }

    // Restore the original stack (even if the book was found or not)
    while (!isSEmpty(&tempStack)) {
        Pop(&tempStack, &book);
        Push(stack, book);  // Restore the books to the original stack
    }
}

// Process the next borrow request from the queue
void processNextBorrowRequest(Queue *queue, BookStack *returnedBooks, BookStack *borrowedBooks) {
    if (isQEmpty(*queue)) {
        printf("No users in the borrow request queue.\n");
        return;
    }

    // Dequeue the next user
    User nextUser;
    Dequeue(queue, &nextUser);

    BookStack tempStack;
    initStack(&tempStack);  // Temporary stack for processing returned books
    Book currentBook;
    int bookFound = 0;

    // Traverse the returnedBooks stack to find the requested book
    while (!isSEmpty(returnedBooks)) {
        Pop(returnedBooks, &currentBook);
        if (currentBook.bookID == nextUser.requestedBookID) {
            bookFound = 1;

            if (currentBook.isAvailable) {
                printf("Processing borrow request for User ID: %d, Name: %s, Requested Book ID: %d\n", nextUser.userID, nextUser.name, nextUser.requestedBookID);

                // Mark the book as borrowed and move to borrowedBooks stack
                currentBook.isAvailable = false;
                Push(borrowedBooks, currentBook);
                printf("Book '%s' (ID: %d) has been borrowed successfully by User ID: %d.\n", currentBook.title, currentBook.bookID, nextUser.userID);
            } else {
                printf("Book '%s' (ID: %d) is not available.\n", currentBook.title, currentBook.bookID);

                // Re-enqueue the user if the book is unavailable
                Enqueue(queue, nextUser);
            }
        }
        // Push the book to the temporary stack
        Push(&tempStack, currentBook);
    }

    // Restore the returnedBooks stack
    while (!isSEmpty(&tempStack)) {
        Pop(&tempStack, &currentBook);
        Push(returnedBooks, currentBook);
    }

    if (!bookFound) {
        printf("Unfortunately, the book with ID %d is not currently available in the returned books stack. Thank you for your patience.\n", nextUser.requestedBookID);
        Enqueue(queue, nextUser);  // Re-enqueue the user if the book is not found
    }
}

// Search for a book in the library (in allBooks, returnedBooks, and borrowedBooks)
int searchBook(BookStack *stack, int bookID) {
    BookStack tempStack;
    initStack(&tempStack);  // Initialize temporary stack to preserve the original stack order
    Book book;
    int found = 0;

    // Search through the stack
    while (!isSEmpty(stack)) {
        Pop(stack, &book);
        if (book.bookID == bookID) {
            found = 1;  // Book found
            printf("Book found: ID: %d, Title: %s, Author: %s\n", book.bookID, book.title, book.author);
        }
        Push(&tempStack, book);  // Push the current book to the temporary stack
    }

    // Restore the original stack
    while (!isSEmpty(&tempStack)) {
        Pop(&tempStack, &book);
        Push(stack, book);  // Restore the books to the original stack
    }
    return found;  // Return 1 if found, 0 if not found
}

// Main function: Run the library management system
int main() {
   initStack(&returnedBooks);
   initStack(&borrowedBooks);
   initStack(&allBooks);

    int choice;
    Book book;
    User user;
    while (1) {
        displayMenu();
        do {
            scanf("%d", &choice);
            if (choice < 1 || choice > 8) {
                printf("\nInvalid choice! Please enter a value between 1 and 8.\n");
            }
        } while (choice < 1 || choice > 8);

        switch (choice) {
            case 1:
                addBook(&allBooks);
                break;

            case 2:
                printf("Enter User ID: ");
                scanf("%d", &user.userID);
                printf("Enter User Name: ");
                scanf(" %[^\n]", user.name);
                printf("Enter Book ID to Borrow: ");
                scanf("%d", &user.requestedBookID);

                borrowBook(&allBooks, &borrowedBooks, &borrowQueue, user.userID, user.requestedBookID, user.name);
                break;

            case 3:
                printf("Enter Book ID to Return: ");
                scanf("%d", &book.bookID);
                returnBook(&returnedBooks, book.bookID, &borrowedBooks);
                returnBook(&allBooks, book.bookID, &borrowedBooks);
                printf("Book returned successfully");
                break;

            case 4:
                processNextBorrowRequest(&borrowQueue, &returnedBooks, &borrowedBooks);
                break;

            case 5:
                displayStack(&returnedBooks);  // Display recently returned books
                break;

            case 6:
                DisplayQueue(&borrowQueue);  // Display the borrow request queue
                break;

            case 7:
                printf("Enter Book ID to Search: ");
                int bookID;
                scanf("%d", &bookID);

                if ((searchBook(&allBooks, bookID)) || (searchBook(&returnedBooks, bookID))) {
                    if (searchBook(&borrowedBooks, bookID)) {
                        printf("The book is currently borrowed.\n");
                    } else {
                        printf("The book is available in the library.\n");
                    }
                } else {
                    printf("Book not found.\n");
                }
                break;

            case 8:
                printf("Exiting the system...\n Goodbye!\n");
                exit(0);
                break;

            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}
