#include <iostream>      
#include <fstream>       
#include <cstring>       
using namespace std;

const int MAX = 100;     // Maximum number of employees we can store in index

// Structure to hold employee information
struct Employee {
    int empID;                  
    char name[30];             
    char designation[30];       
    float salary;               
};

// Structure to hold index (empID + position in file)
struct Index {
    int empID;          // Employee ID (used to search)
    long position;      // Position of the employee record in the file
};

Index indexList[MAX];       // Array to hold index entries
int indexCount = 0;         // Number of records in index

// Load index data from index.dat file into indexList array
void loadIndex() {
    ifstream fin("index.dat", ios::binary);  // Open index file in binary mode
    indexCount = 0;                          // Reset index count

    // Read each index entry from file and store in array
    while (fin.read((char*)&indexList[indexCount], sizeof(Index))) {
        indexCount++;                       // Increase count after each successful read
    }

    fin.close();                            // Close the file
}

// Save the indexList array back into index.dat file
void saveIndex() {
    ofstream fout("index.dat", ios::binary | ios::trunc); // Open index file for writing (truncate)
    
    // Write all index entries to file
    for (int i = 0; i < indexCount; i++) {
        fout.write((char*)&indexList[i], sizeof(Index));
    }

    fout.close();                           // Close the file
}

// Search for an employee in the index by ID
int searchIndex(int id) {
    for (int i = 0; i < indexCount; i++) {
        if (indexList[i].empID == id) {     // If ID matches, return index
            return i;
        }
    }
    return -1;                              // Not found
}

// Function to add a new employee
void addEmployee() {
    Employee emp;                           // Create employee variable

    cout << "Enter Employee ID: ";
    cin >> emp.empID;                       // Input employee ID

    if (searchIndex(emp.empID) != -1) {     // Check if employee already exists
        cout << "Employee already exists!\n";
        return;
    }

    cin.ignore();                           // Clear input buffer
    cout << "Enter Name: ";
    cin.getline(emp.name, 30);              // Input name
    cout << "Enter Designation: ";
    cin.getline(emp.designation, 30);       // Input designation
    cout << "Enter Salary: ";
    cin >> emp.salary;                      // Input salary

    // Open file in append mode to add employee data at end
    ofstream fout("employee.dat", ios::binary | ios::app);
    long pos = fout.tellp();                // Get position where record will be written
    fout.write((char*)&emp, sizeof(emp));   // Write employee data to file
    fout.close();                           // Close file

    // Add entry to index
    indexList[indexCount].empID = emp.empID;
    indexList[indexCount].position = pos;   // Store the file position
    indexCount++;                           // Increase index count

    saveIndex();                            // Save index file
    cout << "Employee added successfully.\n";
}

// Function to display employee info by ID
void displayEmployee() {
    int id;
    cout << "Enter Employee ID to display: ";
    cin >> id;                              // Input ID to search

    int idx = searchIndex(id);              // Search ID in index
    if (idx == -1) {                        // If not found
        cout << "Employee not found.\n";
        return;
    }

    ifstream fin("employee.dat", ios::binary); // Open employee file
    Employee emp;

    // Move to the position where record is stored
    fin.seekg(indexList[idx].position);    
    fin.read((char*)&emp, sizeof(emp));     // Read the employee record
    fin.close();                            // Close file

    // Display the employee information
    cout << "\nEmployee Found:\n";
    cout << "ID: " << emp.empID << "\n";
    cout << "Name: " << emp.name << "\n";
    cout << "Designation: " << emp.designation << "\n";
    cout << "Salary: " << emp.salary << "\n";
}

// Function to delete employee by ID
void deleteEmployee() {
    int id;
    cout << "Enter Employee ID to delete: ";
    cin >> id;

    int idx = searchIndex(id);              // Search employee
    if (idx == -1) {
        cout << "Employee not found.\n";
        return;
    }

    ifstream fin("employee.dat", ios::binary);     // Open original file for reading
    ofstream fout("temp.dat", ios::binary);        // Create temp file to copy valid data
    Employee emp;
    long newPos = 0;                               // Position in new file
    int newIndexCount = 0;                         // New index counter
    Index newIndexList[MAX];                       // Temp index array

    // Read all employees and skip the one to be deleted
    while (fin.read((char*)&emp, sizeof(emp))) {
        if (emp.empID != id) {
            fout.write((char*)&emp, sizeof(emp));              // Write to temp file
            newIndexList[newIndexCount].empID = emp.empID;     // Add to new index
            newIndexList[newIndexCount].position = newPos;
            newPos += sizeof(emp);                             // Update position
            newIndexCount++;
        }
    }

    fin.close();                                // Close old file
    fout.close();                               // Close temp file

    remove("employee.dat");                     // Delete old file
    rename("temp.dat", "employee.dat");         // Rename temp to original

    // Copy new index to original
    for (int i = 0; i < newIndexCount; i++) {
        indexList[i] = newIndexList[i];
    }

    indexCount = newIndexCount;                 // Update index count
    saveIndex();                                // Save updated index

    cout << "Employee deleted successfully.\n";
}

// Main function: displays menu to user
int main() {
    loadIndex();                                // Load index when program starts
    int choice;

    do {
        // Display menu options
        cout << "\n1. Add Employee\n2. Display Employee\n3. Delete Employee\n4. Exit\nEnter choice: ";
        cin >> choice;

        // Call corresponding function
        switch (choice) {
            case 1: addEmployee(); break;
            case 2: displayEmployee(); break;
            case 3: deleteEmployee(); break;
            case 4: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice!\n";
        }
    } while (choice != 4);                      // Repeat until user chooses to exit

    return 0;
}
