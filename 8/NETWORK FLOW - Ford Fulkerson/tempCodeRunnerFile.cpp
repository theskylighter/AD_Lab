#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>
using namespace std;

bool bfs(vector<vector<int>> &rGraph, int s, int t, vector<int> &parent){
    int V=rGraph.size();
    vector<bool> visited(V, false);
    queue<int> q;
    q.push(s);
    visited[s]=true;
    parent[s]=-1;
    while(!q.empty()){
        int u=q.front();
        q.pop();
        for(int v=0; v<V; v++){
            if(!visited[v] && rGraph[u][v]>0){
                if(v==t) {
                    parent[v]=u;
                    return true;                   
            }
                q.push(v);
                parent[v]=u;
                visited[v]=true;
            }
            
        }

    }
    return false;
}

int ford_fulkerson(vector<vector<int>>& graph, int s, int t) {
    vector<vector<int>>     h;
    int max_flow = 0;
    vector<int> parent(graph.size(), -1);
    int min_flow=INT_MAX;
    while(bfs(rGraph,s,t,parent)){
        for(int v=t; v!=s; v=parent[v]){
            int u=parent[v];
            min_flow=min(min_flow,rGraph[u][v]);
        }
    
        for(int v=t; v!=s; v=parent[v]){
            int u=parent[v];
            rGraph[u][v]-= min_flow;
            rGraph[v][u]+=min_flow;
        }
        max_flow+=min_flow;     
    }
    return max_flow;
    
}



int main()
{
    int V = 6;
    vector<vector<int>> graph(V, vector<int> (V, 0));
    graph[0][1] = 16;
    graph[0][2] = 13;
    graph[1][2] = 10;
    graph[1][3] = 12;
    graph[2][1] = 4;
    graph[2][4] = 14;
    graph[3][5] = 20;
    graph[4][3] =4;
    graph[4][5] = 4;
    
    cout << "Maximum Flow: " << ford_fulkerson(graph, 0, 5) << endl;
    return 0;
}