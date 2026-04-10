// Fuente: Program to multiply two matrices - GeeksforGeeks
#include <vector>

using namespace std;

vector<vector<int>> multiplyMatricesNaive(const vector<vector<int>>& m1, const vector<vector<int>>& m2) {
    int n = m1.size();

    vector<vector<int>> res(n, vector<int>(n, 0));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                res[i][j] += m1[i][k] * m2[k][j];
            }
        }
    }
    return res;
}