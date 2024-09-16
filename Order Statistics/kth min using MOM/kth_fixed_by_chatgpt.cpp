#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

void swap(int &a, int &b) {
    int temp = b;
    b = a;
    a = temp;
}

tuple<vector<int>, vector<int>, vector<int>> partition(vector<int> &arr, int low, int high, int pivot) {
    vector<int> lowArr;
    vector<int> midArr;
    vector<int> highArr;

    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            lowArr.push_back(arr[j]);
        } else if (arr[j] > pivot) {
            highArr.push_back(arr[j]);
        } else {
            midArr.push_back(arr[j]);
        }
    }

    return {lowArr, midArr, highArr};
}

int findMedian(vector<int> &temp) {
    sort(temp.begin(), temp.end());
    return temp[temp.size() / 2];
}

int selectMedianOfMedian(vector<int> &arr, int low, int high) {
    // BASE Case
    if (arr.size() <= 5) {
        return findMedian(arr);
    } else {
        vector<int> arrOfMed;
        for (int i = low; i < high; i += 5) {
            vector<int> group(arr.begin() + i, arr.begin() + min(i + 5, int(arr.size())));
            arrOfMed.push_back(findMedian(group));
        }
        return selectMedianOfMedian(arrOfMed, 0, arrOfMed.size());
    }
}

int kmin(vector<int> &arr, int k) {
    int low = 0;
    int high = arr.size();
    
    if (arr.empty() || k < 0 || k >= arr.size()) {
        throw out_of_range("Invalid k value or empty array.");
    }

    if (low == high) {
        return arr[low];  // Base case: only one element in array
    }

    int mom = selectMedianOfMedian(arr, low, high);
    auto [lowArr, midArr, highArr] = partition(arr, low, high, mom);

    if (k < lowArr.size()) {
        return kmin(lowArr, k);
    } else if (k >= lowArr.size() + midArr.size()) {
        return kmin(highArr, k - lowArr.size() - midArr.size());
    } else {
        return midArr[0];
    }
}

int main() {
    ifstream fin("kmin.dat");
    if (!fin.is_open()) {
        cerr << "Error opening file!" << endl;
        return 1;
    }

    string line;
    vector<int> arr;

    while (getline(fin, line)) {
        stringstream lin(line);
        string val;
        while (getline(lin, val, ',')) {
            arr.push_back(stoi(val));
        }
    }

    fin.close();

    int k;
    cout << "Enter k: ";
    cin >> k;

    try {
        int kth = kmin(arr, k - 1);
        cout << "k-th smallest element is: " << kth << endl;
    } catch (const exception &e) {
        cerr << e.what() << endl;
    }

    return 0;
}
