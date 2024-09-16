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
                if(adjM[i][j]==1){
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

    void bfs(vector<vector<int>>&adjL,int currIndex,vector<bool>&visited){

        queue<int> q;
        q.push(currIndex);
        visited[currIndex]=true;

        while(!q.empty()){
            int popped=q.front();
            q.pop();
            cout<<popped<<" ";

            for(int nbr:adjL[popped]){
                if(!visited[nbr]){
                    visited[nbr]=true;
                    q.push(nbr);
                }
            }
        }
    }
enum State{R,W,V};
    void dfs(vector<vector<int>> &List,int start){
    vector<State> state(List.size(),R);
    stack<int> s;
    s.push(start);
    state[start]=W;

    while (!s.empty())
    {
        int current=s.top();
        s.pop();
        if (state[current]==V)
        {
            continue;
        }
        cout<<current<<" ";
        state[current]=V;
        for (int i : List[current])
        {
            if(state[i]==R){
                s.push(i);
                state[i]=W;
            }
        }  
    }
}




int main() {
    string fname="adjmatrix.txt";
    vector<vector<int>> adjmat = read(fname);
    vector<vector<int>> adjL = adjM_to_adjL(adjmat);
    printlist(adjL);



    int index=0; //starting index
    
    cout<<"\nBFS : "<<endl;
    vector<bool> visited(vertices, false);
    bfs(adjL,index,visited);

    cout<<"\nDFS : "<<endl;
    dfs(adjL,index);
    cout<<endl;
    
    return 0;
}