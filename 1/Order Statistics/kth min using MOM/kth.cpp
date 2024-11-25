#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

void swap(int &a, int &b)
{
    int temp = b;
    b = a;
    a = temp;
}
tuple<vector<int>, vector<int>, vector<int>> partition(vector<int> &arr, int low, int high, int pivot)
{

    vector<int> lowArr;
    vector<int> midArr;
    vector<int> highArr;

    for (int j = low; j <= high; j++)
    {
        if (arr[j] < pivot)
        {
            lowArr.push_back(arr[j]);
        }
        else if (arr[j] > pivot)
        {
            highArr.push_back(arr[j]);
        }
        else
        {
            midArr.push_back(arr[j]);
        }
    }

    return {lowArr, midArr, highArr};
}

int findMedian(vector<int> &temp)
{
    sort(temp.begin(), temp.end());
    return temp[temp.size() / 2];
    // returns median element
}

int selectMedianOfMedian(vector<int> &arr, int low, int high)
{
    // BASE Case
    if (arr.size() <= 5)
        return findMedian(arr);
    
    // DO grouping & find medians
    else
    {
        vector<int> arrOfMed;
        for (int i = low; i <= high; i += 5)
        {
            vector<int> group(arr.begin() + i, arr.begin() + min(i + 5, int(arr.size())) );
            arrOfMed.push_back(findMedian(group));
        }
        return selectMedianOfMedian(arrOfMed, 0, arrOfMed.size());
    }
}

int kmin(vector<int> &arr, int k)
{
    int low = 0;
    int high = arr.size()-1;
    
    if(arr.size()==1){
        return arr[0];
    }
        // mom is Pivot basically
        int mom = selectMedianOfMedian(arr, low, high);
        // pivIndex
        auto [lowArr, midArr, highArr] = partition(arr, low, high, mom);

        if (k < lowArr.size())
        {
            return kmin(lowArr, k);
        }
        else if (k >= lowArr.size() + midArr.size())
            return kmin(highArr, k-lowArr.size()-midArr.size());
        else
            return midArr[0];
    
}

int main()
{
    ifstream fin;
    fin.open("kmin.dat");
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
    int k;
    cout << "enter k" << endl;
    cin >> k;

    // k-1 because k (input) is 1 indexed but our indices are 0 indexed so to fix that....
    //  for ex: 4th min will be at pivIndex = 3
    int kth = kmin(arr, k - 1);

    cout << "kth smallest is :"<<kth<<endl;

    return 0;
}