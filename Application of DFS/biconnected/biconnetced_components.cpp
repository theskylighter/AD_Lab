#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> read(string &f_name, int &n)
{
    ifstream file;
    file.open(f_name);

    file >> n;
    string line;
    getline(file, line); // this is used to read the rem of line containing n ,i.e. any ("\n") character is read

    vector<vector<int>> adjmatx;

    while (getline(file, line))
    {
        stringstream lin(line);
        string val;
        vector<int> row;
        while (getline(lin, val, ','))
        {
            row.push_back(stoi(val));
        }
        adjmatx.push_back(row);
    }
    file.close();
    return adjmatx;
}

void adjM_to_adjL(vector<vector<int>> &adjM, vector<int> list[])
{
    int n = adjM.size();
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (adjM[i][j] != 0)
            {
                list[i].push_back(j);
            }
        }
    }
}

int timer = 1;

void dfs(int node, int parent, vector<int> &vis, int disc[], int low[], vector<int> adj[], stack<pair<int, int>> &st, vector<vector<pair<int, int>>> &biComp)
{
    vis[node] = 1;
    disc[node] = low[node] = timer;
    timer++;
    int child = 0;
    for (auto nbr : adj[node])
    {
        if (nbr == parent)
            continue;
        if (!vis[nbr])
        {
            st.push({node, nbr});
            dfs(nbr, node, vis, disc, low, adj, st, biComp);
            low[node] = min(low[node], low[nbr]);
            if (low[nbr] >= disc[node])
            {

                vector<pair<int, int>> component;
                while (!st.empty() && st.top() != make_pair(node, nbr))
                {
                    component.push_back({st.top().first, st.top().second});
                    st.pop();
                }
                component.push_back({node, nbr});
                st.pop();
                biComp.push_back(component);
            }
            child++;
        }
        else if (disc[nbr] < disc[node])
        {
            low[node] = min(low[node], disc[nbr]);
            st.push({node, nbr});
        }
    }
}

vector<vector<pair<int, int>>> BiconnectedComp(int n, vector<int> adj[])
{
    vector<int> vis(n, 0);
    int disc[n];
    int low[n];
    stack<pair<int, int>> st;
    vector<vector<pair<int, int>>> biComp;

    for (int i = 0; i < n; i++)
    {
        if (!vis[i])
        {
            dfs(i, -1, vis, disc, low, adj, st, biComp);
            if (!st.empty())
            {
                vector<pair<int, int>> component;
                while (!st.empty())
                {
                    component.push_back(st.top());
                    st.pop();
                }
                biComp.push_back(component);
            }
        }
    }

    return biComp;
}

int main()
{
    string fname = "graph.dat";
    int n;
    vector<vector<int>> adjmat = read(fname, n);
    vector<int> adjL[n];
    adjM_to_adjL(adjmat, adjL);

    vector<vector<pair<int, int>>> biComp = BiconnectedComp(n, adjL);

    cout << "Biconnected components:\n";
    for (auto &component : biComp)
    {
        for (auto &edge : component)
        {
            cout << "(" << edge.first + 1 << ", " << edge.second + 1 << ") ";
        }
        cout << endl;
    }

    return 0;
}