#include <bits/stdc++.h>
using namespace std;

bool isupper(const vector<vector<int>> &A){
    int n=A.size();
    for(int i=0;i<n;i++){
        for(int j=0;j<i;j++){
            if(A[i][j]!=0){
                return false;
            }
        }
    }
    return true;
}

bool islower(const vector<vector<int>> &A){
    int n=A.size();
    for(int i=0;i<n;i++){
        for(int j=i+1;j<n;j++){
            if(A[i][j]!=0){
                return false;
            }
        }
    }
    return true;
}

vector<int> forward_subs(const vector<vector<int>> &A, const vector<int> &B){
    
    int n=A.size();
    vector<int> X(n);
    for(int i=0;i<n;i++){
        X[i]=B[i];
        for(int j=0;j<i;j++){
            X[i]-=A[i][j]*X[j];
        }
        X[i]/=A[i][i];
    }
    return X;
}

vector<int> backward_subs(const vector<vector<int>> &A, const vector<int> &B){
    
    int n=A.size();
    vector<int> X(n);
    for (int i = n-1; i >= 0; i--)
    {
        X[i]=B[i];
        for (int j = i+1; j<n; j++)
        {
            X[i] -= A[i][j] * X[j];
        }
        X[i] /= A[i][i];    
    }
    return X;
    
}




int main() {
    ifstream file;
    file.open("matrix.dat");
    if(!file){
        cout<<"Error opening file;"<<endl;
    }
    int n;
    file>>n;
    
    file.ignore();
    vector<vector<int>>A(n,vector<int>(n));
    vector<int> B(n);

    //MAtrix A
    for(int i=0;i<n;i++){
        string line;
        getline(file,line);
        stringstream lin(line);
        string item;
        for(int j=0;j<n;j++){
            getline(lin,item,',');
            A[i][j]=stoi(item);
        }
        
        
    }

    //MAtrix B
    for(int j=0;j<n;j++){
        file>>B[j];
    }

    
    if(islower(A)){
        cout<<"Matrix A is lower triangular matrix."<<endl;
        vector<int> X= forward_subs(A,B);
        cout<<"Solution matrix  X:"<<endl;
        for(int i:X){
            cout<<i<<endl;
        }

    }
    else if (isupper(A))
    {
        cout<<"MAtrix A is upper triangular matrix."<<endl;
        vector<int> X= backward_subs(A,B);
        cout<<"Solution matrix  X:"<<endl;
        for(int i:X){
            cout<<i<<endl;
        } 
    }
    else{
        cout<<"Matrix A is neither upper triangular nor lower triangular."<<endl;
    }


    
    return 0;
}