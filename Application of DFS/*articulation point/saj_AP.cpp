    #include <iostream>
    #include <fstream>
    #include <vector>
    #include <sstream>
    #include <queue>
    #include <stack>
    #include <set>
    using namespace std;

    int n;

    // Function to read adjacency matrix from a file
    vector<vector<int>> read(string &filename){
        ifstream file(filename);
        if (!file.is_open()) {
            cout << "Error opening file";
            exit(1);
        }
        file >> n;
        string line;
        getline(file, line);
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

    // Function to convert adjacency matrix to adjacency list
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

    // Function to print the adjacency list
    void printlist(vector<vector<int>> adjlist) {
        for (int i = 0; i < adjlist.size(); i++) {
            cout << i << "-> ";
            for (int j = 0; j < adjlist[i].size(); j++) {
                cout << adjlist[i][j] << " ";
            }
            cout << endl;
        }
    }

    // Helper function for DFS
    void dfs(int u, vector<vector<int>> &adjList, vector<int> &disc, vector<int> &low, vector<int> &parent, vector<bool> &ap, set<int> &articulationPoints, int &time) {
        int children = 0;
        disc[u] = low[u] = ++time;
        for (int v : adjList[u]) {
            if (disc[v] == -1) {  // If v is not visited
                children++;
                parent[v] = u;
                dfs(v, adjList, disc, low, parent, ap, articulationPoints, time);
                low[u] = min(low[u], low[v]);
                if (parent[u] == -1 && children > 1) {
                    ap[u] = true;
                }
                if (parent[u] != -1 && low[v] >= disc[u]) {
                    ap[u] = true;
                }
            } else if (v != parent[u]) {
                low[u] = min(low[u], disc[v]);
            }
        }
    }

    // Function to find articulation points
    set<int> findArticulationPoints(vector<vector<int>> &adjList) {
        int V = adjList.size();
        vector<int> disc(V, -1), low(V, -1), parent(V, -1);
        vector<bool> ap(V, false);
        set<int> articulationPoints;
        int time = 0;

        for (int i = 0; i < V; i++) {
            if (disc[i] == -1) {
                dfs(i, adjList, disc, low, parent, ap, articulationPoints, time);
            }
        }

        for (int i = 0; i < V; i++) {
            if (ap[i]) {
                articulationPoints.insert(i);
            }
        }

        return articulationPoints;
    }

    int main() {
        string fname = "graph.dat";
        vector<vector<int>> adjmat = read(fname);
        vector<vector<int>> adjL = adjM_to_adjL(adjmat);
        
        // Print the adjacency list
        cout << "Adjacency List:" << endl;
        printlist(adjL);
        
        // Find and print articulation points
        set<int> articulationPoints = findArticulationPoints(adjL);
        cout << "Articulation Points:" << endl;
        for (int point : articulationPoints) {
            cout << point << " ";
        }
        cout << endl;

        return 0;
    }

