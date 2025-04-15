#include <iostream>
#include <algorithm>
#include <cstdlib>
using namespace std;

class node {
public:
    string word, meaning;
    int ht;
    node* left, * right;
};

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

// Calculate height
int AVL::height(node* temp) {
    if (temp == NULL)
        return 0;
    return 1 + max(height(temp->left), height(temp->right));
}

// Balance Factor
int AVL::BF(node* temp) {
    if (temp == NULL)
        return 0;
    return height(temp->left) - height(temp->right);
}

// Rotations
node* AVL::RotateRight(node* parent) {
    node* temp = parent->left;
    parent->left = temp->right;
    temp->right = parent;
    parent->ht = height(parent);
    temp->ht = height(temp);
    return temp;
}

node* AVL::RotateLeft(node* parent) {
    node* temp = parent->right;
    parent->right = temp->left;
    temp->left = parent;
    parent->ht = height(parent);
    temp->ht = height(temp);
    return temp;
}

node* AVL::RR(node* T) {
    return RotateLeft(T);
}

node* AVL::LL(node* T) {
    return RotateRight(T);
}

node* AVL::LR(node* T) {
    T->left = RotateLeft(T->left);
    return RotateRight(T);
}

node* AVL::RL(node* T) {
    T->right = RotateRight(T->right);
    return RotateLeft(T);
}

// Insert with safe balancing
node* AVL::insert(node* temp, string str_w, string str_m) {
    if (temp == NULL) {
        temp = new node;
        temp->word = str_w;
        temp->meaning = str_m;
        temp->left = temp->right = NULL;
    } else {
        if (str_w.compare(temp->word) > 0) {
            temp->right = insert(temp->right, str_w, str_m);
            if (BF(temp) == -2) {
                if (temp->right && str_w.compare(temp->right->word) > 0)
                    temp = RR(temp);
                else
                    temp = RL(temp);
            }
        } else {
            temp->left = insert(temp->left, str_w, str_m);
            if (BF(temp) == 2) {
                if (temp->left && str_w.compare(temp->left->word) < 0)
                    temp = LL(temp);
                else
                    temp = LR(temp);
            }
        }
    }
    temp->ht = height(temp);
    return temp;
}

// Find minimum node
node* AVL::findMin(node* root) {
    while (root->left != NULL)
        root = root->left;
    return root;
}

// Delete node
node* AVL::deleteNode(node* root, string str_w) {
    if (root == NULL)
        return NULL;

    if (str_w < root->word)
        root->left = deleteNode(root->left, str_w);
    else if (str_w > root->word)
        root->right = deleteNode(root->right, str_w);
    else {
        if (root->left == NULL) {
            node* temp = root->right;
            delete root;
            return temp;
        } else if (root->right == NULL) {
            node* temp = root->left;
            delete root;
            return temp;
        } else {
            node* temp = findMin(root->right);
            root->word = temp->word;
            root->meaning = temp->meaning;
            root->right = deleteNode(root->right, temp->word);
        }
    }
    root->ht = height(root);
    return root;
}

// Display preorder
void AVL::preorder(node* root) {
    if (root != NULL) {
        cout << root->word << " : " << root->meaning << " (Bf=" << BF(root) << ")\n";
        preorder(root->left);
        preorder(root->right);
    }
}

// Display inorder
void AVL::inorder(node* root) {
    if (root != NULL) {
        inorder(root->left);
        cout << root->word << " : " << root->meaning << " (Bf=" << BF(root) << ")\n";
        inorder(root->right);
    }
}

// Search
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

// Modify
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

// Main driver
int main() {
    AVL Tree;
    int ch;
    string str1, str2;

    cout << "\tOPERATIONS ON AVL TREE\t" << endl;

    while (true) {
        cout << "\n1. Create tree\n2. Add word\n3. Display tree\n4. Delete word\n5. Search word\n6. Modify meaning\n7. Exit" << endl;
        cout << "Enter choice: ";
        cin >> ch;
        cin.ignore();

        switch (ch) {
            case 1:
            case 2:
                cout << "Enter word: ";
                cin >> str1;
                cin.ignore();
                cout << "Enter meaning: ";
                getline(cin, str2);
                Tree.root = Tree.insert(Tree.root, str1, str2);
                break;

            case 3:
                cout << "\nPreorder:\n";
                Tree.preorder(Tree.root);
                cout << "\nInorder:\n";
                Tree.inorder(Tree.root);
                break;

            case 4:
                cout << "Enter word to delete: ";
                cin >> str1;
                Tree.root = Tree.deleteNode(Tree.root, str1);
                break;

            case 5:
                cout << "Enter word to search: ";
                cin >> str1;
                Tree.search(Tree.root, str1);
                break;

            case 6:
                cout << "Enter word to modify: ";
                cin >> str1;
                Tree.modify(Tree.root, str1);
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
