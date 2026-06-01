#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Creating a list of tasks
typedef struct task {
    int id;
    char description[100];
    int priority;
    char status[20];
    struct task *next;
} task;

// Function to create a new task
task* createNew(int id, char description[], int priority, char status[]) {
    task *newTask = (task*)malloc(sizeof(task));
    newTask->id = id;
    strcpy(newTask->description, description);
    newTask->priority = priority;
    strcpy(newTask->status, status);
    newTask->next = NULL;
    return newTask;
}
// Function to get a valid priority from the user
int getValidPriority() {
    int priority;
    while (1) {
        printf("Enter Task Priority (1-5): ");
        if (scanf("%d", &priority) == 1 && priority >= 1 && priority <= 5) {
            return priority;  // Return valid priority
        } else {
            // If the input is invalid, flush the input buffer and prompt again
            while (getchar() != '\n');  // Clear invalid input
            printf("Invalid input. Please enter a priority between 1 and 5.\n");
        }
    }
}

// Function to insert a task into the list in priority order
task* insertion(task *head, int id, char description[], int priority, char status[]) {
    task *previous = NULL, *current = head;
    task *newTask = createNew(id, description, priority, status);

    // Check if ID already exists
    while (current != NULL) {
        if (current->id == id) {
            printf("\nTask with ID %d already exists.\n", id);
            free(newTask);  // Free the unused memory
            return head;
        }
        current = current->next;
    }
    current = head;

    // Insert the task in priority order
    if (head == NULL || head->priority > priority) {
        newTask->next = head;
        head = newTask;
    } else {
        while (current != NULL && current->priority <= priority) {
            previous = current;
            current = current->next;
        }
        previous->next = newTask;
        newTask->next = current;
    }
    printf("\nTask added successfully.\n");
    return head;
}

// Function to delete a task by ID
task* deleteTask(task *head, int id) {
    task *previous = NULL, *current = head;

    // Check if the head node needs to be deleted
    if (head != NULL && head->id == id) {
        head = head->next;
        free(current);
        printf("\nTask with ID %d has been deleted.\n", id);
        return head;
    }

    // Traverse the list to find the task
    while (current != NULL && current->id != id) {
        previous = current;
        current = current->next;
    }

    // If task is not found
    if (current == NULL) {
        printf("\nTask with ID %d not found.\n", id);
        return head;
    }

    previous->next = current->next;
    free(current);
    printf("\nTask with ID %d has been deleted.\n", id);
    return head;
}

// Function to update the status of a task by ID
void updateStatus(task *head, int id, char newStatus[]) {
    task *current = head;

    while (current != NULL) {
        if (current->id == id) {
            strcpy(current->status, newStatus);
            printf("\nTask updated successfully.\n");
            return;
        }
        current = current->next;
    }
    printf("\nTask with ID %d not found.\n", id);
}

// Function to save tasks to a file
void saveTasksToFile(task *head) {
    FILE *file = fopen("tasks.txt", "w");
    if (file == NULL) {
        printf("Error: Unable to create or open tasks.txt for writing!\n");
        return;
    }
    printf("Saving tasks to file...\n");

    task *current = head;
    while (current != NULL) {
        fprintf(file, "%d,%s,%d,%s\n",
                current->id,
                current->description,
                current->priority,
                current->status);
        printf("Saved Task: ID=%d\n", current->id); // Debugging info
        current = current->next;
    }

    fclose(file);
    printf("All tasks saved successfully to tasks.txt\n");
}

// Function to load tasks from a file
task* loadTasksFromFile(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("No existing tasks file found. Starting fresh.\n");
        return NULL;
    }

    task *head = NULL;
    int id, priority;
    char description[100], status[20];

    while (fscanf(file, "%d,%99[^,],%d,%19[^\n]\n", &id, description, &priority, status) != EOF) {
        head = insertion(head, id, description, priority, status);
    }

    fclose(file);
    printf("Tasks loaded from file successfully.\n");
    return head;
}
// Function display By Status
void displayByStatus(task *head) {
    task *temp;
    int found;  // Flag to indicate if tasks with the given priority are found

    // Check if the list is empty
    if (head == NULL) {
        printf("\nYour list is empty\n");
        return;
    }
    temp = head;
    // Display pending tasks
    printf("\nThe pending tasks are:\n");
    found = 0; // Reset found for pending tasks
    while (temp != NULL) {
        if (strcmp(temp->status, "pending") == 0) {
            printf("ID: %d, Description: %s, Priority: %d\n", temp->id, temp->description, temp->priority);
            found = 1;
        }
        temp = temp->next;
    }
    if (found == 0) {
        printf(" No pending tasks\n");
    }

    // Reset temp pointer and display in-progress tasks
    temp = head;
    printf("\nThe in-progress tasks are:\n");
    found = 0; // Reset found for in-progress tasks
    while (temp != NULL) {
        if (strcmp(temp->status, "in progress") == 0) {
            printf("ID: %d, Description: %s, Priority: %d\n", temp->id, temp->description, temp->priority);
            found = 1;
        }
        temp = temp->next;
    }
    if (found == 0) {
        printf("No in-progress tasks\n");
    }

    // Reset temp pointer and display completed tasks
    temp = head;
    printf("\nThe completed tasks are:\n");
    found = 0; // Reset found for completed tasks
    while (temp != NULL) {
        if (strcmp(temp->status, "completed") == 0) {
            printf("ID: %d, Description: %s, Priority: %d\n", temp->id, temp->description, temp->priority);
            found = 1;
        }
        temp = temp->next;
    }
    if (found == 0) {
        printf("No completed tasks\n");
    }
}
// Function to search tasks by priority
void searchByPriority(task *head, int priority) {
    task *current = head;
    int found = 0;        // Flag to indicate if tasks with the given priority are found

    printf("The tasks with priority %d are:\n", priority);

    // Traverse through the linked list to find tasks with the given priority
    while (current != NULL) {
        if (current->priority == priority) {
            // Print task details if the priority matches
            printf("ID: %d, Description: %s, Status: %s\n", current->id, current->description, current->status);
            found = 1;
        }
        current = current->next;
    }

    // If no tasks were found with the specified priority, print a message
    if (found == 0) {
        printf("Sorry, there are no tasks with priority %d!\n", priority);
    }
}
void displayAllTasks(task *head) {
    task *current = head;

    // Check if the list is empty
    if (head == NULL) {
        printf("\nThe task list is empty.\n");
        return;
    }

    printf("\nAll tasks in the list:\n");
    while (current != NULL) {
        printf("ID: %d, Description: %s, Priority: %d, Status: %s\n",
               current->id, current->description, current->priority, current->status);
        current = current->next;
    }
}



int main() {
    task *head = NULL;
    const char *filename = "tasks.txt";
    head = loadTasksFromFile(filename);  // Load existing tasks from file

    int choice, id, priority;
    char description[100], status[20];
    while (1) {
        printf("\nTask Management System\n");
        printf("1. Add Task\n2. Delete Task\n3. Update Task Status\n4. Display All Tasks\n5. Display Task by status\n6. Display Task by priority\n7. Exit\n");
        printf("Enter your choice: ");
        do
        {scanf("%d", &choice);
        if (choice < 1 || choice > 7) {
                printf("\nInvalid choice! Please enter a value between 1 and 7.\n");
                }
         } while (choice < 1 || choice > 7);


        switch (choice) {
            case 1:
                printf("Enter Task ID: ");
                scanf("%d", &id);
                printf("Enter Task Description: ");
                scanf(" %[^\n]", description);

                priority = getValidPriority();
                printf("choose the task's status {'pending', 'in progress', 'completed'}: ");
                do {
                scanf(" %[^\n]", status);
                if (strcmp(status, "pending") != 0 && strcmp(status, "in progress") != 0 && strcmp(status, "completed") != 0) {
                printf("Invalid status. Please enter one of the following: 'pending', 'in progress', 'completed'.\n");
                 }
                } while (strcmp(status, "pending") != 0 && strcmp(status, "in progress") != 0 && strcmp(status, "completed") != 0);
                head = insertion(head, id, description, priority, status);
                saveTasksToFile(head);
                break;

            case 2:
                printf("Enter Task ID to delete: ");
                scanf("%d", &id);
                head = deleteTask(head, id);
                saveTasksToFile(head);
                break;

            case 3:
                printf("Enter Task ID to update: ");
                scanf("%d", &id);
                printf("Enter new status: ");
                scanf(" %[^\n]", status);
                updateStatus(head, id, status);
                saveTasksToFile(head);
                break;

            case 4:
                displayAllTasks(head);
                break;
            case 5:
            //DISPLAY by status
                if (head == NULL){
                printf("\nThe Task list is empty.\n");

                }else {
                 printf("You will See all of your  Tasks grouped by there Status : \n ");
                displayByStatus(head);}
              break;
            case 6:
            // Search tasks by priority
                if (head == NULL){
                printf("\nThe Task list is empty.\n");

                }else {
                printf("Enter the priority to search for: ");
                scanf("%d", &priority);
                searchByPriority(head, priority);}
              break;
            case 7:

                printf("Exiting program.\n");
                return 0;

            default:
                printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}
