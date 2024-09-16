#include <bits/stdc++.h>
using namespace std;

void floyd(vector<vector<int>> &matrix){
    int n = matrix.size();
    for(int i=0;i<n;i++){
        for(int j=0 ; j<n ;j++){
            if(matrix[i][j]==-1) matrix[i][j]=INT_MAX; //-1 denote that there is no direct path from vertex u to v
        }
    }
    for(int k=0 ; k<n ;k++){
        for(int i=0 ; i<n ;i++){
            for(int j=0 ; j<n ; j++){
                if (matrix[i][k] != INT_MAX && matrix[k][j] != INT_MAX){
                matrix[i][j]=min(matrix[i][j] , matrix[i][k] + matrix[k][j]);}
            }
        }
    }
    for(int i=0;i<n;i++){
        for(int j=0 ; j<n ;j++){
            if(matrix[i][j]==INT_MAX) matrix[i][j]=-1; 
        }
    }
}

int main() {
    vector<vector<int>> matrix = {  { 0, 5, -1, 10 },
                                    { -1, 0, 3, -1 },
                                    { -1, -1, 0, 1 },
                                    { -1, -1, -1, 0} };
    floyd(matrix);
    for (auto row : matrix) {
		for (auto cell : row) {
			cout << cell << " ";
		}
		cout << endl;
	}
    
    return 0;
}