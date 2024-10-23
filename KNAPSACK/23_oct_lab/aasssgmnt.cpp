#include <iostream>
#include <fstream>
using namespace std;

void searchInMatrix(int matrix[][100], int n, int key) {
    int i = 0; 
    int j = n - 1; 

    while (i < n && j >= 0) {
        if (matrix[i][j] == key) {
            cout << "Key found at (" << i << "," << j << ")" << endl;
            return;
        } if (matrix[i][j] > key) {
            cout<<"Key not found at ("<<i<<","<<j<<") moving  left"<<endl;
            j--; 
        } else {
            cout<<"Key not found at ("<<i<<","<<j<<") moving  down"<<endl;
            i++; 
            if(matrix[i][j]>key)
            {break;}
        }
    }
    cout << "Key not found in Matrix" << endl;
}

int main() {
    ifstream inputFile("matrix_input.txt"); 
    if (!inputFile) {
        cerr << "Error opening file!" << endl;
        return 1;
    }
    
    int n, key;

    inputFile >> n;

    int matrix[100][100]; 

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            inputFile >> matrix[i][j];
            cout<<matrix[i][j]<<" ";
        }
        cout<<endl;
    }

    inputFile >> key;

    inputFile.close();

    searchInMatrix(matrix, n, key);

    return 0;
}