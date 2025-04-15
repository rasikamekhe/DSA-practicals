#include <iostream>
#include <iomanip>
#include <stack>
#include <queue>
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
    void dfs(int start);
    void bfs(int start);
};

void graph::create() {
    for (int i = 0; i < n; i++) {
        cout << "Enter name of city " << (i + 1) << ": " << endl;
        cin >> city[i];
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << "Enter distance between " << city[i] << " and " << city[j] << ": ";
            cout << "(Enter 0 if no edge)" << endl;
            cin >> G[i][j];
            G[j][i] = G[i][j]; // Ensure symmetry for undirected graph
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

void graph::bfs(int start) {
    bool visited[20] = { false };
    queue<int> q;

    visited[start] = true;
    q.push(start);

    cout << "BFS Traversal starting from " << city[start] << ":\n";

    while (!q.empty()) {
        int current = q.front();
        q.pop();
        cout << city[current] << " ";

        for (int i = 0; i < n; i++) {
            if (G[current][i] != 0 && !visited[i]) {
                q.push(i);
                visited[i] = true;
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

    cout << "DFS Traversal starting from " << city[start] << ":\n";

    while (!s.empty()) {
        int current = s.top();
        s.pop();
        cout << city[current] << " ";

        for (int i = 0; i < n; i++) {
            if (G[current][i] != 0 && !visited[i]) {
                s.push(i);
                visited[i] = true;
            }
        }
    }
    cout << endl;
}

int main() {
    graph g;
    int ch, op, start;

    do {
        cout << "\n1. Create the graph\n2. Display the graph\n3. BFS traversal\n4. DFS traversal" << endl;
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
                cout << "Enter starting city index for BFS (0 to " << g.n - 1 << "): ";
                cin >> start;
                g.bfs(start);
                break;
            case 4:
                cout << "Enter starting city index for DFS (0 to " << g.n - 1 << "): ";
                cin >> start;
                g.dfs(start);
                break;
            default:
                cout << "Invalid choice!" << endl;
                break;
        }

        cout << "Press 1 to continue and 0 to stop: ";
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
