#include<bits/stdc++.h>
using namespace std;

struct Set{
    int rank;
    int parent;
};
vector<Set> s;
void makeSet(int n){
    s.resize(n);
    for(int i=0; i<n;i++){
        s[i].rank=0;
        s[i].parent=i;
    }
}

int findPar(int node){
    if(s[node].parent==node)
        return node;
    return s[node].parent=findPar(s[node].parent);
}

void Union(int u, int v){
    int x=findPar(u);
    int y=findPar(v);
    if (x==y) {
        cout <<"Parent is same"<<endl;
    }
    else {
        if(s[x].rank>s[y].rank){
            s[y].parent=x;
        }
        if(s[y].rank>s[x].rank){
            s[x].parent=v;
        }
        else {
            s[y].parent=x;
            s[x].rank++;
        }
    }

}
struct Edge {
    int u, v, weight;
};

bool compareEdges(const Edge &a, const Edge &b) {
    return a.weight < b.weight;
}

vector<Edge> kruskal(int n, vector<Edge> &edges) {
    vector<Edge> result;
    makeSet(n);

    sort(edges.begin(), edges.end(), compareEdges);

    for (const Edge &e : edges) {
        int u = e.u;
        int v = e.v;
        if (findPar(u) != findPar(v)) {
            Union(u, v);
            result.push_back(e);
        }
    }

    return result;
}

int main() {
    int n = 4;
    vector<Edge> edges = {
        {0, 1, 10},
        {0, 2, 6},
        {0, 3, 5},
        {1, 3, 15},
        {2, 3, 4}
    };

    vector<Edge> mst = kruskal(n, edges);

    cout << "Edges in the Minimum Spanning Tree:" << endl;
    int totalWeight = 0;
    for (const Edge &e : mst) {
        cout << e.u << " -> " << e.v << ": " << e.weight << endl;
        totalWeight += e.weight;
    }
    cout << "Total weight of MST: " << totalWeight << endl;

    return 0;
}