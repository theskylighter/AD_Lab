#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <iostream>
using namespace std;

int partitionIndex(vector<int> &arr, int low, int high)
{
    int piv;

    int pivot = arr[high];
    int i = low - 1;
    int j;
    for (j = low; j < high; j++)
    {
        if (arr[j] < pivot)
        {
            i++;
            swap(arr[i], arr[j]);

            cout << "\n\t";

            for (int k : arr)
                cout << k << " ";
        }
    }
    // upper loop wont swap pivot ele
    //  so doing manually
    swap(arr[i + 1], arr[high]);

    cout << "\n\t";
    for (int k : arr)
        cout << k << " ";

    piv = i + 1;

    return piv;
}

void quickSort(vector<int> &arr, int low, int high)
{
    if (low < high)
    {
        cout << "\nlow = " << low << ", high = " << high << endl;
        int piv = partitionIndex(arr, low, high);

        quickSort(arr, low, piv - 1);
        quickSort(arr, piv + 1, high);
    }
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

    cout << "\n"
         << endl;

    quickSort(arr, 0, arr.size() - 1);

    // after quick sorting
    cout << "\nAfter Quick Sort : ";

    for (int i : arr)
        cout << i << " ";

    cout << endl;

    return 0;
}