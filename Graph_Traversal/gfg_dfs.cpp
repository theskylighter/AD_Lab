#include<bits/stdc++.h>
using namespace std;
 // namespace std;



class graph{
    public:
    map<int,bool> visited;
    map<int, list<int>> adj;

    void addEdge(int u, int v){
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void dispAdj(){
        
        for(int i=0;i<adj.size();i++ ){
            cout<<i<<" : ";
            for( int j: adj[i]){
                cout<<j<<" ";
            }
            cout<<endl;
        }
    }

    void dfs(int v){
        cout<<v<< " ";
        visited[v]=true;

        for(int i:adj[v]){
            if (!visited[i])
            dfs(i);
        }

    }

};


int main(){
    graph g;

    g.addEdge(0,1);
    g.addEdge(0,2);
    g.addEdge(1,3);
    g.addEdge(4,3);
    g.addEdge(4,7);
    g.addEdge(1,5);
    g.addEdge(8,5);
    g.addEdge(2,6);
    g.dispAdj();

    cout<<"DFS : "<<endl;
    g.dfs(0);
    cout<<endl;

}