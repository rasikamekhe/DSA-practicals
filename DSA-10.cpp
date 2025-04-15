#include <iostream>
#include <string.h>
using namespace std;

#define MAX 100

struct patient {
    int priority;
    char name[10];
};

class priority_queue {
private:
    patient queue[MAX];
    int size;

public:
    priority_queue() { size = 0; }
    bool isempty() { return size == 0; }
    void pq_insert(int priority, char name[10]);
    void pq_display();
    void pq_delete();
};

void priority_queue::pq_insert(int priority, char name[10]) {
    if (size == MAX) {
        cout << "Queue is full, cannot insert more patients!";
        return;
    }

    queue[size].priority = priority;
    strcpy(queue[size].name, name);
    size++;

    for (int i = size - 1; i > 0; i--) {
        if (queue[i].priority < queue[i - 1].priority) {
            swap(queue[i], queue[i - 1]);
        } else {
            break;
        }
    }
}

void priority_queue::pq_display() {
    if (isempty()) {
        cout << "No patients in queue.\n";
        return;
    }

    cout << "\nPriority\tSeverity\tPatient Name\n";
    for (int i = 0; i < size; i++) {
        cout << queue[i].priority << "\t\t";
        if (queue[i].priority == 1) cout << "Serious";
        else if (queue[i].priority == 2) cout << "Medium";
        else cout << "Normal";
        cout << "\t\t" << queue[i].name << endl;
    }
}

void priority_queue::pq_delete() {
    if (isempty()) {
        cout << "No patients in queue to delete.\n";
        return;
    }

    cout << "\nPatient " << queue[0].name << " checked successfully.\n";

    for (int i = 0; i < size - 1; i++) {
        queue[i] = queue[i + 1];
    }
    size--;

    pq_display();
}

int main() {
    priority_queue pq; // Creating object of priority_queue class
    int priority, ch, n, ans;
    char name[10];

    do {
        cout << "\nHospital Management System";
        cout << "\n1. Enter Patient Record";
        cout << "\n2. Display Patients";
        cout << "\n3. Delete (Serve) Patient";
        cout << "\nEnter your choice: ";
        cin >> ch;

        switch (ch) {
            case 1:
                cout << "\n1. Serious (1)";
                cout << "\n2. Medium (2)";
                cout << "\n3. Normal (3)";
                cout << "\nEnter the number of patients: ";
                cin >> n;
                for (int i = 0; i < n; i++) {
                    cout << "\nEnter Severity (1-3): ";
                    cin >> priority;
                    cout << "Enter Patient Name: ";
                    cin >> name;
                    pq.pq_insert(priority, name); // Insert into priority queue
                }
                break;

            case 2:
                pq.pq_display();
                break;

            case 3:
                pq.pq_delete();
                break;

            default:
                cout << "Wrong choice! \n";
        }

        cout << "\nDo you want to perform the operation again? (1 for Yes / 0 for No): ";
        cin >> ans;

    } while (ans == 1);

    return 0;
}

//OUTPUT:
Hospital Management System
1. Enter Patient Record
2. Display Patients
3. Delete (Severe) Patient
Enter your choice: 1
1. Serious (1)
2. Medium (2)
3. Normal (3)
Enter the number of patients: 4
Enter Severity (1-3): 1
Enter Patient Name: john
Enter Severity (1-3): 3
Enter Patient Name: bob
Enter Severity (1-3): 2
Enter Patient Name: alice
Enter Severity (1-3): 3
Enter Patient Name: kate
Do you want to perform the operation again? (1 for Yes / 0 for No): 1
Hospital Management System
1. Enter Patient Record
2. Display Patients
3. Delete (Severe) Patient

Enter your choice: 2
Priority Severity Patient Name
1 Serious john
2 Medium alice
3 Normal bob
3 Normal kate
Do you want to perform the operation again? (1 for Yes / 0 for No): 1
Hospital Management System
1. Enter Patient Record
2. Display Patients
3. Delete (Severe) Patient
Enter your choice: 3
Patient john checked successfully.
Priority Severity Patient Name
2 Medium alice
3 Normal bob
3 Normal kate
Do you want to perform the operation again? (1 for Yes / 0 for No): 0
