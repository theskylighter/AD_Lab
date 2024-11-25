#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include<bits/stdc++.h>

using namespace std;

// Function to read input from a file
vector<float> readInputFile(const string& filename) {
    vector<float> array;
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Could not open the file " << filename << endl;
        return array;
    }

    float number;
    char comma;
    while (file >> number) {
        if (number == -1) break;  // Stop if -1 is encountered
        array.push_back(number);
        file >> comma;  // Read the comma delimiter
    }
    file.close();
    return array;
}

// Bubble Sort
void bubbleSort(vector<float>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// Selection Sort
void selectionSort(vector<float>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        swap(arr[i], arr[minIndex]);
    }
}

// Insertion Sort
void insertionSort(vector<float>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        float key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// Helper function for counting sort used in radix sort 
void counting_Sort(vector<int> &temp, int n, int k){
    vector<int> ans(n);
    int count[10] = {0};

    //storing the count
    for(int i = 0; i < n; i++){
        count[(temp[i]/k) % 10]++;
    }

    for(int i = 1; i < 10; i++){
        count[i] += count[i-1];
    }

    //make ans array
    for(int i = n-1; i >= 0; i--){
        ans[count[(temp[i]/k) % 10] - 1] = temp[i];
        count[(temp[i] / k) % 10]--;
    }

    for (int i = 0; i < n; i++) {
        temp[i] = ans[i];
    }
}

void radixSort(vector<float> &arr){
    int n = arr.size();
    vector<int> temp(n);

    for(int i = 0; i < n; i++){
        temp[i] = static_cast<int>(round(arr[i]));
    }

    int maxEle = *max_element(temp.begin(), temp.end());
    for(int i = 1; maxEle/i > 0; i *= 10){
        counting_Sort(temp, n, i);
    }

    for (int i = 0; i < n; i++) {
        arr[i] = temp[i];
    }
}

// Function to print the array
void printArray(const vector<float>& arr) {
    
    for (float num : arr) {
        cout << num << " ";
    }
    cout << endl;
}

int main() {
    string filename = "input.dat";
    vector<float> array = readInputFile(filename);

    if (array.empty()) {
        return 1;  // Exit if the array could not be loaded
    }

    // Printing the original array
    cout << "Original Array "<< endl;
    printArray(array);

    // Bubble Sort
    vector<float> bubbleSorted = array;
    bubbleSort(bubbleSorted);
    cout <<"\n Bubble Sorted: ";
    printArray(bubbleSorted);

    // Selection Sort
    vector<float> selectionSorted = array;
    selectionSort(selectionSorted);
    cout << "\n Selection Sorted : ";
    printArray(selectionSorted);

    // Insertion Sort
    vector<float> insertionSorted = array;
    insertionSort(insertionSorted);
    cout << "\n Insertion Sorted: ";
    printArray(insertionSorted );

    // Radix Sort (only for integers)
    vector<float> radixSorted = array;
    radixSort(radixSorted);
    cout << "\n Radix Sorted "<< ": ";
    printArray(radixSorted);

    return 0;
}
