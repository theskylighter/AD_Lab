// // Write a C++ program to solve equation Ax = b for x. Here A is n×n matrix and b is a n×1 vector.

// Read A and b from a file matrix.dat. This file has 2n+1 lines. First line has only one positive integer ie value of n.
// Next n rows have rows of matrix A, entries in a row are separated by comma.
// Next n rows have one integer each corresponding to element of b.

// Your program should check if A is lower triangular or upper triangular and then solve for x using forward / backward substitution.
// Otherwise program should generate an exception.
#include <iostream>
#include <fstream>
#include <bits/stdc++.h>
#include <string>
// #include<strstream>
using namespace std;

int n;
vector<vector<int>> matA;
vector<int> matB;

void read(string &filename)
{

    ifstream file;
    file.open(filename);

    if (!file.is_open())
    {
        cout << "error opening file" << endl;
    }
    else
    {
        file >> n;
        
        file.ignore();
        int count = 1;
        cout << "opening file" << endl;
        string line;
        while (getline(file, line))
        {

            stringstream lin(line);
            string val;
            vector<int> row;

            if (count <= n)
            {
                while (getline(lin, val, ','))
                {
                    row.push_back(stoi(val));
                }
                matA.push_back(row);
                count++;
            }
            else if (count >= n && count <= 2 * n + 1)
            {
                while (getline(lin, val))
                {
                    matB.push_back(stoi(val));
                    count++;
                }
            }
        }
    }
}

void printAB()
{
    cout << "printing A" << endl;
    for (auto i : matA)
    {
        for (auto j : i)
        {
            cout << j << " ";
        }
        cout << endl;
    }
}
bool isUpper()
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < i; j++)
        {
            if (matA[i][j] != 0)
                return false;
        }
    }
    return true;
}
bool isLower()
{
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (matA[i][j] != 0)
                return false;
        }
    }
    return true;
}

vector<int> forwardSub()
{
    vector<int> x(n);

    for (int i = 0; i < n; i++)
    {
        x[i] = matB[i];
        for (int j = 0;j<i;j++)
        {
            x[i] = x[i] - matA[i][j] * x[j];
        }
        x[i]= x[i]/matA[i][i];
    }
    return x;
}
vector<int> backwardSub(){
    vector<int> x(n);
    
    
    for (int i = n-1; i>=0; i--)
    {
        x[i] = matB[i];
        for (int j = i+1;j<n;j++)
        {
            x[i] = x[i] - matA[i][j] * x[j];
        }
        x[i]= x[i]/matA[i][i];
    }
    return x;

}

int main()
{
    string fname = "matrix.dat";
    read(fname);
    // printAB();

    if(n<100){
    if (isLower())
    {
        cout << "it is lower  triangular matrix" << endl;
        vector<int> ans=forwardSub();
        cout<<"solution:"<<endl;
        for(int i:ans){
            cout<<i<<endl;
        }

    }
    else if (isUpper())
    {
        cout << "it is Upper  triangular matrix" << endl;
        vector<int> ans=backwardSub();
        cout<<"solution:"<<endl;
        for(int i:ans){
            cout<<i<<endl;
        }
    }
    else
    {
        cout << "neither uppper nor lower triangular matrix" << endl;
    }
    }

    else{
    cout<<"Enter size between 0 to 100"<<endl;
    }    
    return 0;
}