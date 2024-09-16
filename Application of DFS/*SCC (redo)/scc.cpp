#include <iostream>
#include <vector>
#include <list>
#include <unordered_map>
#include <stack>
using namespace std;

// Depth-First Search to fill the stack with nodes in the order of their finishing times
void dfs(int node, unordered_map<int, bool> &visited, unordered_map<int, list<int>> &adj, stack<int> &st) {
    visited[node] = true;
    for (auto i : adj[node]) {
        if (!visited[i]) {
            dfs(i, visited, adj, st);
        }
    }
    st.push(node); // Push the node to the stack after visiting all its neighbors
}

// Reverse DFS to collect all nodes in the current SCC
void revdfs(int node, unordered_map<int, list<int>> &rev_adj, stack<int> &st, unordered_map<int, bool> &visited, vector<int> &temp) {
    visited[node] = true;
    temp.push_back(node); // Add the node to the current SCC
    for (auto nbr : rev_adj[node]) {
        if (!visited[nbr]) {
            revdfs(nbr, rev_adj, st, visited, temp);
        }
    }
}

// Function to find all Strongly Connected Components (SCCs) in a directed graph
vector<vector<int>> SCC(vector<vector<int>> &edges, int v) {
    // Creating ADJACENCY LIST
    unordered_map<int, list<int>> adj;
    stack<int> st;
    for (auto edge : edges) {
        int u = edge[0];
        int v = edge[1];
        adj[u].push_back(v); // Add edge to the adjacency list
    }

    // Step 1: Perform DFS on the original graph to fill the stack
    unordered_map<int, bool> visited;
    for (int i = 0; i < v; i++) {
        if (!visited[i]) {
            dfs(i, visited, adj, st);
        }
    }

    // Step 2: Transpose the graph
    unordered_map<int, list<int>> rev_adj;
    for (auto edge : edges) {
        int u = edge[0];
        int v = edge[1];
        rev_adj[v].push_back(u); // Reverse the direction of the edge
    }

    // Step 3: Perform DFS on the transposed graph
    visited.clear();
    vector<vector<int>> sccs;
    while (!st.empty()) {
        int node = st.top();
        st.pop();
        if (!visited[node]) {
            vector<int> temp;
            revdfs(node, rev_adj, st, visited, temp);
            sccs.push_back(temp); // Add the current SCC to the list of SCCs
        }
    }

    return sccs; // Return the list of SCCs
}