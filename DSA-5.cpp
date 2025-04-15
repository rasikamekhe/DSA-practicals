#include <iostream>
using namespace std;

class node {
public:
    node* left;
    node* right;
    string word, meaning;
};

class BST {
public:
    node* root;
    node* temp;
    int op;
    string key;
    int flag;

    BST() { // constructor
        root = NULL;
        flag = 0;
    }

    void create();
    void ascending(node* root);
    void descending(node* root);
    void insert(node* root, node* temp);
    int search(node* root, string word);
    void updateMeaning(node* root, string word);
    int findMaxComparisons(node* root);
    int findMinComparisons(node* root);
    node* deleteNode(node* root, string key);
};

void BST::create() {
    do {
        temp = new node;
        cout << "Enter the word to store in tree: ";
        cin.ignore();
        getline(cin, temp->word);
        cout << "Enter the meaning of word: ";
        getline(cin, temp->meaning);
        temp->left = temp->right = NULL;

        if (root == NULL) {
            root = temp;
        } else {
            insert(root, temp);
        }

        cout << "Do you want to continue? yes-1 no-0: ";
        cin >> op;
    } while (op == 1);
}

void BST::insert(node* root, node* temp) {
    if (temp->word < root->word) {
        if (root->left == NULL)
            root->left = temp;
        else
            insert(root->left, temp);
    } else if (temp->word > root->word) {
        if (root->right == NULL)
            root->right = temp;
        else
            insert(root->right, temp);
    }
}

void BST::ascending(node* root) {
    if (root != NULL) {
        ascending(root->left);
        cout << root->word << " : " << root->meaning << endl;
        ascending(root->right);
    }
}

void BST::descending(node* root) {
    if (root != NULL) {
        descending(root->right);
        cout << root->word << " : " << root->meaning << endl;
        descending(root->left);
    }
}

int BST::search(node* root, string word) {
    if (root == NULL)
        return 0;
    if (word == root->word)
        return 1;
    if (word < root->word)
        return search(root->left, word);
    else
        return search(root->right, word);
}

void BST::updateMeaning(node* root, string word) {
    if (root == NULL) {
        cout << "Word not found" << endl;
        return;
    }

    if (word == root->word) {
        cout << "Enter the new meaning: ";
        cin.ignore();
        getline(cin, root->meaning);
        cout << "Meaning updated successfully!" << endl;
        return;
    }

    if (word < root->word)
        updateMeaning(root->left, word);
    else
        updateMeaning(root->right, word);
}

int BST::findMaxComparisons(node* root) {
    int count = 0;
    while (root != NULL) {
        count++;
        root = root->right;
    }
    return count;
}

int BST::findMinComparisons(node* root) {
    int count = 0;
    while (root != NULL) {
        count++;
        root = root->left;
    }
    return count;
}

node* BST::deleteNode(node* root, string key) {
    if (root == NULL)
        return root;

    if (key < root->word) {
        root->left = deleteNode(root->left, key);
    } else if (key > root->word) {
        root->right = deleteNode(root->right, key);
    } else {
        if (root->left == NULL) {
            node* temp = root->right;
            delete root;
            return temp;
        } else if (root->right == NULL) {
            node* temp = root->left;
            delete root;
            return temp;
        }

        node* succParent = root;
        node* succ = root->right;

        while (succ->left != NULL) {
            succParent = succ;
            succ = succ->left;
        }

        root->word = succ->word;
        root->meaning = succ->meaning;
        root->right = deleteNode(root->right, succ->word);
    }

    return root;
}

int main() {
    BST obj;
    int ch;
    string word;

    while (1) {
        cout << "\n__MENU__";
        cout << "\n1. Create";
        cout << "\n2. Insert";
        cout << "\n3. Traverse using ascending";
        cout << "\n4. Traverse using descending";
        cout << "\n5. Search";
        cout << "\n6. Delete";
        cout << "\n7. Update the meaning of word";
        cout << "\n8. Maximum comparisons";
        cout << "\n9. Minimum comparisons";
        cout << "\n10. Exit";
        cout << "\nEnter your choice: ";
        cin >> ch;

        switch (ch) {
            case 1:
            case 2:
                obj.create();
                break;
            case 3:
                obj.ascending(obj.root);
                break;
            case 4:
                obj.descending(obj.root);
                break;
            case 5:
                cout << "Enter the word to search in BST: ";
                cin >> obj.key;
                obj.flag = obj.search(obj.root, obj.key);
                if (obj.flag == 1)
                    cout << "Word found!" << endl;
                else
                    cout << "Word not found." << endl;
                break;
            case 6:
                cout << "Enter the word to be deleted: ";
                cin >> word;
                obj.root = obj.deleteNode(obj.root, word);
                cout << "Word deleted!" << endl;
                break;
            case 7:
                cout << "Enter the word to update the meaning: ";
                cin >> word;
                obj.updateMeaning(obj.root, word);
                break;
            case 8:
                cout << "Maximum comparisons required: " << obj.findMaxComparisons(obj.root) << endl;
                break;
            case 9:
                cout << "Minimum comparisons required: " << obj.findMinComparisons(obj.root) << endl;
                break;
            case 10:
                exit(0);
            default:
                cout << "Invalid choice!" << endl;
        }
    }

    return 0;
}


//OUTPUT:
__MENU__
1. Create
2. Insert
3. Traverse using ascending
4. Traverse using descending
5. Search
6. Delete
7. Update the meaning of word
8. Maximum comparision
9. Minimum comparisions
10. Exit
Enter your choice: 1
Enter the word to store in tree: nest
Enter the meaningn of word to store in tree: house
Do you want to continue? yes-1 no-0: 1
Enter the word to store in tree: hat
Enter the meaningn of word to store in tree: thing
Do you want to continue? yes-1 no-0: 1
Enter the word to store in tree: apple
Enter the meaningn of word to store in tree: fruit
Do you want to continue? yes-1 no-0: 1
Enter the word to store in tree: ink
Enter the meaningn of word to store in tree: thing
Do you want to continue? yes-1 no-0: 1
Enter the word to store in tree: queen
Enter the meaningn of word to store in tree: lady
Do you want to continue? yes-1 no-0: 1
Enter the word to store in tree: ox
Enter the meaningn of word to store in tree: animal
Do you want to continue? yes-1 no-0: 1
Enter the word to store in tree: zebra
Enter the meaningn of word to store in tree: animal
Do you want to continue? yes-1 no-0: 0
__MENU__
1. Create
2. Insert
3. Traverse using ascending
4. Traverse using descending
5. Search
6. Delete
7. Update the meaning of word
8. Maximum comparision
9. Minimum comparisions
10. Exit
Enter your choice: 2
Enter the word to store in tree: pineapple
Enter the meaningn of word to store in tree: fruit
Do you want to continue? yes-1 no-0: 0
__MENU__
1. Create
2. Insert
3. Traverse using ascending
4. Traverse using descending
5. Search
6. Delete
7. Update the meaning of word
8. Maximum comparision
9. Minimum comparisions
10. Exit
Enter your choice: 3
apple : fruit
hat : thing
ink : thing
nest : house
ox : animal
pineapple : fruit
queen : lady
zebra : animal
__MENU__
1. Create
2. Insert
3. Traverse using ascending
4. Traverse using descending
5. Search
6. Delete
7. Update the meaning of word
8. Maximum comparision
9. Minimum comparisions
10. Exit
Enter your choice: 4
zebra : animal
queen : lady
pineapple : fruit
ox : animal
nest : house
ink : thing
hat : thing
apple : fruit
__MENU__
1. Create
2. Insert
3. Traverse using ascending
4. Traverse using descending
5. Search
6. Delete
7. Update the meaning of word
8. Maximum comparision
9. Minimum comparisions
10. Exit
Enter your choice: 5
Enter the data to be search in BST
hat
Data found
__MENU__
1. Create
2. Insert
3. Traverse using ascending
4. Traverse using descending
5. Search
6. Delete
7. Update the meaning of word
8. Maximum comparision
9. Minimum comparisions
10. Exit
Enter your choice: 5
Enter the data to be search in BST
mili
data not found
__MENU__
1. Create
2. Insert
3. Traverse using ascending
4. Traverse using descending
5. Search
6. Delete
7. Update the meaning of word
8. Maximum comparision
9. Minimum comparisions
10. Exit
Enter your choice: 6
Enter the word to be deleted: pineapple
Word deleted!
__MENU__
1. Create
2. Insert
3. Traverse using ascending
4. Traverse using descending
5. Search
6. Delete
7. Update the meaning of word
8. Maximum comparision
9. Minimum comparisions
10. Exit
Enter your choice: 7
Enter the word to update the meaning: hat
Enter the new meaning: clothing
Meaning updated! successfully
__MENU__
1. Create
2. Insert
3. Traverse using ascending
4. Traverse using descending
5. Search
6. Delete
7. Update the meaning of word
8. Maximum comparision
9. Minimum comparisions
10. Exit
Enter your choice: 8
Maximum comparision required: 3
__MENU__
1. Create
2. Insert
3. Traverse using ascending
4. Traverse using descending
5. Search
6. Delete
7. Update the meaning of word
8. Maximum comparision
9. Minimum comparisions
10. Exit
Enter your choice: 9
Minimum comparisions reuired: 3
__MENU__
1. Create
2. Insert
3. Traverse using ascending
4. Traverse using descending
5. Search
6. Delete
7. Update the meaning of word
8. Maximum comparision
9. Minimum comparisions
10. Exit
Enter your choice: 10
=== Code Execution Successful ===
