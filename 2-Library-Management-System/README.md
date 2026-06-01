# C Data Structures & Web UI Projects

This repository contains two academic mini-projects demonstrating the practical use of fundamental data structures (Linked Lists, Stacks, Queues) implemented in C, along with simple HTML/JS frontend interfaces.

## 1. Task Management System
* **Backend (C):** Manages tasks using a custom **Linked List**, featuring operations like insertion by priority, status updates, searching, and persistent file storage (`tasks.txt`).
* **Frontend (HTML/JS):** A clean interface (`uipg1.html`) simulating the system behavior.

## 2. Library Book Management System
* **Backend (C):** A modular system (`library.c`, `stack.c`, `queue.c`) that utilizes:
  * **Stacks:** To handle recently returned books.
  * **Queues:** To handle waitlists/borrow requests for unavailable books.
* **Frontend (HTML/JS):** A dedicated dashboard (`uipg2.html`) to visualize the library operations.

## How to Run the C Programs
Compile using GCC:
```bash
# For Task Management
gcc main.c -o task_manager
./task_manager

# For Library Management
gcc main.c library.c stack.c queue.c -o library_manager
./library_manager