// Fuente: geeksforgeeks - Strassen's Matrix Multiplication Algorithm | Implementation
#include <vector>

using namespace std;

typedef vector<vector<int>> Matrix;

Matrix add(Matrix A, Matrix B) {
    int n = A.size();
    Matrix res(n, vector<int>(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            res[i][j] = A[i][j] + B[i][j];
    return res;
}

Matrix subtract(Matrix A, Matrix B) {
    int n = A.size();
    Matrix res(n, vector<int>(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            res[i][j] = A[i][j] - B[i][j];
    return res;
}

Matrix strassen(Matrix A, Matrix B) {
    int n = A.size();
    if (n == 1) {
        return {{A[0][0] * B[0][0]}};
    }
    int newSize = n / 2;
    Matrix a11(newSize, vector<int>(newSize)), a12(newSize, vector<int>(newSize)),
        a21(newSize, vector<int>(newSize)), a22(newSize, vector<int>(newSize)),
        b11(newSize, vector<int>(newSize)), b12(newSize, vector<int>(newSize)),
        b21(newSize, vector<int>(newSize)), b22(newSize, vector<int>(newSize));


    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            a11[i][j] = A[i][j];
            a12[i][j] = A[i][j + newSize];
            a21[i][j] = A[i + newSize][j];
            a22[i][j] = A[i + newSize][j + newSize];

            b11[i][j] = B[i][j];
            b12[i][j] = B[i][j + newSize];
            b21[i][j] = B[i + newSize][j];
            b22[i][j] = B[i + newSize][j + newSize];
        }
    }

    Matrix p1 = strassen(a11, subtract(b12, b22));
    Matrix p2 = strassen(add(a11, a12), b22);
    Matrix p3 = strassen(add(a21, a22), b11);
    Matrix p4 = strassen(a22, subtract(b21, b11));
    Matrix p5 = strassen(add(a11, a22), add(b11, b22));
    Matrix p6 = strassen(subtract(a12, a22), add(b21, b22));
    Matrix p7 = strassen(subtract(a11, a21), add(b11, b12));

    Matrix C(n, vector<int>(n));
    Matrix c11 = add(subtract(add(p5, p4), p2), p6);
    Matrix c12 = add(p1, p2);
    Matrix c21 = add(p3, p4);
    Matrix c22 = subtract(subtract(add(p5, p1), p3), p7);

    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            C[i][j] = c11[i][j];
            C[i][j + newSize] = c12[i][j];
            C[i + newSize][j] = c21[i][j];
            C[i + newSize][j + newSize] = c22[i][j];
        }
    }

    return C;
}

vector<vector<int>> multiplyMatricesStrassen(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    return strassen(A, B);
}