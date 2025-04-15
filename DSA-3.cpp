#include <iostream>
using namespace std;

class node {
public:
    node* left;
    node* right;
    int data;
};

class BST {
public:
    node* root;
    node* temp;
    int value, op, key;
    int flag;

    BST() { // Constructor
        root = NULL;
        flag = 0;
    }

    void create();
    void inorder(node* root);
    void preorder(node* root);
    void postorder(node* root);
    void insert(node* root, node* temp);
    int search(node* root, int key);
    int minimum(node* root);
    int maximum(node* root);
    node* mirrorTree(node* root);
};

void BST::create() {
    do {
        temp = new node;
        cout << "Enter the data to store in tree: ";
        cin >> value;
        temp->data = value;
        temp->left = temp->right = NULL;

        if (root == NULL) {
            root = temp;
        } else {
            insert(root, temp); // Call insert
        }

        cout << "Do you want to continue? yes-1 no-0: ";
        cin >> op;
    } while (op == 1);
}

void BST::inorder(node* root) {
    if (root != NULL) {
        inorder(root->left);
        cout << root->data << " ";
        inorder(root->right);
    }
}

void BST::preorder(node* root) {
    if (root != NULL) {
        cout << root->data << " ";
        preorder(root->left);
        preorder(root->right);
    }
}

void BST::postorder(node* root) {
    if (root != NULL) {
        postorder(root->left);
        postorder(root->right);
        cout << root->data << " ";
    }
}

void BST::insert(node* root, node* temp) {
    // Left subtree contains only values less than root
    if (temp->data < root->data) {
        if (root->left == NULL)
            root->left = temp;
        else
            insert(root->left, temp);
    }
    // Right subtree contains only values greater than root
    else if (temp->data > root->data) {
        if (root->right == NULL)
            root->right = temp;
        else
            insert(root->right, temp);
    }
}

int BST::search(node* root, int key) {
    // Base case: if root is null, key is not found
    if (root == NULL)
        return 0;

    // If key is found at the current node
    if (key == root->data)
        return 1;

    // Search left or right subtree
    if (key < root->data)
        return search(root->left, key);
    else
        return search(root->right, key);
}

int BST::minimum(node* root) {
    if (root == NULL) {
        cout << "Tree is empty\n";
        return -1;
    }
    while (root->left != NULL)
        root = root->left;
    return root->data;
}

int BST::maximum(node* root) {
    if (root == NULL) {
        cout << "Tree is empty\n";
        return -1;
    }
    while (root->right != NULL)
        root = root->right;
    return root->data;
}

node* BST::mirrorTree(node* root) {
    if (root == NULL)
        return NULL;

    node* temp = root->left;
    root->left = mirrorTree(root->right);
    root->right = mirrorTree(temp);
    return root;
}

int main() {
    BST obj;
    int ch;

    while (1) {
        cout << "\n__MENU__";
        cout << "\n1. Create";
        cout << "\n2. Insert";
        cout << "\n3. Traverse using Inorder";
        cout << "\n4. Traverse using Preorder";
        cout << "\n5. Traverse using Postorder";
        cout << "\n6. Search";
        cout << "\n7. Minimum node";
        cout << "\n8. Maximum node";
        cout << "\n9. Mirror Tree";
        cout << "\n10. Exit";
        cout << "\nEnter your choice: ";
        cin >> ch;

        switch (ch) {
            case 1:
                obj.create();
                break;
            case 2:
                obj.create();
                break;
            case 3:
                cout << "Inorder Traversal: ";
                obj.inorder(obj.root);
                cout << endl;
                break;
            case 4:
                cout << "Preorder Traversal: ";
                obj.preorder(obj.root);
                cout << endl;
                break;
            case 5:
                cout << "Postorder Traversal: ";
                obj.postorder(obj.root);
                cout << endl;
                break;
            case 6:
                cout << "\nEnter the data to search in BST: ";
                cin >> obj.key;
                obj.flag = obj.search(obj.root, obj.key);
                if (obj.flag == 1)
                    cout << "Data found" << endl;
                else
                    cout << "Data not found" << endl;
                break;
            case 7:
                cout << "Minimum node value: " << obj.minimum(obj.root) << endl;
                break;
            case 8:
                cout << "Maximum node value: " << obj.maximum(obj.root) << endl;
                break;
            case 9:
                obj.root = obj.mirrorTree(obj.root);
                cout << "Tree mirrored successfully" << endl;
                break;
            case 10:
                exit(0);
                break;
            default:
                cout << "Invalid choice" << endl;
        }
    }
    return 0;
}

//OUTPUT:
__MENU__
1. Create
2. Insert
3. Traverse using inorder
4. Traverse using preorder
5. Traverse using postorder
6. Search

7. Minimum node
8. Maximum node
9. Mirror Tree
10. Exit
Enter your choice: 1
Enter the data to store in tree: 10
Do you want to continue? yes-1 no-0: 1
Enter the data to store in tree: 20
Do you want to continue? yes-1 no-0: 1
Enter the data to store in tree: 5
Do you want to continue? yes-1 no-0: 1
Enter the data to store in tree: 30
Do you want to continue? yes-1 no-0: 1
Enter the data to store in tree: 40
Do you want to continue? yes-1 no-0: 1
Enter the data to store in tree: 6
Do you want to continue? yes-1 no-0: 1
Enter the data to store in tree: 3
Do you want to continue? yes-1 no-0: 0

__MENU__
1. Create
2. Insert
3. Traverse using inorder
4. Traverse using preorder

5. Traverse using postorder
6. Search
7. Minimum node
8. Maximum node
9. Mirror Tree
10. Exit
Enter your choice: 2
Enter the data to store in tree: 2
Do you want to continue? yes-1 no-0: 0

__MENU__
1. Create
2. Insert
3. Traverse using inorder
4. Traverse using preorder
5. Traverse using postorder
6. Search
7. Minimum node
8. Maximum node
9. Mirror Tree
10. Exit
Enter your choice: 3
2 3 5 6 10 20 30 40
__MENU__
1. Create

2. Insert
3. Traverse using inorder
4. Traverse using preorder
5. Traverse using postorder
6. Search
7. Minimum node
8. Maximum node
9. Mirror Tree
10. Exit
Enter your choice: 4
10 5 3 2 6 20 30 40

__MENU__
1. Create
2. Insert
3. Traverse using inorder
4. Traverse using preorder
5. Traverse using postorder
6. Search
7. Minimum node
8. Maximum node
9. Mirror Tree
10. Exit
Enter your choice: 5
2 3 6 5 40 30 20 10

__MENU__
1. Create
2. Insert
3. Traverse using inorder
4. Traverse using preorder
5. Traverse using postorder
6. Search
7. Minimum node
8. Maximum node
9. Mirror Tree
10. Exit
Enter your choice: 6
Enter the data to be search in BST: 6
Data found

__MENU__
1. Create
2. Insert
3. Traverse using inorder
4. Traverse using preorder
5. Traverse using postorder
6. Search
7. Minimum node
8. Maximum node
9. Mirror Tree

10. Exit
Enter your choice: 6
Enter the data to be search in BST: 9
data not found

__MENU__
1. Create
2. Insert
3. Traverse using inorder
4. Traverse using preorder
5. Traverse using postorder
6. Search
7. Minimum node
8. Maximum node
9. Mirror Tree
10. Exit
Enter your choice: 7
Minimum node value: 2

__MENU__
1. Create
2. Insert
3. Traverse using inorder
4. Traverse using preorder
5. Traverse using postorder

6. Search
7. Minimum node
8. Maximum node
9. Mirror Tree
10. Exit
Enter your choice: 8
Maximum node value: 40

__MENU__
1. Create
2. Insert
3. Traverse using inorder
4. Traverse using preorder
5. Traverse using postorder
6. Search
7. Minimum node
8. Maximum node
9. Mirror Tree
10. Exit
Enter your choice: 9
Tree mirrored successfully

__MENU__
1. Create
2. Insert

3. Traverse using inorder
4. Traverse using preorder
5. Traverse using postorder
6. Search
7. Minimum node
8. Maximum node
9. Mirror Tree
10. Exit
Enter your choice: 10

=== Code Execution Successful ===
