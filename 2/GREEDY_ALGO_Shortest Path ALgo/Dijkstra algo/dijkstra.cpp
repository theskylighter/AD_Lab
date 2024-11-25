#include <bits/stdc++.h>
using namespace std;

void addEdge(vector<vector<pair<int,int>>>& adj,int i,int j, int w){
// graph strored as (node,weight)
    adj[i].push_back(make_pair(j,w));
    adj[j].push_back(make_pair(i,w));
}
void printDist(vector<int> &dist){
    cout<<"minimum distance array"<<endl;
    for(auto i:dist) cout<<i<<" ";
    cout<<endl;}
void dij(vector<vector<pair<int,int>>>& adj,int v, int s){

// making a min heap
// stored as (weight,node)
    priority_queue<pair<int,int>, vector<pair<int,int>>,greater<pair<int,int>>> pq;

// answer = array storing minimum distance from S;
    vector<int> dist(v);

// setting infinite distance initially
    for(int i=0;i<v;i++)    dist[i]=INT_MAX;

    dist[s]=0;
    pq.push(make_pair(0,s));

    while(!pq.empty())
    {
        int dis =pq.top().first; //distance of top element
        int node =pq.top().second;// node of top element

        pq.pop();
        for(auto i : adj[node]){
            int weight=i.second;
            int nextNode = i.first;
            // if new distance is less than prev dis
            if(dis + weight< dist[nextNode])
            {
                // then update distance array
                // dis[i] =      dis + edgeWeight
                dist[nextNode] = dis + weight;
                // and add (dist,node) to min heap
                pq.push(make_pair(dist[nextNode],nextNode));
            }

        }

    }
    printDist(dist);
}


int main(){
    // no of vertexs
    int v=6;
    vector<vector<pair<int,int>>> adj(v);
    addEdge(adj, 0, 1, 4);
    addEdge(adj, 0, 2, 4);
    addEdge(adj, 1, 2, 2);
    addEdge(adj, 2, 3, 3);
    addEdge(adj, 2, 5, 6);
    addEdge(adj, 2, 4, 1);
    addEdge(adj, 3, 5, 2);
    addEdge(adj, 4, 5, 3);

// setting source node as 0; 
    int s=0;
    dij(adj,v,s);

    return 0;
}