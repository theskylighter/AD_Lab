#include<bits/stdc++.h>
using namespace std;
void f(int ind, vector<int>&m){
    
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
vector<int> m(arr.size());
f(0,m);
// cout<<arr[1]<<endl;
return 0;
}