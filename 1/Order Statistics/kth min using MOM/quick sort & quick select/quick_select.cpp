#include <fstream>
#include <bits/stdc++.h>
#include <string>
#include <sstream>
using namespace std;

int quickSortUtil(vector<int> &arr, int low, int high,int k)
{
    if(low<high){
        cout<<"\n\nlowIn = "<<low<<", highIn = "<<high<<", pivot ="<<arr[high]<<endl;
// pivot Element
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

// Printing array to see the current status
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
// pivot Index
    int piv=i+1;
// modification for quickSelect 
    if(k<piv)
    return quickSortUtil(arr, low, piv-1,k);
    else if(k>piv)
    return quickSortUtil(arr,piv+1,high,k);
    else
    return arr[piv];
    }
}

void quickSort(vector<int> &arr,int k)
{
    int n = arr.size();

    int kthMin=quickSortUtil(arr, 0, n - 1,k);
    cout<<"\nkth min = "<<kthMin<<endl;

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
    
    int k;
    cout<< "\nEnter k :";
    cin>>k;
    
    cout<< endl;
// sending k-1 because, k was 1 indexed(general lang) while our array indices are 0 indexed, so to fix that...
// 4th min should be found at index = 3 
    quickSort(arr,k-1);

    cout<<endl;

    return 0;
}