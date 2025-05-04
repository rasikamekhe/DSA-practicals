#include <iostream>
#include <algorithm>
#include <cstdlib>
using namespace std;

// Node class representing a word and its meaning
class node {
public:
    string word, meaning;
    int ht;    // height 
    node* left, * right;
};

// AVL Tree class
class AVL {
public:
    node* root;
    AVL() { root = NULL; }

    node* insert(node*, string, string);
    node* deleteNode(node*, string);
    void preorder(node*);
    void inorder(node*);
    node* RotateRight(node*);
    node* RotateLeft(node*);
    node* RR(node*);
    node* LL(node*);
    node* LR(node*);
    node* RL(node*);
    int height(node*);
    int BF(node*);
    void search(node*, string);
    void modify(node*, string);
    node* findMin(node*);
};

// Calculate height of node
int AVL::height(node* temp) {
    if (temp == NULL)
        return 0;
    return 1 + max(height(temp->left), height(temp->right));    // 1 + max height of left or right subtree
}

// Calculate Balance Factor
int AVL::BF(node* temp) {
    if (temp == NULL)
        return 0;
    return height(temp->left) - height(temp->right); // difference of heights
}

// Right Rotation
node* AVL::RotateRight(node* parent) {
    node* temp = parent->left;
    parent->left = temp->right;    // after rotation, right child of temp becomes left child of parent as per BST 
    temp->right = parent;

    parent->ht = height(parent);
    temp->ht = height(temp);

    return temp; // new root after rotation
}

// Left Rotation
node* AVL::RotateLeft(node* parent) {
    node* temp = parent->right;
    parent->right = temp->left;          //  // after rotation, left child of temp becomes right child of parent as per BST 
    temp->left = parent;

    parent->ht = height(parent);
    temp->ht = height(temp);

    return temp; // new root after rotation
}

// Right-Right case
node* AVL::RR(node* T) {
    return RotateLeft(T);
}

// Left-Left case
node* AVL::LL(node* T) {
    return RotateRight(T);
}

// Left-Right case
node* AVL::LR(node* T) {
    T->left = RotateLeft(T->left);
    return RotateRight(T);
}

// Right-Left case
node* AVL::RL(node* T) {
    T->right = RotateRight(T->right);
    return RotateLeft(T);
}

// Insert word and balance the tree
node* AVL::insert(node* temp, string str_w, string str_m) {
    if (temp == NULL) {
        temp = new node;
        temp->word = str_w;
        temp->meaning = str_m;
        temp->left = temp->right = NULL;
    }
    else {
        if (str_w.compare(temp->word) > 0) {
            temp->right = insert(temp->right, str_w, str_m); // go to right subtree

            // Check balance after insertion
            if (BF(temp) == -2) {
                if (temp->right && str_w.compare(temp->right->word) > 0)   // Checks if right child exists and new word is greater than it (RR case)
                    temp = RR(temp);
                else
                    temp = RL(temp);
            }
        }
        else {
            temp->left = insert(temp->left, str_w, str_m); // go to left subtree

            // Check balance after insertion
            if (BF(temp) == 2) {
                if (temp->left && str_w.compare(temp->left->word) < 0)   // // Checks if left child exists and new word is less than it (LL case)
                    temp = LL(temp);
                else
                    temp = LR(temp);
            }
        }
    }

    temp->ht = height(temp); // update height after insertion
    return temp;
}

// Find the node with the minimum word (leftmost node) i.e: inorder successor
node* AVL::findMin(node* root) {
    while (root->left != NULL)
        root = root->left;
    return root;
}

// Delete a word and balance the tree
node* AVL::deleteNode(node* root, string str_w) {
    if (root == NULL)
        return NULL;

    if (str_w < root->word)
        root->left = deleteNode(root->left, str_w);
    else if (str_w > root->word)
        root->right = deleteNode(root->right, str_w);
    else {
        // Node found
        if (root->left == NULL) {
            node* temp = root->right;
            delete root;
            return temp;
        }
        else if (root->right == NULL) {
            node* temp = root->left;
            delete root;
            return temp;
        }
        else {
            // Node with two children - use inorder successor
            node* temp = findMin(root->right);
            root->word = temp->word;
            root->meaning = temp->meaning;
            root->right = deleteNode(root->right, temp->word);
        }
    }

    root->ht = height(root); // update height after deletion
    return root;
}

// Display in preorder traversal
void AVL::preorder(node* root) {
    if (root != NULL) {
        cout << root->word << " : " << root->meaning << " (BF=" << BF(root) << ")\n";
        preorder(root->left);
        preorder(root->right);
    }
}

// Display in inorder traversal (sorted dictionary)
void AVL::inorder(node* root) {
    if (root != NULL) {
        inorder(root->left);
        cout << root->word << " : " << root->meaning << " (BF=" << BF(root) << ")\n";
        inorder(root->right);
    }
}

// Search for a word
void AVL::search(node* root, string str_w) {
    if (root == NULL) {
        cout << "Word not found" << endl;
        return;
    }

    if (str_w.compare(root->word) < 0)
        search(root->left, str_w);
    else if (str_w.compare(root->word) > 0)
        search(root->right, str_w);
    else {
        cout << "Word: " << root->word << "\nMeaning: " << root->meaning << endl;
    }
}

// Modify the meaning of a word
void AVL::modify(node* root, string str_w) {
    if (root == NULL) {
        cout << "Word not found" << endl;
        return;
    }

    if (str_w.compare(root->word) < 0)
        modify(root->left, str_w);
    else if (str_w.compare(root->word) > 0)
        modify(root->right, str_w);
    else {
        cout << "Enter new meaning: ";
        cin.ignore();
        getline(cin, root->meaning);
    }
}

// Main function to interact with the dictionary
int main() {
    AVL Tree;
    int ch;
    string str1, str2;

    cout << "\t--- DICTIONARY USING AVL TREE ---\t" << endl;

    while (true) {
        cout << "\n1. Add word\n2. Display (Inorder/Preorder)\n3. Delete word\n4. Search word\n5. Modify meaning\n6. Maximum Comparisons\n7. Exit" << endl;
        cout << "Enter choice: ";
        cin >> ch;
        cin.ignore();

        switch (ch) {
        case 1:
            cout << "Enter word: ";
            cin >> str1;
            cin.ignore();
            cout << "Enter meaning: ";
            getline(cin, str2);
            Tree.root = Tree.insert(Tree.root, str1, str2);
            break;

        case 2:
            cout << "\nPreorder:\n";
            Tree.preorder(Tree.root);
            cout << "\nInorder:\n";
            Tree.inorder(Tree.root);
            break;

        case 3:
            cout << "Enter word to delete: ";
            cin >> str1;
            Tree.root = Tree.deleteNode(Tree.root, str1);
            break;

        case 4:
            cout << "Enter word to search: ";
            cin >> str1;
            Tree.search(Tree.root, str1);
            break;

        case 5:
            cout << "Enter word to modify: ";
            cin >> str1;
            Tree.modify(Tree.root, str1);
            break;

        case 6:
            cout << "Maximum comparisons required to search = Height = " << Tree.height(Tree.root) << endl;
            break;

        case 7:
            exit(0);

        default:
            cout << "Invalid choice!" << endl;
        }
    }

    return 0;
}





//OUTPUT:
OPERATIONS ON AVL TREE

1. Create tree
2. Add word
3. Display tree
4. Delete word
5. Search word
6. Modify meaning
7. Exit
Enter choice: 1
Enter word: cat
Enter meaning: small animal

1. Create tree
2. Add word
3. Display tree
4. Delete word
5. Search word
6. Modify meaning
7. Exit
Enter choice: 2
Enter word: dog
Enter meaning: another pet

1. Create tree

2. Add word
3. Display tree
4. Delete word
5. Search word
6. Modify meaning
7. Exit
Enter choice: 2
Enter word: apple
Enter meaning: fruit

1. Create tree
2. Add word
3. Display tree
4. Delete word
5. Search word
6. Modify meaning
7. Exit
Enter choice: 2
Enter word: shirt
Enter meaning: cloth

1. Create tree
2. Add word
3. Display tree
4. Delete word
5. Search word

6. Modify meaning
7. Exit
Enter choice: 3

Preorder:
cat : small animal (Bf=-1)
apple : fruit (Bf=0)
dog : another pet (Bf=-1)
shirt : cloth (Bf=0)

Inorder:
apple : fruit (Bf=0)
cat : small animal (Bf=-1)
dog : another pet (Bf=-1)
shirt : cloth (Bf=0)

1. Create tree
2. Add word
3. Display tree
4. Delete word
5. Search word
6. Modify meaning
7. Exit
Enter choice: 4
Enter word to delete: cat

1. Create tree
2. Add word
3. Display tree
4. Delete word
5. Search word
6. Modify meaning
7. Exit
Enter choice: 3

Preorder:
dog : another pet (Bf=0)
apple : fruit (Bf=0)
shirt : cloth (Bf=0)

Inorder:
apple : fruit (Bf=0)
dog : another pet (Bf=0)
shirt : cloth (Bf=0)

1. Create tree
2. Add word
3. Display tree
4. Delete word
5. Search word
6. Modify meaning
7. Exit

Enter choice: 5
Enter word to search: shirt
Word: shirt
Meaning: cloth

1. Create tree
2. Add word
3. Display tree
4. Delete word
5. Search word
6. Modify meaning
7. Exit
Enter choice: 6
Enter word to modify: dog
Enter new meaning: animal

1. Create tree
2. Add word
3. Display tree
4. Delete word
5. Search word
6. Modify meaning
7. Exit
Enter choice: 3

Preorder:

dog : animal (Bf=0)
apple : fruit (Bf=0)
shirt : cloth (Bf=0)

Inorder:
apple : fruit (Bf=0)
dog : animal (Bf=0)
shirt : cloth (Bf=0)

1. Create tree
2. Add word
3. Display tree
4. Delete word
5. Search word
6. Modify meaning
7. Exit
Enter choice: 7

...Program finished with exit code 0
Press ENTER to exit console.
