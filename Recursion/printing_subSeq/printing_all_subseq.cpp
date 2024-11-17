#include<bits/stdc++.h>
using namespace std;
void f(int ind, vector<int>&m,vector<int> &arr, int n){
    // cout<<"ind = "<<ind<<endl;
    if(ind==n){
        // BASE CASE : print m[]
        for(auto i:m){
            cout<<i<<" ";
        }
        cout<<endl;
        return;
    }

    m.push_back(arr[ind]);
    f(ind+1,m,arr,n);
    m.pop_back();
    f(ind+1,m,arr,n);
}


int main(){
vector<int> arr;

ifstream fin("input.txt");

string line;
getline(fin,line);
stringstream ss(line);
string token;

    while(getline(ss,token,',')){
        arr.push_back(stoi(token));
        // cout<<token;
    }

// f(index,empty array)
vector<int> m;
f(0,m,arr,arr.size());

return 0;
}