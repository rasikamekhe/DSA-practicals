#include <iostream>
#include <iomanip>
#include <stack>
#include <queue>
using namespace std;

class graph {
    int G[20][20];           // Adjacency matrix
    string city[20];         // City names

public:
    int n;                   // Number of cities (vertices)

    graph() {
        cout << "Enter number of cities in flight path graph: ";
        cin >> n;

        // Initialize adjacency matrix to 0 (no connections yet)
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                G[i][j] = 0;
            }
        }
    }

    void create();
    void display();
    void dfs(int start);
    void bfs(int start);
    bool isConnected(); 
};

void graph::create() {
    // Input city names
    for (int i = 0; i < n; i++) {
        cout << "Enter name of city " << (i + 1) << ": ";
        cin >> city[i];
    }

    // Input distances (edges)
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            if (i == j) {
                G[i][j] = 0;
                continue;
            }
            cout << "Enter distance between " << city[i] << " and " << city[j] << " (0 if no flight): ";
            cin >> G[i][j];
            G[j][i] = G[i][j];  // Undirected graph (symmetric)
        }
    }
}

void graph::display() {
    // Display adjacency matrix with city labels
    cout << "\nAdjacency Matrix:\n\t";
    for (int i = 0; i < n; i++) {
        cout << setw(10) << city[i];
    }
    cout << endl;

    for (int i = 0; i < n; i++) {
        cout << setw(10) << city[i];
        for (int j = 0; j < n; j++) {
            cout << setw(10) << G[i][j];
        }
        cout << endl;
    }
}

void graph::bfs(int start) {
    bool visited[20] = { false };
    queue<int> q;

    visited[start] = true;
    q.push(start);

    cout << "\nBFS Traversal from " << city[start] << ": ";

    while (!q.empty()) {
        int current = q.front();  // Get front of queue
        q.pop();                  // Remove from queue

        cout << city[current] << " ";

        for (int i = 0; i < n; i++) {
            if (G[current][i] != 0 && !visited[i]) {
                visited[i] = true;
                q.push(i);
            }
        }
    }
    cout << endl;
}

void graph::dfs(int start) {
    bool visited[20] = { false };
    stack<int> s;

    visited[start] = true;
    s.push(start);

    cout << "\nDFS Traversal from " << city[start] << ": ";

    while (!s.empty()) {
        int current = s.top();
        s.pop();

        cout << city[current] << " ";

        for (int i = 0; i < n; i++) {
            if (G[current][i] != 0 && !visited[i]) {
                visited[i] = true;
                s.push(i);
            }
        }
    }
    cout << endl;
}

bool graph::isConnected() {
    bool visited[20] = { false };
    queue<int> q;

    visited[0] = true;
    q.push(0);  // Start from first city

    int count = 0;  // Count visited nodes

    while (!q.empty()) {
        int current = q.front();
        q.pop();
        count++;

        for (int i = 0; i < n; i++) {
            if (G[current][i] != 0 && !visited[i]) {
                visited[i] = true;
                q.push(i);
            }
        }
    }

    if (count == n) {
        return true;  // All cities visited
    } else {
        return false; // Some cities are not reachable
    }
}

// ----------------------- MAIN FUNCTION -----------------------
int main() {
    graph g;
    int ch, op, start;

    do {
        cout << "\nMenu:\n";
        cout << "1. Create Graph\n";
        cout << "2. Display Graph\n";
        cout << "3. BFS Traversal\n";
        cout << "4. DFS Traversal\n";
        cout << "5. Check if Graph is Connected\n";
        cout << "Enter your choice: ";
        cin >> ch;

        switch (ch) {
            case 1:
                g.create();
                break;

            case 2:
                g.display();
                break;

            case 3:
                cout << "Enter starting city index (0 to " << g.n - 1 << "): ";
                cin >> start;
                g.bfs(start);
                break;

            case 4:
                cout << "Enter starting city index (0 to " << g.n - 1 << "): ";
                cin >> start;
                g.dfs(start);
                break;

            case 5:
                if (g.isConnected()) {
                    cout << "\nThe graph is CONNECTED — All cities are reachable." << endl;
                } else {
                    cout << "\nThe graph is NOT CONNECTED — Some cities are unreachable." << endl;
                }
                break;

            default:
                cout << "Invalid choice!" << endl;
        }

        cout << "\nPress 1 to continue or 0 to exit: ";
        cin >> op;

    } while (op == 1);

    return 0;
}


//OUTPUT:
Enter no. of vertices you want in flight path graph:  3
  
1.Create the graph
2.Display the graph
3.BFS traversal
4.DFS traversal
Enter your choice: 1
Enter name of city: 1:
pune
Enter name of city: 2:
mumbai
Enter name of city: 3:
nashik
Enter dist b/wpune and pune: (Enter 0 if no edge)
12
Enter dist b/wpune and mumbai: (Enter 0 if no edge)
10
Enter dist b/wpune and nashik: (Enter 0 if no edge)
6
Enter dist b/wmumbai and pune: (Enter 0 if no edge)
11
Enter dist b/wmumbai and mumbai: (Enter 0 if no edge)
19
Enter dist b/wmumbai and nashik: (Enter 0 if no edge)
3
Enter dist b/wnashik and pune: (Enter 0 if no edge)
8
Enter dist b/wnashik and mumbai: (Enter 0 if no edge)
15

Enter dist b/wnashik and nashik: (Enter 0 if no edge)
21
Press 1 to continue and 0 to stop1
1.Create the graph
2.Display the graph
3.BFS traversal
4.DFS traversal
Enter your choice: 2
Adjacency matrix:
pune mumbai
nashik
pune 12 11
8
mumbai 11 19
15
nashik 8 15
21
Press 1 to continue and 0 to stop1
1.Create the graph
2.Display the graph
3.BFS traversal
4.DFS traversal
Enter your choice: 3
Enter starting city index for BFS(0 to2): 1
BFS Traversal starting frommumbai:
mumbai pune nashik

Press 1 to continue and 0 to stop1
1.Create the graph
2.Display the graph

3.BFS traversal
4.DFS traversal
Enter your choice: 4
Enter starting city index for DFS(0 to2): 0
DFS Traversal starting frompune:
pune nashik mumbai
Press 1 to continue and 0 to stop0
