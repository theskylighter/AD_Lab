#include <bits/stdc++.h>
using namespace std;

const double EPS = 1e-9; //take minimum integer value

bool lup_decomp(vector<vector<double>>& A, vector<int>& P) {
    int n = A.size();
    P.resize(n);
    for (int i = 0; i < n; i++) {
        P[i] = i;  //intialize P with values 0,1,2,3...n-1
    }

    for (int k = 0; k < n; k++) {
        double pivotValue = 0;
        int pivotRow = -1;

        // Find the pivot row
        for (int i = k; i < n; i++) {
            if (fabs(A[i][k]) > pivotValue) { //
                pivotValue = fabs(A[i][k]);
                pivotRow = i;
            }
        }

        // If the matrix is singular
        if (pivotValue < EPS) {
            return false;
        }

        // Swap rows in P and A
        swap(P[k], P[pivotRow]);
        swap(A[k], A[pivotRow]);

        for (int i = k + 1; i < n; i++) {
            A[i][k] /= A[k][k];
            for (int j = k + 1; j < n; j++) {
                A[i][j] -= A[i][k] * A[k][j];
            }
        }
    }
    return true;
}

vector<double> lup_solve(const vector<vector<double>>& A, const vector<int>& P, const vector<double>& b) {
    int n = A.size();
    vector<double> x(n), y(n);

    // Forward substitution to solve Ly = Pb
    for (int i = 0; i < n; i++) {
        y[i] = b[P[i]];
        for (int j = 0; j < i; j++) {
            y[i] -= A[i][j] * y[j];
        }
    }

    // Backward substitution to solve Ux = y
    for (int i = n - 1; i >= 0; i--) {
        x[i] = y[i];
        for (int j = i + 1; j < n; j++) {
            x[i] -= A[i][j] * x[j];
        }
        x[i] /= A[i][i];
    }

    return x;
}

bool inverse(const vector<vector<double>>& A, vector<vector<double>>& invA) {
    int n = A.size();
    vector<vector<double>> LU = A;
    vector<int> P;

    if (!lup_decomp(LU, P)) {
        return false;  // Matrix is singular, no inverse
    }

    invA.resize(n, vector<double>(n));

    // Solve for each column of the identity matrix to find the inverse
    for (int i = 0; i < n; i++) {
        vector<double> e(n, 0);
        e[i] = 1; // i-th column of the identity matrix
        vector<double> col = lup_solve(LU, P, e);
        for (int j = 0; j < n; j++) {
            invA[j][i] = col[j];
        }
    }
    return true;
}

void read_matrix(string file, vector<vector<double>>& matrix, int &n){
    ifstream infile(file);
    if (!infile) {
        cerr << "Error opening file!" << endl;
        return ;
    }
    infile >> n;
    if (n <= 0) {
        cerr << "Invalid number of symbols(can only be posititve)." << endl;
        return ;
    }
    matrix.resize(n,vector<double>(n));
    infile.ignore();
    for(int i=0;i<n;i++){
        string line;
        getline(infile,line);
        stringstream lin(line);
        string item;
        for(int j=0;j<n;j++){
            getline(lin,item,',');
            matrix[i][j]=stod(item);
        } 
    }
}

vector<vector<double>> matrix_mult(vector<vector<double>> A , vector<vector<double>> B){
    int n = A.size();
    vector<vector<double>> C(n,vector<double>(n));
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            for(int k=0;k<n;k++){
                C[i][j] += A[i][k]*B[k][j];
            }
        }
    }
    return C;
}

bool verify_inverse(const vector<vector<double>>& A, const vector<vector<double>>& A_inv) {
    int n = A.size();
    vector<vector<double>> identity = matrix_mult(A, A_inv);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j && fabs(identity[i][j] - 1) > EPS) {
                return false;
            } else if (i != j && fabs(identity[i][j]) > EPS) {
                return false;
            }
        }
    }
    return true;
}


int main() {
    string file="lup.dat";
    vector<vector<double>> matrix;
    int n;
    read_matrix(file,matrix,n);    
    //create a copy of this matrix
    vector<vector<double>> matrix_copy = matrix;
    vector<vector<double>> inv_matrix;

    if (!inverse(matrix, inv_matrix)) {
        cout << "The matrix has no inverse (singular matrix)." << endl;
        return 0;
    }

    cout << "Inverse of the matrix:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout <<inv_matrix[i][j] << "\t";
        }
        cout << endl;
    }

    if (verify_inverse(matrix, inv_matrix)) {
        cout << "The inverse is verified successfully!" << endl;
    } else {
        cout << "Error: The computed matrix is not the inverse!" << endl;
    }

    return 0;
}