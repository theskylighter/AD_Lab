#include <iostream>
#include <vector>

using namespace std;

int merge(vector<int> &arr, int p, int q, int r)
{

    int count = 0;
    int n1 = q - p + 1;
    int n2 = r - q;
    vector<int> L(n1);
    vector<int> R(n2);

    for (int i = 0; i < n1; i++)
    {
        L[i] = arr[p + i];
    }
    for (int i = 0; i < n2; i++)
    {
        R[i] = arr[q + i + 1];
    }
    int i = 0, j = 0, k = p;

    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
            arr[k] = L[i++];
        else
        {
            arr[k] = R[j++];
            count += (n1-i);
        }
        k++;
    }
    while (i < n1)
    {
        arr[k++] = L[i++];
    }
    while (j < n2)
    {
        arr[k++] = R[j++];
    }
    return count;
}
int mergesort(vector<int> &arr, int low, int high)
{
    if (low < high)
    {

        int inv_count = 0;
        int mid = (low + high) / 2;

        inv_count += mergesort(arr, low, mid);
        inv_count += mergesort(arr, mid + 1, high);
        inv_count += merge(arr, low, mid, high);

        return inv_count;
    }
    else 
        return 0;
        // base case.
}

int main()
{
    vector<int> arr = {4, 3, 2, 1};

    cout << "\nINPUT ARRAY : \n";
    for (int i = 0; i < arr.size(); i++)
    {
        cout << arr[i] << " ";
    }
    cout << "\nInversions :" << mergesort(arr, 0, arr.size() - 1);

    cout << endl;
    return 0;
}