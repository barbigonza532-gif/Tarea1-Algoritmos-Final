#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <string>
#include <windows.h>
#include <psapi.h>
#include "algorithms/mergesort.cpp"
#include "algorithms/quicksort.cpp"
#include "algorithms/sort.cpp"

using namespace std;
using namespace std::chrono;

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
    } else {
        cout << "ERROR: No se pudo crear el archivo de resultados en: " << ruta << endl;
    }
}

void save_output(string input_filename, const vector<int>& sorted_data) {
    size_t last_slash = input_filename.find_last_of("/\\");
    string base_name = (last_slash == string::npos) ? input_filename : input_filename.substr(last_slash + 1);
    size_t last_dot = base_name.find_last_of(".");
    if (last_dot != string::npos) base_name = base_name.substr(0, last_dot);
    string out_path = "data/array_output/" + base_name + "_out.txt";
    ofstream outfile(out_path);
    if (outfile.is_open()) {
        for (size_t i = 0; i < sorted_data.size(); ++i) {
            outfile << sorted_data[i] << (i == sorted_data.size() - 1 ? "" : " ");
        }
        outfile.close();
    } else {
        cout << "ERROR: No se pudo crear el archivo de salida en: " << out_path << endl;
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "Uso: ./sorting_exec nombre_archivo.txt" << endl;
        return 1;
    }
    string input_file = argv[1];
    ifstream file(input_file);
    if (!file.is_open()) {
        cout << "No se pudo abrir: " << input_file << endl;
        return 1;
    }

    int val;
    vector<int> data;
    while (file >> val) data.push_back(val);
    int n = data.size();

    // medicion quick
    vector<int> q_data = data;
    auto start = high_resolution_clock::now();
    quickSortArray(q_data);
    auto stop = high_resolution_clock::now();
    size_t mem_quick = get_peak_memory_kb();
    save_measurement("quicksort", n, duration_cast<microseconds>(stop - start).count() / 1000000.0, mem_quick);

    // medicion merge
    vector<int> m_data = data;
    start = high_resolution_clock::now();
    mergeSortArray(m_data);
    stop = high_resolution_clock::now();
    size_t mem_merge = get_peak_memory_kb();
    save_measurement("mergesort", n, duration_cast<microseconds>(stop - start).count() / 1000000.0, mem_merge);

    // medicion sort
    vector<int> s_data = data;
    start = high_resolution_clock::now();
    sortArray(s_data);
    stop = high_resolution_clock::now();
    size_t mem_sort = get_peak_memory_kb();
    save_measurement("sort", n, duration_cast<microseconds>(stop - start).count() / 1000000.0, mem_sort);

    save_output(input_file, s_data);

    return 0;
}