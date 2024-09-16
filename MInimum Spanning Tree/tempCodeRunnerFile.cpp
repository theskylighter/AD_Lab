#include <iostream>
#include <vector>
#include <algorithm>
#include <stdlib.h>
#include <queue>
using namespace std;

void addEdge(vector<vector<pair<int, int>>> &adj, int w, int i, int j)
{
    // graph strored as (node,weight)
    adj[i].push_back(make_pair(j, w));
    adj[j].push_back(make_pair(i, w));
}
void print_adj(vector<vector<pair<int, int>>> &adj,int v){
    cout<<"\nAdjacency list ="<<endl;
    for(int i=0;i< v;i++){
        cout<<"\n"<<i<<" : ";
        for(auto it:adj[i])
            cout << "{" << it.first << "," << it.second << "} ";
    }

}
void print_MST(vector<pair<int, int>> &MST, int &sum)
{
    cout << "\n\nWeight of MST = " << sum << endl;
    cout<<"MST = ";
    for (auto it : MST)
    {
        cout << "{" << it.first << "," << it.second << "} ";
    }
    cout << endl;
}

void prims(vector<vector<pair<int, int>>> &adj, int v)
{
    priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> pq;
    vector<int> vis(v, 0);
    vector<pair<int, int>> MST;
    int sum = 0;

    // weight, node, parent
    pq.push({{0, 0, -1}});

    while (!pq.empty())
    {
        int wt = pq.top()[0];
        int node = pq.top()[1];
        int parent = pq.top()[2];
        pq.pop();

        // if node not visited
        if (vis[node] != 1)
        {

            vis[node] = 1;
            sum += wt;
            if(parent!=-1)
                MST.push_back(make_pair(parent,node));

            // add neighbors to pQ
            for (auto it : adj[node])
            {
                if (vis[it.first] != 1)
                {
                    // push (weight, nbr node, parent)
                    pq.push({it.second, it.first, node});
                }
            }
        }
    }
    print_MST(MST, sum);
}

int main()
{
    // no of vertexs
    int v = 6;
    vector<vector<pair<int, int>>> adj(v);
    //        (weight,i,j)
    addEdge(adj, 4, 0, 1);
    addEdge(adj, 4, 0, 2);
    addEdge(adj, 2, 1, 2);
    addEdge(adj, 3, 2, 3);
    addEdge(adj, 6, 2, 5);
    addEdge(adj, 1, 2, 4);
    addEdge(adj, 2, 3, 5);
    addEdge(adj, 3, 4, 5);

    print_adj(adj,v);
    prims(adj, v);
    return 0;
}
