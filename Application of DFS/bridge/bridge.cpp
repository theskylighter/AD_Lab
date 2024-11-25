#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> read(string &filename ,int &n){
    ifstream file;
    file.open(filename);

    file>>n;
    string line;
    getline(file,line); 
    vector<vector<int>> adjM;

    while(getline(file,line)){
        stringstream ss(line);
        string val;
        vector<int> row;
        while(getline(ss,val,',')){
            row.push_back(stoi(val));
        }
        adjM.push_back(row);
    }
    file.close();
    
    return adjM;

}

void adjM_to_adjL(vector<vector<int>> &adjM , vector<int> list[]){
    int n=adjM.size();
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(adjM[i][j]!=0){
                list[i].push_back(j);
            }
        }
    }  
}

int timer = 0;
void dfs(int node , int parent ,vector<int> &vis , int tin[] , int low[], vector<vector<int>> &bridges, vector<int> adjL[]){
    vis[node]=1;
    tin[node] = low[node] = timer;
    timer++;

    for(auto it : adjL[node]){
        if(it==parent) continue;
        if(!vis[it]){
            dfs(it,node,vis,tin,low,bridges,adjL);
            low[node]=min(low[node],low[it]);
            if(low[it]>tin[node]){
                bridges.push_back({node,it});
            }
        }
        else{
            low[node]=min(low[node],low[it]);
        }
    }

}

vector<vector<int>> Bridges(vector<int> adjL[] ,int n){
    //make a visited array
    vector<int> vis(n,0);
    int tin[n];
    int low[n];
    vector<vector<int>> bridges;

    for (int i = 0; i < n; i++) {
        if (!vis[i]) {
            dfs(i, -1, vis, tin, low, bridges, adjL);
        }
    }
    return bridges;


}

int main() {
    
    string fname="graph.dat";
    int n;
    
    vector<vector<int>> adjM = read(fname,n);
    vector<int> adjL[n];
    adjM_to_adjL(adjM,adjL);
    vector<vector<int>> bridges = Bridges(adjL,n);
    for(auto i:bridges){
        cout<<'['<<i[0]<<','<<i[1]<<']'<<endl;
    }
    
    return 0;
}