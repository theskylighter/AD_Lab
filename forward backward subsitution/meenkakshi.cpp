#include <bits/stdc++.h>
using namespace std;
int n;
vector<vector<int>> mat;
vector<int> Read_mat (string &filename){
    ifstream fread;
    fread.open(filename);
    if (!fread.is_open())
        cout<<"Error opening file"<<endl;
    fread>>n;
    string line;
    int i=0;
    while(getline(fread,line)&& i<n){
        stringstream ss(line);
        string value;
        int j=0;
        while (getline(ss, value, ',')) {
                    mat[i][j] = stoi(value);
                    j++;
                }
        i++;
    }
    vector<int>b(n);
    for (int i=0;i<n;i++){
        string ch;
        fread>>ch;
        b[i]=stoi(ch);
        }
    return b;
}

bool isUpper (vector<vector<int>> matrix){
    for (int i=0;i<n; i++){
        for (int j=0;j<=i;j++){
            if (matrix[i][j]!=0) return false;
            }
        }
    return true;
}

bool isLower (vector<vector<int>> matrix){
    for (int i=0;i<n; i++){
        for (int j=n;j>i;j--){
            if (matrix[i][j]!=0) return false;
            }
        }
    return true;
}

vector<int> Forward_sub(vector<vector<int>> L,vector<int>b){
    vector<int>x(n);
    for (int i=0;i<n;i++){
        x[i]=b[i];
            for (int j=0;j<i;j++){
                    x[i]=x[i]-(L[i][j]*x[j]);
            x[i] = x[i]/L[i][i];
        }
    }
    return x;
}

vector<int> Backward_sub(vector<vector<int>> U, vector<int>b){
    vector<int>x(n);
    for (int i=n-1;i>=0;i--){
        x[i]=b[i];
            for (int j=i+1;j<n;j++){
                    x[i]=x[i]-(U[i][j]*x[j]);
            x[i] = x[i]/U[i][i];
        }
    }
    return x;
}

int main(){
    string fname="matrix.dat";
    vector<int> b= Read_mat(fname);
    int n=mat.size();
    cout<<"Printing the matrix"<<endl;
    for (int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cout<< mat[i][j]<<" ";
            }
        cout<< endl;
        }
    if (isUpper(mat)){
        vector<int>x = Backward_sub(mat,b);
        for (int i=0;i<x.size();i++){
            cout<<x[i]<<endl;
        }
        }
    else if(isLower(mat)){
        vector<int>x =Forward_sub(mat,b);
        for (int i=0;i<x.size();i++){
            cout<<x[i]<<endl;
        }
    }
    else {
        cout<<"The matrix is not a Upper Triangular or a Lower Triangular matrix"<<endl;
    }
    return 0;
}