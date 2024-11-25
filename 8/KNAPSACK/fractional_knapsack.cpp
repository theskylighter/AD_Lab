#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct knapsack{
    float val;
    float wt;
    float ratio;
};
bool compare(knapsack a, knapsack b){
    return a.ratio > b.ratio;
}

float fractionalKnapsack(struct knapsack k[], int M, int n){
    sort(k,k+n, compare);
    float curr_wt=0;
    float profit=0;
    for(int i=0; i<n;i++){
        if(curr_wt+k[i].wt <=M){
            profit+=k[i].val;
            curr_wt+=k[i].wt;
        }
        else{
            float rem_wt=M-curr_wt;
            profit+=rem_wt*k[i].ratio;
            break;
        }

    }
    return profit;
}

int main(){
    int n, M;
    cout << "Enter the number of items: ";
    cin >> n;
    knapsack k[n];
    cout << "Enter the values and weights of the items: \n";
    for(int i=0; i<n; i++){
        cin >> k[i].val >> k[i].wt;
        k[i].ratio = k[i].val / k[i].wt;
    }
    cout << "Enter the capacity of the knapsack: ";
    cin >> M;
    float max_value = fractionalKnapsack(k, M, n);
    cout << "Maximum profit earned using knapsack of" << M << " is " << max_value << endl;
    return 0;
}