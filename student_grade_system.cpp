#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>
using namespace std;

// Structure for student
struct Student {
    int id;
    string name;
    vector<double> grades;
    double average;
    Student* next;
};

// Head of the linked list
Student* head = nullptr;

// Function prototypes
void addStudent();
void displayStudents();
Student* searchStudent(int id);
void deleteStudent(int id);
void calculateStatistics();
void sortStudentsByAverage();
void saveToFile(const string& filename);
void loadFromFile(const string& filename);

// Function to add a new student
void addStudent() {
    Student* newStudent = new Student;
    cout << "Enter Student ID: ";
    cin >> newStudent->id;
    cout << "Enter Student Name: ";
    cin.ignore();
    getline(cin, newStudent->name);

    int numSubjects;
    cout << "Enter number of subjects: ";
    cin >> numSubjects;

    cout << "Enter grades: ";
    double sum = 0;
    for (int i = 0; i < numSubjects; i++) {
        double grade;
        cin >> grade;
        newStudent->grades.push_back(grade);
        sum += grade;
    }
    newStudent->average = sum / numSubjects;
    newStudent->next = nullptr;

    // Insert into linked list
    if (head == nullptr) {
        head = newStudent;
    } else {
        Student* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newStudent;
    }

    cout << "Student added successfully!" << endl;
}

// Function to display all students
void displayStudents() {
    if (head == nullptr) {
        cout << "No students to display." << endl;
        return;
    }

    Student* temp = head;
    while (temp != nullptr) {
        cout << "ID: " << temp->id
             << ", Name: " << temp->name
             << ", Average: " << fixed << setprecision(2) << temp->average
             << ", Grades: ";
        for (double grade : temp->grades) {
            cout << grade << " ";
        }
        cout << endl;
        temp = temp->next;
    }
}

// Function to search for a student by ID
Student* searchStudent(int id) {
    Student* temp = head;
    while (temp != nullptr) {
        if (temp->id == id) {
            return temp;
        }
        temp = temp->next;
    }
    return nullptr;
}

// Function to delete a student by ID
void deleteStudent(int id) {
    if (head == nullptr) {
        cout << "List is empty." << endl;
        return;
    }

    if (head->id == id) {
        Student* toDelete = head;
        head = head->next;
        delete toDelete;
        cout << "Student deleted successfully." << endl;
        return;
    }

    Student* temp = head;
    while (temp->next != nullptr && temp->next->id != id) {
        temp = temp->next;
    }

    if (temp->next == nullptr) {
        cout << "Student not found." << endl;
    } else {
        Student* toDelete = temp->next;
        temp->next = toDelete->next;
        delete toDelete;
        cout << "Student deleted successfully." << endl;
    }
}

// Function to calculate statistics
void calculateStatistics() {
    if (head == nullptr) {
        cout << "No students to analyze." << endl;
        return;
    }

    double totalAverage = 0;
    int count = 0;
    double highestAverage = -1;
    double lowestAverage = 101;
    string bestStudent, worstStudent;

    Student* temp = head;
    while (temp != nullptr) {
        totalAverage += temp->average;
        if (temp->average > highestAverage) {
            highestAverage = temp->average;
            bestStudent = temp->name;
        }
        if (temp->average < lowestAverage) {
            lowestAverage = temp->average;
            worstStudent = temp->name;
        }
        count++;
        temp = temp->next;
    }

    cout << "Class Average: " << totalAverage / count << endl;
    cout << "Top Performer: " << bestStudent << " with average " << highestAverage << endl;
    cout << "Lowest Performer: " << worstStudent << " with average " << lowestAverage << endl;
}

// Function to sort students by average grade
void sortStudentsByAverage() {
    if (head == nullptr || head->next == nullptr) {
        return;
    }

    bool swapped;
    do {
        swapped = false;
        Student* temp = head;
        Student* prev = nullptr;

        while (temp->next != nullptr) {
            if (temp->average < temp->next->average) {
                if (prev == nullptr) {
                    Student* next = temp->next;
                    temp->next = next->next;
                    next->next = temp;
                    head = next;
                } else {
                    Student* next = temp->next;
                    temp->next = next->next;
                    next->next = temp;
                    prev->next = next;
                }
                swapped = true;
            }
            prev = temp;
            temp = temp->next;
        }
    } while (swapped);
}

// Function to save data to a file
void saveToFile(const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "Failed to open file." << endl;
        return;
    }

    Student* temp = head;
    while (temp != nullptr) {
        file << temp->id << "," << temp->name << "," << temp->average << ",";
        for (size_t i = 0; i < temp->grades.size(); i++) {
            file << temp->grades[i];
            if (i != temp->grades.size() - 1) file << ";";
        }
        file << endl;
        temp = temp->next;
    }

    file.close();
    cout << "Data saved to file successfully!" << endl;
}

// Function to load data from a file
void loadFromFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Failed to open file." << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        Student* newStudent = new Student;

        getline(ss, line, ',');
        newStudent->id = stoi(line);

        getline(ss, newStudent->name, ',');

        getline(ss, line, ',');
        newStudent->average = stod(line);

        string grades;
        getline(ss, grades);
        stringstream gradeStream(grades);

        string grade;
        while (getline(gradeStream, grade, ';')) {
            newStudent->grades.push_back(stod(grade));
        }

        newStudent->next = nullptr;
        if (head == nullptr) {
            head = newStudent;
        } else {
            Student* temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newStudent;
        }
    }

    file.close();
    cout << "Data loaded from file successfully!" << endl;
}

// Main function
int main() {
    int choice;
    string filename = "students.txt";

    loadFromFile(filename);

    do {
        cout << "\nMenu:\n";
        cout << "1. Add Student\n";
        cout << "2. Display Students\n";
        cout << "3. Search Student\n";
        cout << "4. Delete Student\n";
        cout << "5. Calculate Statistics\n";
        cout << "6. Sort Students by Average\n";
        cout << "7. Save to File\n";
        cout << "8. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                displayStudents();
                break;
            case 3: {
                cout << "Enter Student ID to search: ";
                int id;
                cin >> id;
                Student* found = searchStudent(id);
                if (found) {
                    cout << "ID: " << found->id << ", Name: " << found->name
                         << ", Average: " << found->average << endl;
                } else {
                    cout << "Student not found." << endl;
                }
                break;
            }
            case 4:
                cout << "Enter Student ID to delete: ";
                int idToDelete;
                cin >> idToDelete;
                deleteStudent(idToDelete);
                break;
            case 5:
                calculateStatistics();
                break;
            case 6:
                sortStudentsByAverage();
                cout << "Students sorted by average grade." << endl;
                break;
            case 7:
                saveToFile(filename);
                break;
            case 8:
                cout << "Exiting program." << endl;
                saveToFile(filename);
                break;
            default:
                cout << "Invalid choice. Try again." << endl;
        }
    } while (choice != 8);

    return 0;
}
