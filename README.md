# Student Management System

## Overview
The **Student Management System** is a C++ program that allows users to manage student records using a linked list. The program provides functionality to add, display, search, delete, calculate statistics, sort students, and save or load data from a file.

---

## Features

1. **Add a New Student**:
   - Allows the user to input a student's ID, name, grades, and calculates the average grade.

2. **Display All Students**:
   - Displays all students in the system along with their details.

3. **Search for a Student**:
   - Searches for a student by their ID and displays their information.

4. **Delete a Student**:
   - Deletes a student record by their ID.

5. **Calculate Statistics**:
   - Calculates and displays:
     - Class average grade.
     - Top-performing student.
     - Lowest-performing student.

6. **Sort Students by Average**:
   - Sorts all students in descending order of their average grade.

7. **Save and Load Data**:
   - Saves all student data to a file (`students.txt` by default).
   - Loads student data from a file at program startup.

8. **Data Persistence**:
   - Ensures that all data is saved to a file upon exiting the program.

---

## How to Use

### Prerequisites:
- A C++ compiler (e.g., `g++`).

### Steps:
1. Clone the repository or copy the source code into a file named `StudentManagementSystem.cpp`.
2. Compile the program:
   ```bash
   g++ -o StudentManagementSystem StudentManagementSystem.cpp
