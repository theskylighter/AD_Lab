#include <fstream>
#include <bits/stdc++.h>
#include <string>
#include <sstream>
using namespace std;

void quickSortUtil(vector<int> &arr, int low, int high)
{
    if(low<high){
        cout<<"\nlow = "<<low<<", high = "<<high<<endl;

    int pivot = arr[high];
    int i = low-1;
    int j = low;
    for (int j = low; j < high; j++)
        {
            if (arr[j] < pivot)
            {
                i++;
                swap(arr[i], arr[j]);

                 cout<<"\n\t";
        for (int k : arr)
        cout << k << " ";
            }
        }
    //upper loop wont swap pivot ele
    // so doing manually
    swap(arr[i+1],arr[high]);
    
    cout<<"\n\t";
    for (int k : arr)
        cout << k << " ";
    int piv=i+1;

    quickSortUtil(arr, low, piv-1);
    quickSortUtil(arr,piv+1,high);
    }
}

void quickSort(vector<int> &arr)
{
    int n = arr.size();

    quickSortUtil(arr, 0, n - 1);
}

void swap(int &x, int &y)
{
    int temp = y;
    y = x;
    x = temp;
}

int main()
{
    ifstream fin;
    fin.open("unsorted list.dat");
    string line;
    string val;
    vector<int> arr;

    while (getline(fin, line))
    {
        stringstream lin(line);
        string val;
        while (getline(lin, val, ','))
        {
            arr.push_back(stoi(val));
        }
    }
    cout << "printing unsorted list : ";
    
    for (int i : arr)
        cout << i << " ";
    
    cout<< "\n" << endl;


    quickSort(arr);


//after quick sorting
    cout<<"\nAfter Quick Sort : ";

    for (int i : arr)
        cout << i << " ";

    cout<<endl;

    return 0;
}