#include "library.h"

// Queue operations

// Procedure InitQueue - Initializes the queue
void InitQueue(Queue *Q) {
    (*Q).Head = NULL;  // Set the Head to NULL (empty queue)
    (*Q).Tail = NULL;  // Set the Tail to NULL (empty queue)
}

// Procedure Enqueue - Adds a user to the queue
void Enqueue(Queue *queue, User data) {
    EQueue newNode = (EQueue)malloc(sizeof(QNode));  // Allocate memory for a new node
    if (newNode == NULL) {  // Check if memory allocation is successful
        printf("Memory allocation failed.\n");
        return;
    }

    // Copy the user data correctly into the new node
    newNode->Data.userID = data.userID;
    strncpy(newNode->Data.name, data.name, sizeof(newNode->Data.name) - 1);  // Ensure null termination
    newNode->Data.name[sizeof(newNode->Data.name) - 1] = '\0';  // Ensure null-termination for name
    newNode->Data.requestedBookID = data.requestedBookID;  // Set the requested book ID
    newNode->Next = NULL;  // Set the next pointer of the new node to NULL (end of the queue)

    // If the queue is empty, initialize the Head and Tail to the new node
    if (queue->Tail == NULL) {
        queue->Head = newNode;
        queue->Tail = newNode;
    } else {
        // Otherwise, add the new node at the end of the queue
        queue->Tail->Next = newNode;
        queue->Tail = newNode;
    }
}

// Procedure Dequeue - Removes a user from the queue
void Dequeue(Queue *Q, TypeElm *x) {
    EQueue V;
    V = (*Q).Head;  // Get the node at the front of the queue
    *x = V->Data;  // Copy the data from the front node

    // If the queue has only one element, set both Head and Tail to NULL
    if ((*Q).Head == (*Q).Tail) {
        (*Q).Head = NULL;
        (*Q).Tail = NULL;
    } else {
        // Otherwise, move the Head to the next node
        (*Q).Head = (*Q).Head->Next;
    }
    free(V);  // Free the memory of the dequeued node
}

// Function isQEmpty - Checks if the queue is empty
int isQEmpty(Queue Q) {
    if (Q.Head == NULL)  // If Head is NULL, the queue is empty
        return 1;
    else
        return 0;  // Queue is not empty
}

// Function Head - Returns the data at the front of the queue
TypeElm Head(Queue Q) {
    return Q.Head->Data;  // Return the data at the front node
}

// Function to display the elements of the queue
void DisplayQueue(Queue *queue) {
    if (isQEmpty(*queue)) {  // If the queue is empty, print a message
        printf("No users in the borrow request queue.\n");
        return;
    }

    Queue tempQueue;
    InitQueue(&tempQueue);  // Initialize a temporary queue to store the elements
    User user;

    // Traverse the queue and print the details of each user
    while (!isQEmpty(*queue)) {
        Dequeue(queue, &user);  // Dequeue the user
        printf("User ID: %d, Name: %s, Requested Book ID: %d\n",
               user.userID, user.name, user.requestedBookID);
        Enqueue(&tempQueue, user);  // Re-enqueue the user to the temporary queue
    }

    // Restore the original queue by transferring users back from the temporary queue
    while (!isQEmpty(tempQueue)) {
        Dequeue(&tempQueue, &user);  // Dequeue from the temporary queue
        Enqueue(queue, user);  // Re-enqueue back to the original queue
    }
}
