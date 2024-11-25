#include<bits/stdc++.h>
using namespace std;

void read_file(vector<int> &p, string &file_name){
    ifstream infile(file_name);
    if (!infile) {
        cout << "Error: Could not open file 'mcm.dat'. Please check if the file exists.\n";
        return ;
    }

    string line;
    if (!getline(infile, line) || line.empty()) {
        cout << "Error: File is empty or could not read content.\n";
        return ;
    }
    infile.close();

    stringstream ss(line);
    string token;
    while (getline(ss, token, ',')) {
        if(stoi(token)==-999) break;
        try {
            p.push_back(stoi(token));
        } catch (const invalid_argument&) {
            cout << "Error: File contains non-numeric data.\n";
            return ;
        } catch (const out_of_range&) {
            cout << "Error: Number in file is out of range.\n";
            return ;
        }
        if(stoi(token)==-999) break;
    }
    
    return;
}

struct SubarrResult {
    int leftIndex;
    int rightIndex;
    int sum;
    char prefix; // L, R, or M
};

void print_f(SubarrResult &result, vector<int> &arr){
    cout<< result.prefix << " [ "<<result.leftIndex <<" , "<<result.rightIndex<< " ] : ";
    for(int i= result.leftIndex ; i<=result.rightIndex ; i++){
        cout<< arr[i] <<" ";
    }
    cout << "\t\t-> Sum : "<< result.sum <<endl;
}

SubarrResult max_cross_subarray(vector<int> &p, int low, int mid , int high){
    int left_sum=INT_MIN;
    int sum=0;
    int max_left = mid;
    for(int i=mid ; i>=low ; i--){
        sum += p[i];
        if(sum > left_sum){
            left_sum = sum;
            max_left = i;
        }
    }

    int right_sum=INT_MIN;
    sum=0;
    int max_right = mid+1;
    for(int j=mid+1 ; j<=high ; j++){
        sum += p[j];
        if(sum > right_sum){
            right_sum = sum;
            max_right = j;
        }
    }
    SubarrResult result= {max_left, max_right, left_sum+right_sum , 'M'};
    cout<<"CROSS :  ";
    print_f(result,p);
    return result;
}

SubarrResult max_subarray(vector<int> &arr, int low, int high){
    if(low==high){
        SubarrResult res= {low,high,arr[low],'L'};

        return res;
    }

    int mid= (low+high)/2;

    SubarrResult left = max_subarray(arr , low , mid);
    SubarrResult right = max_subarray(arr , mid+1 , high);
    SubarrResult cross = max_cross_subarray(arr , low , mid , high);
    
    cout<<"LEFT :  ";
    print_f(left , arr);
    cout<<"RIGHT :  ";
    print_f(right, arr);
    cout<<"\n";

    SubarrResult result;

    if(left.sum >= right.sum && left.sum >= cross.sum){
        result= left;
        result.prefix = 'L';
    }
    else if(right.sum >= left.sum && right.sum >= cross.sum){
        result = right;
        result.prefix = 'R';
    }
    else{
        result = cross;
        result.prefix='M';
    }

    return result;
}

int main(){
    vector<int> arr;
    string file_name="mss.dat";
    read_file(arr,file_name);
    
    if(arr.empty()){
        cout<<"Error: empty array"<<endl;
        return 0;
    }
    
    if(arr.size()>32){
        cout<<"Error : The maximum size should be 32."<<endl;
        return 0;
    }
    SubarrResult result= max_subarray(arr,0,arr.size()-1);

    print_f(result,arr);
    return 0;
}