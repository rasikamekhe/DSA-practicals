#include <iostream>      // For input-output operations
#include <fstream>       // For file operations
#include <string>        // For using the string class
using namespace std;     // So we don't need to prefix std:: before standard classes

// Structure to store employee data
struct Employee {
    int Employee_ID;     // Unique identifier for each employee
    int salary;          // Employee's salary
    string name;         // Employee's name
    string designation;  // Employee's job title

    // Function to write employee data to a file
    void writedata(ofstream &out) {
        out << Employee_ID << endl;
        out << name << endl;
        out << designation << endl;
        out << salary << endl;
    }

    // Function to read employee data from a file
    void readdata(ifstream &in) {
        in >> Employee_ID;
        in.ignore();              // Ignore newline after ID
        getline(in, name);        // Read full name (can include spaces)
        getline(in, designation); // Read full designation
        in >> salary;             // Read salary
    }
};

// Function to add a new employee to the file
void add() {
    ofstream out("employee.dat", ios::app); // Open file in append mode
    if (!out) {                             // Check if file opened successfully
        cout << "Error! Can't open the file." << endl;
        return;
    }

    Employee e;                             // Create an employee object
    cout << "Enter the Employee ID: ";
    cin >> e.Employee_ID;
    cin.ignore();                           // Ignore newline character
    cout << "Enter the Employee Name: ";
    getline(cin, e.name);
    cout << "Enter the Employee Designation: ";
    getline(cin, e.designation);
    cout << "Enter the Employee Salary: ";
    cin >> e.salary;

    e.writedata(out);                       // Write data to file
    out.close();                            // Close the file
    cout << "Employee data added successfully." << endl;
}

// Function to delete an employee record
void deleteEmployee() {
    int del_ID;
    cout << "Enter the Employee ID whose data is to be deleted: ";
    cin >> del_ID;

    ifstream in("employee.dat");            // Open original file for reading
    if (!in) {
        cout << "Error! Can't open the file for reading." << endl;
        return;
    }

    ofstream out("temp.dat");               // Temporary file for writing remaining data
    if (!out) {
        cout << "Error! Can't create the temporary file." << endl;
        return;
    }

    Employee e;
    bool found = false;

    while (in) {
        e.readdata(in);                     // Read each record
        if (!in) break;                     // Stop at end of file

        if (e.Employee_ID == del_ID) {      // If ID matches, skip writing it
            found = true;
            cout << "Employee with ID " << del_ID << " deleted." << endl;
            continue;                       // Skip writing to temp file
        }
        e.writedata(out);                   // Write other records to temp file
    }

    in.close();                             // Close both files
    out.close();

    if (found) {
        remove("employee.dat");             // Delete original file
        rename("temp.dat", "employee.dat"); // Rename temp file to original file
        cout << "Employee data has been successfully deleted." << endl;
    } else {
        cout << "No employee found with ID " << del_ID << endl;
        remove("temp.dat");                 // Clean up temp file if not found
    }
}

// Function to display a specific employee's data
void display() {
    int display_ID;
    cout << "Enter the Employee ID to display: ";
    cin >> display_ID;

    ifstream in("employee.dat");            // Open file for reading
    if (!in) {
        cout << "Error! Can't open the file for reading." << endl;
        return;
    }

    Employee e;
    bool found = false;

    while (in) {
        e.readdata(in);                     // Read each employee
        if (!in) break;

        if (e.Employee_ID == display_ID) {  // If ID matches, display info
            cout << "Employee Found:" << endl;
            cout << "Employee ID: " << e.Employee_ID << endl;
            cout << "Name: " << e.name << endl;
            cout << "Designation: " << e.designation << endl;
            cout << "Salary: " << e.salary << endl;
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Employee with ID " << display_ID << " not found." << endl;
    }

    in.close();                             // Close file
}

// Function to update an existing employee's data
void updateEmployee() {
    int update_ID;
    cout << "Enter the Employee ID whose data is to be updated: ";
    cin >> update_ID;

    ifstream in("employee.dat");            // Open file for reading
    if (!in) {
        cout << "Error! Can't open the file for reading." << endl;
        return;
    }

    ofstream out("temp.dat");               // Temporary file to store updated data
    if (!out) {
        cout << "Error! Can't create the temporary file." << endl;
        return;
    }

    Employee e;
    bool found = false;

    while (in) {
        e.readdata(in);                     // Read each employee
        if (!in) break;

        if (e.Employee_ID == update_ID) {
            found = true;
            cin.ignore();                   // Flush newline

            cout << "Enter new Name: ";
            string newName;
            getline(cin, newName);
            if (!newName.empty()) {
                e.name = newName;
            }

            cout << "Enter new Designation : ";
            string newDesignation;
            getline(cin, newDesignation);
            if (!newDesignation.empty()) {
                e.designation = newDesignation;
            }

            cout << "Enter new Salary : ";
            int newSalary;
            cin >> newSalary;
            e.salary = newSalary;

            cout << "Employee data updated." << endl;
        }

        e.writedata(out);                   // Write updated or unchanged data
    }

    in.close();
    out.close();

    if (found) {
        remove("employee.dat");             // Delete original file
        rename("temp.dat", "employee.dat"); // Replace with updated file
        cout << "Employee data has been successfully updated." << endl;
    } else {
        cout << "No employee found with ID " << update_ID << endl;
        remove("temp.dat");                 // Remove temp if no update was made
    }
}

// Main menu-driven function
int main() {
    int choice = 0;

    do {
        cout << "\nMenu:\n";
        cout << "1. Add Employee\n";
        cout << "2. Delete Employee\n";
        cout << "3. Display Employee Information\n";
        cout << "4. Update Employee Information\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        // Call the corresponding function based on user choice
        switch (choice) {
            case 1:
                add();
                break;
            case 2:
                deleteEmployee();
                break;
            case 3:
                display();
                break;
            case 4:
                updateEmployee();
                break;
            case 5:
                cout << "Exiting program." << endl;
                break;
            default:
                cout << "Invalid choice! Please enter a valid option." << endl;
        }

    } while (choice != 5); // Loop until user chooses to exit

    return 0;
}

//OUTPUT:
Menu:
1. Add Employee
2. Delete Employee
3. Display Employee Information
4. Update Employee Information
5. Exit
Enter your choice: 1
Enter the Employee ID: 123
Enter the Employee Name: Manali
Enter the Employee Designation: ABC
Enter the Employee Salary: 7800
Employee data added successfully.
Menu:
1. Add Employee
2. Delete Employee
3. Display Employee Information
4. Update Employee Information
5. Exit
Enter your choice: 1
Enter the Employee ID: 456
Enter the Employee Name: Rohini
Enter the Employee Designation: DEF
Enter the Employee Salary: 6700
Employee data added successfully.
Menu:
1. Add Employee
2. Delete Employee
3. Display Employee Information
4. Update Employee Information
5. Exit
Enter your choice: 4
Enter the Employee ID whose data is to be updated: 123
Enter new Name: Rasika
Enter new Designation : GHI
Enter new Salary : 9800
Employee data updated.
Menu:
1. Add Employee
2. Delete Employee
3. Display Employee Information
4. Update Employee Information
5. Exit
Enter your choice: 3
Enter the Employee ID to display: 123
Employee Found:
Employee ID: 123
Name: Rasika
Designation: GHI
Salary: 9800
Menu:
1. Add Employee
2. Delete Employee
3. Display Employee Information
4. Update Employee Information
5. Exit
Enter your choice: 5
Exiting program.
