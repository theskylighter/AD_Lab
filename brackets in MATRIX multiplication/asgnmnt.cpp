#include <iostream>
#include <fstream>
#include <vector>
#include <limits>
#include <sstream>

using namespace std;

// Function to print the optimal parenthesization
void printOptimalParens(int i, int j, const vector<vector<int>>& s) {
    if (i == j)
        cout << "M" << i;
    else {
        cout << "(";
        printOptimalParens(i, s[i][j], s);
        printOptimalParens(s[i][j] + 1, j, s);
        cout << ")";
    }
}

// Function to perform matrix chain multiplication using dynamic programming
void matrixChainOrder(const vector<int>& p, int n) {
    vector<vector<int>> m(n, vector<int>(n, 0));
    vector<vector<int>> s(n, vector<int>(n, 0));

    // L is chain length
    for (int L = 2; L < n; L++) {
        for (int i = 1; i < n - L + 1; i++) {
            int j = i + L - 1;
            m[i][j] = numeric_limits<int>::max();
            for (int k = i; k < j; k++) {
                int q = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
                if (q < m[i][j]) {
                    m[i][j] = q;
                    s[i][j] = k;
                }
            }
        }
    }

    // Print the cost table
    cout << "Cost Table (m[i][j]):\n";
    for (int i = 1; i < n; i++) {
        for (int j = 1; j < n; j++) {
            if (i <= j)
                cout << m[i][j] << "\t";
            else
                cout << "\t";
        }
        cout << endl;
    }

    // Print the k table
    cout << "\nOptimal Split Indices (s[i][j]):\n";
    for (int i = 1; i < n; i++) {
        for (int j = 1; j < n; j++) {
            if (i < j)
                cout << s[i][j] << "\t";
            else
                cout << "\t";
        }
        cout << endl;
    }

    // Print the optimal parenthesization
    cout << "\nOptimal Parenthesization: ";
    printOptimalParens(1, n - 1, s);
    cout << endl;
}

int main() {
    ifstream infile("mcm.dat");
    
    if (!infile) {
        cout << "Error: Could not open file 'mcm.dat'. Please check if the file exists.\n";
        return 1;
    }

    string line;
    if (!getline(infile, line) || line.empty()) {
        cout << "Error: File is empty or could not read content.\n";
        return 1;
    }

    infile.close();

    vector<int> p;
    stringstream ss(line);
    string token;
    while (getline(ss, token, ',')) {
        try {
            p.push_back(stoi(token));
        } catch (const invalid_argument&) {
            cout << "Error: File contains non-numeric data.\n";
            return 1;
        } catch (const out_of_range&) {
            cout << "Error: Number in file is out of range.\n";
            return 1;
        }
    }

    if (p.size() < 2) {
        cout << "Error: Not enough data for matrix chain multiplication.\n";
        return 1;
    }

    int n = p.size();
    matrixChainOrder(p, n);

    return 0;
}