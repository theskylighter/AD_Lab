#include<bits/stdc++.h>
using namespace std;

class graph{
    public:
    map<int,bool> visited;
    map<int, list<int>> adj;
    int V; // number of vertices

    graph(const string& filename) {
        readAdjMatrix(filename);
    }

    void readAdjMatrix(const string& filename) {
        ifstream file(filename);
        if (!file) {
            cout << "Error opening file!" << endl;
            return;
        }

        file >> V; // Read number of vertices
        
        // Read adjacency matrix
        for(int i = 0; i < V; i++) {
            for(int j = 0; j < V; j++) {
                int value;
                file >> value;
                if(j < V-1) {
                    char comma;
                    file >> comma; // Read and discard the comma
                }
                if(value == 1) {
                    addEdge(i, j);
                }
            }
        }
        file.close();
    }

    void addEdge(int u, int v){
        adj[u].push_back(v);
    }

    void dispAdj(){
        for(int i = 0; i < V; i++){
            cout << i << " : ";
            for(int j: adj[i]){
                cout << j << " ";
            }
            cout << endl;
        }
    }

    void dfs(int v){
        cout << v << " ";
        visited[v] = true;

        for(int i: adj[v]){
            if(!visited[i])
                dfs(i);
        }
    }
};

int main(){
    graph g("adjmatrix.txt");
    
    cout << "Adjacency List:" << endl;
    g.dispAdj();

    cout << "DFS traversal starting from vertex 0:" << endl;
    g.dfs(0);
    cout << endl;

    return 0;
}