#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <stack>
using namespace std;

int n;

vector<vector<int>> read(string &filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error opening file";
        exit(1);
    }
    file >> n;
    string line;
    file.ignore();
    vector<vector<int>> matrix;
    while (getline(file, line)) {
        stringstream ss(line);
        string val;
        vector<int> row;
        while (getline(ss, val, ',')) {
            row.push_back(stoi(val));
        }
        matrix.push_back(row);
    }
    return matrix;
}

vector<vector<int>> adjM_to_adjL(vector<vector<int>> &mat) {
    int n = mat.size();
    vector<vector<int>> adjlist(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (mat[i][j] != 0) {
                adjlist[i].push_back(j);
            }
        }
    }
    return adjlist;
}

void printlist(vector<vector<int>> adjlist) {
    for (int i = 0; i < adjlist.size(); i++) {
        cout << i << "-> ";
        for (int j = 0; j < adjlist[i].size(); j++) {
            cout << adjlist[i][j] << " ";
        }
        cout << endl;
    }
}

void dfs(int currentNode, vector<vector<int>> &adj, vector<int> &disc, vector<int> &low, vector<int> &parent, vector<int> &APs) {
    static int time = 0;
    int childCount = 0;
    disc[currentNode] = low[currentNode] = ++time;

    for (int nbr : adj[currentNode]) {
        
        // nbr is Unvisited
        if (disc[nbr] == -1) { 
            parent[nbr] = currentNode;
            childCount++;
            dfs(nbr, adj, disc, low, parent, APs);

            // check & update
            // if the subtree rooted at neighborNode(child) has a connection back to one of currentNode's ancestors

            low[currentNode] = min(low[currentNode], low[nbr]);

            // currentNode is an articulation point in two cases:
            // 1) currentNode is the root of the DFS tree and has more than one child
            if (parent[currentNode] == -1 && childCount > 1) {
                APs.push_back(currentNode);
            }
            // 2) currentNode is not the root &
            //  one of its child can't connect to currentNode or any of its ancestors
            if (parent[currentNode] != -1 && low[nbr] >= disc[currentNode]) {
                APs.push_back(currentNode);
            }
        } 

        // nbr has been visited but not parent 
        else if (nbr != parent[currentNode]) {
            // ! this is condition for alternate connection to ancestors 
            // Update lowestTime[currentNode] for back edge
            low[currentNode] = min(low[currentNode], disc[nbr]);
        }
    }
}

vector<int> tarjan(vector<vector<int>> &adj) {
    int n = adj.size();
    vector<int> disc(n, -1); // Discovery time of nodes
    vector<int> lowestTime(n, -1);    // Lowest discovery time reachable
                                      // (low-link)
    vector<int> parent(n, -1);        // Parent of nodes in DFS tree
    vector<int> APs;

    for (int node = 0; node < n; node++) {
        if (disc[node] == -1) {
            dfs(node, adj, disc, lowestTime, parent, APs);
        }
    }

    return APs;
}

int main() {
    string fname = "graph.dat";
    vector<vector<int>> adjmat = read(fname);
    vector<vector<int>> adjL = adjM_to_adjL(adjmat);
    printlist(adjL);

    vector<int> APs = tarjan(adjL);
    cout << "Articulation Points: ";
    for (int ap : APs) {
        cout << ap << " ";
    }
    cout << endl;

    return 0;
}
