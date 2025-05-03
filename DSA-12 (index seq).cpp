#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

const int MAX = 100;

// Define the Employee structure
struct Employee {
    int empID;
    char name[30];
    char designation[30];
    float salary;
};

// Define the Index structure (used to index the file)
struct Index {
    int empID;
    long position; // Position in the file where the record starts
};

Index indexList[MAX];
int indexCount = 0;

// Load the index from the file
void loadIndex() {
    ifstream fin("index.dat", ios::binary);
    indexCount = 0;
    while (fin.read((char*)&indexList[indexCount], sizeof(Index))) {
        indexCount++;
    }
    fin.close();
}

// Save the index to the file
void saveIndex() {
    ofstream fout("index.dat", ios::binary | ios::trunc);
    for (int i = 0; i < indexCount; i++) {
        fout.write((char*)&indexList[i], sizeof(Index));
    }
    fout.close();
}

// Search the index by empID
int searchIndex(int id) {
    for (int i = 0; i < indexCount; i++) {
        if (indexList[i].empID == id) {
            return i; // Found
        }
    }
    return -1; // Not found
}

// Add a new employee
void addEmployee() {
    Employee emp;
    cout << "Enter Employee ID: ";
    cin >> emp.empID;

    if (searchIndex(emp.empID) != -1) {
        cout << "Employee already exists!\n";
        return;
    }

    cin.ignore();
    cout << "Enter Name: ";
    cin.getline(emp.name, 30);
    cout << "Enter Designation: ";
    cin.getline(emp.designation, 30);
    cout << "Enter Salary: ";
    cin >> emp.salary;

    ofstream fout("employee.dat", ios::binary | ios::app);
    long pos = fout.tellp(); // get current position
    fout.write((char*)&emp, sizeof(emp));
    fout.close();

    indexList[indexCount].empID = emp.empID;
    indexList[indexCount].position = pos;
    indexCount++;

    saveIndex();
    cout << "Employee added successfully.\n";
}

// Display employee details by ID
void displayEmployee() {
    int id;
    cout << "Enter Employee ID to display: ";
    cin >> id;

    int idx = searchIndex(id);
    if (idx == -1) {
        cout << "Employee not found.\n";
        return;
    }

    ifstream fin("employee.dat", ios::binary);
    Employee emp;
    fin.seekg(indexList[idx].position); // Go to the position in the file
    fin.read((char*)&emp, sizeof(emp));
    fin.close();

    cout << "\nEmployee Found:\n";
    cout << "ID: " << emp.empID << "\n";
    cout << "Name: " << emp.name << "\n";
    cout << "Designation: " << emp.designation << "\n";
    cout << "Salary: " << emp.salary << "\n";
}

// Delete an employee by ID
void deleteEmployee() {
    int id;
    cout << "Enter Employee ID to delete: ";
    cin >> id;

    int idx = searchIndex(id);
    if (idx == -1) {
        cout << "Employee not found.\n";
        return;
    }

    ifstream fin("employee.dat", ios::binary);
    ofstream fout("temp.dat", ios::binary);
    Employee emp;
    long newPos = 0;
    int newIndexCount = 0;
    Index newIndexList[MAX];

    while (fin.read((char*)&emp, sizeof(emp))) {
        if (emp.empID != id) {
            fout.write((char*)&emp, sizeof(emp));
            newIndexList[newIndexCount].empID = emp.empID;
            newIndexList[newIndexCount].position = newPos;
            newPos += sizeof(emp);
            newIndexCount++;
        }
    }

    fin.close();
    fout.close();

    remove("employee.dat");
    rename("temp.dat", "employee.dat");

    for (int i = 0; i < newIndexCount; i++) {
        indexList[i] = newIndexList[i];
    }
    indexCount = newIndexCount;
    saveIndex();

    cout << "Employee deleted successfully.\n";
}

// Main menu to interact with the program
int main() {
    loadIndex();
    int choice;

    do {
        cout << "\n1. Add Employee\n2. Display Employee\n3. Delete Employee\n4. Exit\nEnter choice: ";
        cin >> choice;
        switch (choice) {
            case 1: addEmployee(); break;
            case 2: displayEmployee(); break;
            case 3: deleteEmployee(); break;
            case 4: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice!\n";
        }
    } while (choice != 4);

    return 0;
}
