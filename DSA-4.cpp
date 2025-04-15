#include <iostream>
#include <string>
#include <stack>
using namespace std;

struct Node {
    char data;
    Node* left;
    Node* right;

    Node(char c) {
        data = c;
        left = right = nullptr;
    }
};

bool isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}

Node* ExpTree(const string& prefix) {
    stack<Node*> s;
    for (int i = prefix.length() - 1; i >= 0; i--) {
        char ch = prefix[i];
        if (isalpha(ch)) {
            s.push(new Node(ch));
        } else if (isOperator(ch)) {
            Node* newNode = new Node(ch);
            if (!s.empty()) {
                newNode->left = s.top(); s.pop();
            }
            if (!s.empty()) {
                newNode->right = s.top(); s.pop();
            }
            s.push(newNode);
        }
    }
    return s.empty() ? nullptr : s.top();
}

void postorder(Node* root) {
    if (root == nullptr) return;

    stack<Node*> s;
    stack<char> rs;

    s.push(root);
    while (!s.empty()) {
        Node* curr = s.top(); s.pop();
        rs.push(curr->data);

        if (curr->left) s.push(curr->left);
        if (curr->right) s.push(curr->right);
    }

    while (!rs.empty()) {
        cout << rs.top() << " ";
        rs.pop();
    }
    cout << endl;
}

void deletenode(Node* root) {
    if (root == nullptr) return;

    stack<Node*> s;
    s.push(root);

    while (!s.empty()) {
        Node* t = s.top(); s.pop();

        if (t->left) s.push(t->left);
        if (t->right) s.push(t->right);

        delete t;
    }
}

int main() {
    Node* root = nullptr;
    int choice;

    do {
        cout << "\nMENU" << endl;
        cout << "1. Postorder" << endl;
        cout << "2. Delete Tree" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                string prefix;
                cout << "Enter prefix expression: ";
                cin >> prefix;
                root = ExpTree(prefix);
                cout << "Postorder: ";
                postorder(root);
                break;
            }
            case 2: {
                deletenode(root);
                root = nullptr;
                cout << "Deleted nodes successfully" << endl;
                break;
            }
            case 3:
                cout << "Exiting." << endl;
                break;
            default:
                cout << "Invalid choice" << endl;
        }
    } while (choice != 3);

    return 0;
}

//OUTPUT:
Menu:
1. Add Student
2. Delete Student
3. Display Student Information
4. Exit
Enter your choice: 1
Enter the roll number of the student: 34
Enter the name of the student: Manali
Enter the division of the student: B
Enter the address of the student: Shahunagar
Student data added successfully.
Menu:
1. Add Student
2. Delete Student
3. Display Student Information
4. Exit
Enter your choice: 3
Enter the roll number of the student to display: 34
Student Found:
ROLL NO: 101
NAME: Manali
DIVISION: B
ADDRESS: Shahunagar
Menu:
1. Add Student
2. Delete Student

3. Display Student Information
4. Exit
Enter your choice: 2
Enter the roll number of student whose data is to be deleted: 34
Student with roll number 34 deleted.
Student data has been successfully deleted.
Menu:
1. Add Student
2. Delete Student
3. Display Student Information
4. Exit
Enter your choice: 3
Enter the roll number of the student to display: 34
Student with roll number 34 not found.
Menu:
1. Add Student
2. Delete Student
3. Display Student Information
4. Exit
Enter your choice: 4
Exiting program.
