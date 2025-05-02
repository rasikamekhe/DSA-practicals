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

