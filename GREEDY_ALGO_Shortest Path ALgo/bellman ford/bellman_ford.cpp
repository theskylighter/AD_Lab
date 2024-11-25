#include <bits/stdc++.h>
// #include<math.h>
using namespace std;

void addEdge(vector<vector<int>>& adj,int i,int j, int w){
// graph data strored as (node i,node j, EdgeWeight)

    vector<int> temp={i,j,w};
    adj.push_back(temp);
}
void printDist(vector<int> &dist){
    cout<<"minimum distance array"<<endl;
    for(auto i:dist) cout<<i<<" ";
    cout<<endl;}

vector<int> ford(vector<vector<int>>& adj, int v, int s){
    vector<int> dist(v,1e8);
    dist[s]=0;
//N-1 iterations
        int i,j,w;
    for(int k=0;k<v-1;k++) {
        for(auto it:adj){
            i=it[0];
            j=it[1];
            w=it[2];
// cout<<i<<j<<w<<endl;
            if(dist[i]!=1e8 && dist[i]+w < dist[j]){
                dist[j]=dist[i] + w;
            }

        }
    }
//also check if there was any updation in nth iteration to indicate negative cycle in graph
for(auto it:adj){
            i=it[0];
            j=it[1];
            w=it[2];
// cout<<i<<j<<w<<endl;
            if(dist[i]!=1e8 && dist[i]+w < dist[j]){
                dist[j]=dist[i] + w;
                cout<<"Negative cycle detected !"<<endl;
                return {-1};
            }
        }
        return dist;


}

int main(){
    // no of vertexs
    int v=6;
    vector<vector<int>> adj;
    addEdge(adj,3,2,6);
    addEdge(adj,5,3,1);
    addEdge(adj,0,1,5);
    addEdge(adj,1,5,-3);
    addEdge(adj,1,2,-2);
    addEdge(adj,3,4,-2);
    addEdge(adj,2,4,3);

// setting source node as 0; 
    int s=0;
    vector<int> dist=ford(adj,v,s);
    printDist(dist);

    return 0;
}