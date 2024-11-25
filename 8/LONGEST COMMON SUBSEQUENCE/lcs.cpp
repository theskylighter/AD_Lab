#include<iostream>
#include<vector>
#include<string>

using namespace std;

int LCS(vector<vector<int>> &dp,string &s1, string &s2){
    int n=s1.length()+1;
    int m=s2.length()+1;
    for(int i=1;i<n;i++){
        for(int j=1;j<m;j++){
            if(s1[i-1]==s2[j-1]){
                dp[i][j]=dp[i-1][j-1]+1;
            }
            else{
                dp[i][j]=max(dp[i-1][j],dp[i][j-1]);
            }
        }
    }
    return dp[n-1][m-1];
}

string print_LCS( vector<vector<int>> &dp, string &s1, string &s2){
    string lcs="";
    int n=s1.length();
    int m=s2.length();
    int i=n, j=m;
    while(i>0 && j>0){
        if(s1[i-1]==s2[j-1]){
            lcs=s1[i-1]+lcs;
            i--;
            j--;
        }
        else if(dp[i-1][j]>dp[i][j-1]){
            i--;
        }
        else j--;
        
    }
    return lcs;
}

int main() {
    string X;
    cin>>X;
    string Y;
    cin>>Y;
    int m = X.length();
    int n = Y.length();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
    int lcsLength = LCS(dp,X, Y);
    cout << "Length of LCS: " << lcsLength << endl;
    string lcs = print_LCS(dp,X, Y);
    cout << "LCS: " << lcs << endl;

    return 0;
}+