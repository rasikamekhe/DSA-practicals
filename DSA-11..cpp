#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Student {
    int roll_no;
    string name;
    char div;
    string address;

    void writedata(ofstream &out) {
        out << "ROLL NO: " << roll_no << endl;
        out << "NAME: " << name << endl;
        out << "DIVISION: " << div << endl;
        out << "ADDRESS: " << address << endl;
    }

    void readdata(ifstream &in) {
        in >> roll_no;
        in.ignore();
        getline(in, name);
        in >> div;
        in.ignore();
        getline(in, address);
    }
};

void add() {
    ofstream out("student.dat", ios::app);
    if (!out) {
        cout << "Error! Can't open the file." << endl;
        return;
    }

    Student s;
    cout << "Enter the roll number of the student: ";
    cin >> s.roll_no;
    cin.ignore();
    cout << "Enter the name of the student: ";
    getline(cin, s.name);
    cout << "Enter the division of the student: ";
    cin >> s.div;
    cin.ignore();
    cout << "Enter the address of the student: ";
    getline(cin, s.address);

    s.writedata(out);
    out.close();
    cout << "Student data added successfully." << endl;
}

void deletestudent() {
    int del_roll;
    cout << "Enter the roll number of student whose data is to be deleted: ";
    cin >> del_roll;

    ifstream in("student.dat");
    if (!in) {
        cout << "Error! Can't open the file for reading." << endl;
        return;
    }

    ofstream out("temp.dat");
    if (!out) {
        cout << "Error! Can't create the temporary file." << endl;
        return;
    }

    Student s;
    bool found = false;

    while (in >> s.roll_no) {
        in.ignore();
        getline(in, s.name);
        in >> s.div;
        in.ignore();
        getline(in, s.address);

        if (s.roll_no == del_roll) {
            found = true;
            cout << "Student with roll number " << del_roll << " deleted." << endl;
            continue;
        }

        s.writedata(out);
    }

    in.close();
    out.close();

    if (found) {
        remove("student.dat");
        rename("temp.dat", "student.dat");
        cout << "Student data has been successfully deleted." << endl;
    } else {
        cout << "No student found with roll number " << del_roll << endl;
        remove("temp.dat");
    }
}

void display() {
    int display_roll;
    cout << "Enter the roll number of the student to display: ";
    cin >> display_roll;

    ifstream in("student.dat");
    if (!in) {
        cout << "Error! Can't open the file for reading." << endl;
        return;
    }

    Student s;
    bool found = false;

    while (in >> s.roll_no) {
        in.ignore();
        getline(in, s.name);
        in >> s.div;
        in.ignore();
        getline(in, s.address);

        if (s.roll_no == display_roll) {
            cout << "Student Found:" << endl;
            cout << "ROLL NO: " << s.roll_no << endl;
            cout << "NAME: " << s.name << endl;
            cout << "DIVISION: " << s.div << endl;
            cout << "ADDRESS: " << s.address << endl;
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Student with roll number " << display_roll << " not found." << endl;
    }

    in.close();
}

int main() {
    int choice = 0;
    do {
        cout << "\nMenu:\n";
        cout << "1. Add Student\n";
        cout << "2. Delete Student\n";
        cout << "3. Display Student Information\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                add();
                break;
            case 2:
                deletestudent();
                break;
            case 3:
                display();
                break;
            case 4:
                cout << "Exiting program." << endl;
                break;
            default:
                cout << "Invalid choice! Please enter a valid option." << endl;
        }
    } while (choice != 4);

    return 0;
}
