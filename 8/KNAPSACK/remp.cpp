#include <iostream>
#include <vector>
using namespace std;

// Function to solve 0/1 Knapsack problem
int knapsack(int maxWeight, vector<int>& weights, vector<int>& values, int n) {
    // Create a 2D DP table
    vector<vector<int>> dp(n + 1, vector<int>(maxWeight + 1, 0));

    // Fill the DP table
    for (int i = 1; i <= n; i++) {
        for (int w = 1; w <= maxWeight; w++) {
            // Check if the current item can be included based on its weight
            if (weights[i - 1] <= w) {
                // Max of either including the item or not including it
                dp[i][w] = max(dp[i - 1][w], dp[i - 1][w - weights[i - 1]] + values[i - 1]);
            } else {
                // If the item's weight is more than the current capacity, we don't include it
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    // The maximum value will be in dp[n][maxWeight]
    return dp[n][maxWeight];
}

int main() {
    // Define the number of items and the weight limit of the knapsack
    int n = 4;  // Number of items
    int maxWeight = 10;  // Maximum weight the knapsack can hold

    // Define the weights and values of the items
    vector<int> weights = {4, 3, 5, 2};  // Weights of the items
    vector<int> values = {50, 40, 70, 30};  // Values of the items

    // Call the knapsack function and print the result
    int maxValue = knapsack(maxWeight, weights, values, n);
    cout << "Maximum value that can be carried in the knapsack: " << maxValue << endl;

    return 0;
}
