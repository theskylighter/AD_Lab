    #include <bits/stdc++.h>
using namespace std;
// namespace std;

class graph
{
public:
    map<int, bool> visited;
    map<int, list<int>> adj;
    stack<int> sort;

    void addEdge(int u, int v)
    {
        //    DIRECTED GRAPH
        adj[u].push_back(v);

        //    UNDIRECTED GRAPH
        // adj[v].push_back(u);
    }

    void dispAdj()
    {

        for (int i = 0; i < adj.size(); i++)
        {
            cout << i << " : ";
            for (int j : adj[i])
            {
                cout << j << " ";
            }
            cout << endl;
        }
    }
//  going till the deepest point of graph and then pushing that point 
//  to the bottom of the stack...
//  SO while printing, ALL child nodes will be printed last 
// AND, ALL parent nodes will be printed firstly from the top
    void topoSortRecur(int v)
    {
        cout << "v:" << v << endl;
        visited[v] = true;

        for (int nbr : adj[v])
        {
            if (!visited[nbr])
                topoSortRecur(nbr);
        }
        sort.push(v);
    }

    void topoSort()
    {
        // calls topo sort for all vertices
        // IN ORDER to Manage disconnected portions also
        for (int i = 0; i < adj.size(); i++)
        {
            if (!visited[i])
            {
                cout << "i : " << i << endl;
                topoSortRecur(i);
            }
        }
        int current;
        cout << "topological sort : \n";
        while (!sort.empty())
        {
            current = sort.top();
            sort.pop();
            cout << current << " ";
        }
    }
};

int main()
{
    graph g;

    // g.addEdge(0, 1);
    // g.addEdge(1, 2);
    // g.addEdge(3, 1);
    // g.addEdge(3, 2);
    g.addEdge(0, 1);
    g.addEdge(1, 2);
    g.addEdge(2,0);
    g.addEdge(2,3);
    g.addEdge(3, 4);
    g.addEdge(4,5);
    g.addEdge(5,6);
    g.addEdge(6,3);

// { 0,1}, { 1, 2 }, { 2, 0 }, { 3, 2 }, { 4, 3 }
    g.dispAdj();
    cout << endl;

    g.topoSort();
    cout << endl;
}