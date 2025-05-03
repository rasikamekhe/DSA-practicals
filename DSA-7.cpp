#include <iostream>
#include <iomanip>
using namespace std;

class Graph {
    int G[20][20];         // Adjacency matrix to store edge weights (costs between offices)
    string office[20];     // Array to store office names

public:
    int n;                 // Number of offices

    // Constructor to initialize the graph
    Graph() {
        cout << "Enter the number of offices: ";
        cin >> n;

        // Initialize the adjacency matrix with 0 (no connection)
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                G[i][j] = 0;
            }
        }
    }

    // Function to create the graph (input office names and connection costs)
    void create();
    void display();
    void prims();  // Function to apply Prim’s algorithm and find MST
};

// Function to input office names and their pairwise connection costs
void Graph::create() {
    for (int i = 0; i < n; i++) {
        cout << "Enter name of office " << (i + 1) << ": ";
        cin >> office[i];
    }

    // Only fill upper triangle of matrix to avoid duplicate inputs
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            cout << "Enter cost to connect " << office[i] << " and " << office[j] << ": ";
            cout << "(Enter 0 if no direct connection)" << endl;
            cin >> G[i][j];
            G[j][i] = G[i][j];  // Symmetric for undirected graph
        }
    }
}

// Function to display the adjacency matrix
void Graph::display() {
    cout << "\nAdjacency Matrix (Cost to connect offices):\n";
    cout << "\t\t";
    for (int i = 0; i < n; i++) {
        cout << setw(15) << office[i];
    }
    cout << endl;

    for (int i = 0; i < n; i++) {
        cout << setw(15) << office[i];
        for (int j = 0; j < n; j++) {
            cout << setw(15) << G[i][j];
        }
        cout << endl;
    }
}

// Function to find the Minimum Spanning Tree using Prim's Algorithm
void Graph::prims() {
    int visited[20] = {0};  // Track which offices are connected
    int no_edges = 0;       // Number of edges in MST
    int min_cost = 0;       // Total cost of MST
    int min, u, v;

    int R;
    cout << "\nEnter the starting office index (0 to " << n - 1 << "): ";
    cin >> R;

    visited[R] = 1;  // Mark the starting office as connected

    cout << "\nEdges selected for Minimum Spanning Tree:\n";

    while (no_edges < n - 1) {
        min = 999;  // Set large initial min
        u = -1;
        v = -1;

        // Loop through connected offices to find the smallest connecting edge
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

        // If valid edge found, add it to MST
        if (u != -1 && v != -1) {
            cout << office[u] << " - " << office[v] << " : " << min << endl;
            visited[v] = 1;
            no_edges++;
            min_cost += min;
        }
    }

    cout << "\nTotal minimum cost to connect all offices: " << min_cost << endl;
}

// Main function
int main() {
    Graph g;
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
