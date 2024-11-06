#include<iostream>
#include<vector>

using namespace std;
// QUICKSORT
// MERGE SORT
// HEAP SORT
int partition(vector<int>& arr , int low ,int high){
    int pivot = arr[high];
    int i= low-1;
    int j;
    for (j = low; j <= high - 1; ++j) {
        if (arr[j] < pivot) {
            ++i;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i+1],arr[high]);
    return i+1;
}

void QuickSort(vector<int>& arr , int low ,int high){
    if(low < high){
        int part_index = partition(arr,low,high);

        QuickSort(arr,low,part_index-1);
        QuickSort(arr,part_index+1,high);
    }
}

void merge(vector<int> &arr, int p, int q, int r){

    int n1=q-p+1;
    int n2= r-q;
    vector<int> L(n1);
    vector<int> R(n2);

    for(int i=0;i<n1;i++)
    {
     L[i]=arr[p+i];   
    }
    for(int i=0;i<n2;i++)
    {
     R[i]=arr[q+i+1];   
    }
int i=0,j=0,k=p;

    while(i<n1&&j<n2){
        if(L[i]<R[j])
            arr[k] = L[i++];
        else{
            arr[k] = R[j++];
        }
        k++;
    }
    while(i<n1){
        arr[k++]=L[i++];
    }
    while(j<n2){
        arr[k++]=R[j++];
        
    }

    
}
void mergesort(vector<int>&arr,int low,int high){
if(low<high){


int mid= (low+high)/2;

mergesort(arr,low,mid);
mergesort(arr,mid+1,high);
merge(arr,low,mid,high);
}
}

int main(){
    vector<int> arr={2,9,3,6,7,12,8,20};
    
    cout<<"\nINPUT ARRAY : \n";
    for(int i=0;i<arr.size();i++){
        cout<<arr[i]<<" ";
    }
    mergesort(arr,0,arr.size()-1);

    cout<<"\nafter merge sort ARRAY : \n";
    for(int i=0;i<arr.size();i++){
        cout<<arr[i]<<" ";
    }

    cout<<endl;
    return 0;
}