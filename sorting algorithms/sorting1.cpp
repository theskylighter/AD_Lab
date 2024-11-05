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
void countingSortForRadix(vector<int>& arr, int k) {
    int n = arr.size();
    vector<int> output(n);
    int count[10] = {0};

    for (int i = 0; i < n; i++) {
        int index = (arr[i] / k) % 10;
        count[index]++;
    }

    for (int i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }

    for (int i = n - 1; i >= 0; i--) {
        int index = (arr[i] / k) % 10;
        output[count[index] - 1] = arr[i];
        count[index]--;
    }

    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
    }
}

// Radix Sort (only for integers)
void radixSort(vector<float>& arr) {

    vector<int> intArr(arr.begin(), arr.end());  // Convert to integers for radix sort

    int maxVal=INT_MIN;
    for(int i=0;i<arr.size();i++){
        if(arr[i]>maxVal){
            maxVal=arr[i];
        }
    }
    // int maxVal = *max_element(intArr.begin(), intArr.end());

    for (int k = 1; maxVal / k > 0; k *= 10) {
        countingSortForRadix(intArr, k);
    }

    for (int i = 0; i < arr.size(); i++) {
        arr[i] = intArr[i];
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
