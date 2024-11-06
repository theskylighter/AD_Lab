#include<iostream>
#include<vector>
using namespace std;

void swap(int& a,int& b){
    int temp=a;
    a=b;
    b=temp;
}
int main(){

    int n;
    cout<<"enter array size\n";
    cin>>n;
    vector<int> arr(n);
    cout<<"Enter array elements"<<endl;
    for(int i =0;i<n;i++){
        cin>>arr[i];
    }

    cout<<"YOur array is : ";
    for(int i =0;i<n;i++){
        cout<<arr[i]<<" ";
    }
    cout<<endl;
    int count=0;

    for(int i=0;i<n-1;i++){
        for(int j=0;j<n-1-i;j++){
            if(arr[j]>arr[j+1]){
                swap(arr[j],arr[j+1]);
                count++;
            }
        }
    }
    cout<<"INVERSIONS : "<<count<<endl;
    return 0;
}