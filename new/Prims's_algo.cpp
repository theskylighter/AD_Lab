#include <bits/stdc++.h>
using namespace std;

//find minimum key value from vertices not included in mst
int min_index(int key[] ,bool in_mst[] , int V){
    //V= no of vertices
    int min=INT_MAX , min_index;
    for(int i=0;i<V;i++){
        if(in_mst[i]==false && key[i] < min){
            min = key[i];
            min_index=i;
        }
    }
    return min_index;
}

void print_g(int parent[],vector<vector<int>> graph , int V){
    cout << "Edge \tWeight\n";
    for (int i = 1; i < V; i++)
        cout << parent[i] << " - " << i << " \t"
             << graph[i][parent[i]] << " \n";
}

void primMST(vector<vector<int>> graph , int V){

    //array to store constructed MST
    int parent[V];

    bool in_mst[V];

    int key[V];

    for(int i=0 ; i<V ; i++){
        key[i]=INT_MAX ;
        in_mst[i] = false;
    }

    key[0] = 0 ;//make key 0 as first vertex
    parent[0]=-1; //root node

    //first node = root of MST
    for (int count = 0; count< V-1 ; count++)
    {
        int a = min_index(key , in_mst , V);
        in_mst[a] = true;

        for (int v = 0; v < V; v++)
        {
            if(graph[a][v] && in_mst[v]==false && graph[a][v]<key[v]){
                parent[v]=a;
                key[v]=graph[a][v];
            }
        }
        
    }
    print_g(parent,graph , V);

    
}


int main() {
    vector<vector<int>> graph= { { 0, 2, 0, 6, 0 },
                        { 2, 0, 3, 8, 5 },
                        { 0, 3, 0, 0, 7 },
                        { 6, 8, 0, 0, 9 },
                        { 0, 5, 7, 9, 0 } };

   
    primMST(graph,5);
    
    return 0;
}