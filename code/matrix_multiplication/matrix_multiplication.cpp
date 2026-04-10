#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <string>
#include <cmath>
#include <sstream>
#include <windows.h>
#include <psapi.h>
#include "algorithms/strassen.cpp"
#include "algorithms/naive.cpp"

using namespace std;
using namespace std::chrono;
typedef vector<vector<int>> Matrix;

size_t get_peak_memory_kb() {
    PROCESS_MEMORY_COUNTERS info;
    if (GetProcessMemoryInfo(GetCurrentProcess(), &info, sizeof(info))) {
        return info.PeakWorkingSetSize / 1024;
    }
    return 0;
}

void save_measurement(string algo_name, int n, double time, size_t memory) {
    ofstream outfile;
    string ruta = "data/measurements/" + algo_name + "_results.txt";
    outfile.open(ruta, ios_base::app);
    if (outfile.is_open()) {
        outfile << n << " " << time << " " << memory << endl;
        outfile.close();
    }
}

void save_matrix_output(string input_filename, const Matrix& res, string algo) {
    size_t last_slash = input_filename.find_last_of("/\\");
    string base_name = (last_slash == string::npos) ? input_filename : input_filename.substr(last_slash + 1);
    size_t last_dot = base_name.find_last_of(".");
    if (last_dot != string::npos) base_name = base_name.substr(0, last_dot);
    string out_path = "data/matrix_output/" + base_name + "_" + algo + "_out.txt";
    ofstream outfile(out_path);
    if (outfile.is_open()) {
        for (const auto& row : res) {
            for (size_t i = 0; i < row.size(); ++i) {
                outfile << row[i] << (i == row.size() - 1 ? "" : " ");
            }
            outfile << endl;
        }
        outfile.close();
    }
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        cout << "Uso: ./matrix_exec matriz1.txt matriz2.txt" << endl;
        return 1;
    }
    string input_file1 = argv[1];
    string input_file2 = argv[2];
    ifstream file1(input_file1);
    if (!file1.is_open()) {
        cout << "No se pudo abrir: " << input_file1 << endl;
        return 1;
    }
    string line;
    getline(file1, line);
    stringstream ss(line);
    int temp;
    vector<int> first_row;
    while (ss >> temp) first_row.push_back(temp);

    int n = first_row.size();
    Matrix A(n, vector<int>(n));
    for(int j = 0; j < n; j++) A[0][j] = first_row[j];

    for(int i = 1; i < n; i++)
        for(int j = 0; j < n; j++)
            file1 >> A[i][j];
    file1.close();

    ifstream file2(input_file2);
    if (!file2.is_open()) return 1;
    Matrix B(n, vector<int>(n));
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            file2 >> B[i][j];
    file2.close();

    auto start = high_resolution_clock::now();
    Matrix res_naive = multiplyMatricesNaive(A, B);
    auto stop = high_resolution_clock::now();
    size_t mem_naive = get_peak_memory_kb();
    save_measurement("naive", n, duration_cast<microseconds>(stop - start).count() / 1000000.0, mem_naive);
    save_matrix_output(input_file1, res_naive, "naive");

    start = high_resolution_clock::now();
    Matrix res_strassen = multiplyMatricesStrassen(A, B);
    stop = high_resolution_clock::now();
    size_t mem_strassen = get_peak_memory_kb();
    save_measurement("strassen", n, duration_cast<microseconds>(stop - start).count() / 1000000.0, mem_strassen);
    save_matrix_output(input_file1, res_strassen, "strassen");

    return 0;
}