// Write a C++ program to solve maximum sum subarray problem recursively. Program should read comma separated values of an array from a file mss.dat. Sequence of elements of array is terminated by -999.

// Program should output indices as well as elements of maximum subarray as decided in conquer phase. It should prefix output by printing L (if solution came from left half) or R(if it was from right half) or M.

// This has to be completed and submitted within lab class

#include <bits/stdc++.h>
using namespace std;
struct ans
{
    int leftIndex;
    int rightIndex;
    int sum;
    // char prefix; // L R or M
};

void read(vector<int> &arr, string &filename)
{

    fstream fin;
    fin.open(filename);
    if (fin.is_open() != true)
    {
        cout << "error opening file";
    }
    else
    {
        string line;
        while (getline(fin, line))
        {

            stringstream lin(line);
            string val;
            while (getline(lin, val, ','))
            {
                if (stoi(val) == -999)
                    break;
                arr.push_back(stoi(val));
            }
        }
        cout << "\n\nInput Array :" << endl;
        for (int i : arr)
            cout << i << ' ';
    }
}
ans maxCrossingSum(vector<int> &arr, int low, int mid, int high)
{
    int leftSum=INT_MIN;
    int sum=0;
    int maxLeft=mid; //leftIndex
    for(int i=mid;i>=low;i--){
        sum+=arr[i];
        if(sum> leftSum){
            leftSum=sum;    
            maxLeft= i;
        }
    }
    int rightSum=INT_MIN;
     sum=0;
    int maxRight=mid;
    for(int j=mid+1;j<=high;j++){
        sum+=arr[j];
        if(sum> rightSum){
            rightSum=sum;
            maxRight= j;
        }
    }
    return {maxLeft,maxRight,leftSum+rightSum};
}
ans maxRecur(vector<int> &arr, int low, int high)
{
    if (low == high)
        return {low, high, arr[low]}; // BASE Case only 1 element
    else
    {
        int mid = (low + high) / 2;

        ans leftAns = maxRecur(arr, low, mid);
        ans rightAns = maxRecur(arr, mid + 1, high);
        ans crossAns = maxCrossingSum(arr, low, mid, high);

        // RETURN
        if(leftAns.sum>=rightAns.sum&&leftAns.sum>=crossAns.sum){
            return {leftAns.leftIndex,leftAns.rightIndex,leftAns.sum};
        }
        else if(rightAns.sum>=leftAns.sum&&rightAns.sum>=crossAns.sum){
            return {rightAns.leftIndex,rightAns.rightIndex,rightAns.sum};
        }
        else{
            return {crossAns.leftIndex,crossAns.rightIndex,crossAns.sum};
        }
    }
}

void maxSumSubarray(vector<int> &arr)
{
    // int sum = INT_MIN;
    int n = arr.size();
    ans a1 = maxRecur(arr, 0, n - 1);
    // printing ANSWER;
    cout<<"\n[i,j]"<<" "<<"SUM"<<endl;
    cout<<'['<<a1.leftIndex<<','<<a1.rightIndex<<"] "<<a1.sum<<endl;
}

int main()
{
    vector<int> arr;
    string filename = "mss.dat";
    read(arr, filename);
    cout << endl;

    maxSumSubarray(arr);
    return 0;
}