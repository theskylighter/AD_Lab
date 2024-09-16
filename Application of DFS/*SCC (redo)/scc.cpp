#include <iostream>
#include <vector>
#include <list>
#include <unordered_map>
#include <stack>
using namespace std;

void dfs(int node, unordered_map<int, bool> &visited, unordered_map<int, list<int>> &adj, stack<int> &st){
    visited[node] = true;
    for(auto i : adj[node]){
        if(!visited[i]){
            dfs(i,visited,adj,st);
        }
    }
    st.push(node);
}

void revdfs(int node, unordered_map<int, list<int>> &rev_adj, stack<int> &st, unordered_map<int, bool> &visited, vector<int> &temp){
    visited[node] = true;
    temp.push_back(node);
    for(auto nbr : rev_adj[node]){
        if(!visited[nbr]){
            revdfs(nbr,rev_adj,st,visited,temp);
        }
    }
}

vector<vector<int>> SCC(vector<vector<int>> &edges, int v){
    
    //  Creating ADJACENCY  LIST
    unordered_map<int, list<int>> adj;
    stack<int> st;
    for(auto edge : edges){
        int u = edge[0];
        int v = edge[1];

        adj[u].push_back(v);
    }

    unordered_map<int, bool> visited;
    vector<vector<int>> ans;

    for(int i = 0; i < v; i++){
        if(!visited[i]){
            dfs(i,visited,adj,st);
        }
    }

    //creating REVERSED adj list
    unordered_map<int, list<int>> rev_adj;
    for(int i = 0; i < v; i++){
        visited[i] = false;
        for(auto j : adj[i]){
            rev_adj[j].push_back(i);
        }
    }

    while(!st.empty()){
        int top = st.top();
        st.pop();
        if(!visited[top]){
            vector<int> temp;
            revdfs(top,rev_adj,st,visited,temp);
            ans.push_back(temp);
        }
    }

    return ans;
}

int main()
{
    int V = 5;
    vector<vector<int> > edges{{ 0,1}, { 1, 2 }, { 2, 0 }, { 3, 2 }, { 4, 3 }};

    vector<vector<int>> ans;
    ans = SCC(edges, V);
    
    cout << "Strongly Connected Components are:\n";
    for (auto x : ans) {
        for (auto y : x) {
            cout << y << " ";
        }
        cout << "\n";
    }
    return 0;
}