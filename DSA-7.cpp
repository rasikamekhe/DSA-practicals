#include <iostream>
#include <iomanip>
using namespace std;

class graph {
    int G[20][20];
    string city[20];

public:
    int n;

    graph() {
        cout << "Enter no. of vertices you want in flight path graph: " << endl;
        cin >> n;

        // Initialize adj matrix to 0
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                G[i][j] = 0;
            }
        }
    }

    void create();
    void display();
    void prims();
};

void graph::create() {
    for (int i = 0; i < n; i++) {
        cout << "Enter name of city " << (i + 1) << ": " << endl;
        cin >> city[i];
    }

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            cout << "Enter distance between " << city[i] << " and " << city[j] << ": ";
            cout << "(Enter 0 if no direct flight)" << endl;
            cin >> G[i][j];
            G[j][i] = G[i][j];
        }
    }
}

void graph::display() {
    cout << "\nAdjacency matrix: " << endl;
    cout << "\t\t";
    for (int i = 0; i < n; i++) {
        cout << setw(20) << city[i] << " ";
    }
    cout << endl;

    for (int i = 0; i < n; i++) {
        cout << setw(20) << city[i] << " ";
        for (int j = 0; j < n; j++) {
            cout << setw(20) << G[i][j] << " ";
        }
        cout << endl;
    }
}

void graph::prims() {
    int visited[20] = {0}; // visited array
    int no_edges = 0;
    int min_cost = 0;
    int min, u, v;

    cout << "Enter starting vertex (index between 0 and " << n - 1 << "): ";
    int R;
    cin >> R;

    visited[R] = 1; // Mark the starting vertex as visited
    no_edges = 0;

    cout << "\nEdges in the minimum spanning tree (MST):" << endl;

    while (no_edges < n - 1) {
        min = 999; // Initialize min with 999
        u = -1;
        v = -1;

        for (int i = 0; i < n; i++) {
            if (visited[i] == 1) {
                for (int j = 0; j < n; j++) {
                    if (visited[j] == 0 && G[i][j] < min && G[i][j] != 0) {
                        min = G[i][j];
                        u = i;
                        v = j;
                    }
                }
            }
        }

        if (u != -1 && v != -1) {
            cout << city[u] << " - " << city[v] << " : " << min << endl;
            visited[v] = 1; // Mark the vertex as visited
            no_edges++;
            min_cost += min;
        }
    }

    cout << "Minimum cost of MST is: " << min_cost << endl;
}

int main() {
    graph g;
    g.create();
    g.display();
    g.prims();
    return 0;
}

//OUTPUT:
Enter no. of vertices you want in flight path graph:
5
Enter name of city 1: A
Enter name of city 2: B
Enter name of city 3: C
Enter name of city 4: D
Enter name of city 5: E
Enter distance between A and B: (Enter 0 if no direct flight) 4
Enter distance between A and C: (Enter 0 if no direct flight) 0
Enter distance between A and D: (Enter 0 if no direct flight) 3
Enter distance between A and E: (Enter 0 if no direct flight) 5
Enter distance between B and C: (Enter 0 if no direct flight) 2
Enter distance between B and D: (Enter 0 if no direct flight) 0
Enter distance between B and E: (Enter 0 if no direct flight) 0
Enter distance between C and D: (Enter 0 if no direct flight) 1
Enter distance between C and E: (Enter 0 if no direct flight) 1
Enter distance between D and E: (Enter 0 if no direct flight) 0
Adjacency matrix:
  A B C D E
A 0 4 0 3 5
B 4 0 2 0 0
C 0 2 0 1 1
D 3 0 1 0 0
E 5 0 1 0 0
Enter starting vertex: A
Edges in the minimum spanning tree (MST):
A - D : 3
D - C : 1
C - E : 1
C - B : 2
Mininum cost of MST is: 7
