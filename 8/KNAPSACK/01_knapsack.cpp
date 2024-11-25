#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
 
int knapsack(int W, const vector<int>& weights, const vector<int>& values, int n) {
    vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));
    
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= W; j++) {
            if (weights[i - 1] <= j) {
                dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - weights[i - 1]] + values[i - 1]);
            } else {
                dp[i][j] = dp[i - 1][j];
            }
        }
    }
    return dp[n][W];
}

int main() {
    int M;
    int n;  
    cout << "Enter the number of items: ";
    cin >> n;
    vector<int> weights(n), values(n);
    cout << "Enter the weights and values of the items: ";
    for (int i = 0; i < n; ++i) {
        cin >> weights[i] >> values[i];
    }
    cout << "Enter the capacity of the knapsack: ";
    cin >> M;
    int maxValue = knapsack(M, weights, values, n);
    cout << "Maximum value in the knapsack: " << maxValue << endl;

    return 0;
}
