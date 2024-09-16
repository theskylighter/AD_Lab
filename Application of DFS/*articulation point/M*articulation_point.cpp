// Write a C++program that reads adjacency matrix of a graph from file graph.dat and outputs all articulation points

// File graph.dat contains n+1 lines where n is number of vertices. First line is value of n and next n lines are respective rows of adjacency matrix.

// Each cell in adjacency matrix denotes the weight of edge.

#include <iostream>
#include<fstream>
#include<vector>
#include<sstream>
#include<queue>
#include<stack>
using namespace std;

int vertices;
vector<vector<int>> read(string &f_name){
    ifstream file(f_name);


    file>>vertices;

    string line;
    getline(file,line);

    vector<vector<int>> adjmatx;

    while(getline(file,line)){
        stringstream lin(line);
        string val;
        vector<int> row;
        while (getline(lin,val,','))
        {
            row.push_back(stoi(val));
        }
        adjmatx.push_back(row);
    }
    return adjmatx;
}
    vector<vector<int>> adjM_to_adjL(vector<vector<int>> &adjM){
        int n=adjM.size();
        vector<vector<int>> list(n);
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                if(adjM[i][j]!=0){
                    list[i].push_back(j);
                }
            }
        }
        return list ;
        
    }
    


void printlist(vector<vector<int>> &List){
        int n=List.size();
        for(int i=0; i<n; i++){
            cout << i << ": ";
            for(int j=0; j< (List[i].size()); j++){
                cout << List[i][j] << " ";
            }
        cout << endl;
        }
    }

int main() {
    string fname="graph.dat";
    vector<vector<int>> adjmat = read(fname);
    vector<vector<int>> adjL = adjM_to_adjL(adjmat);
    printlist(adjL);

    
    return 0;
}