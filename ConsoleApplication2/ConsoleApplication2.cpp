#include <iostream>
#include <omp.h>
#include <vector>
#include <chrono>
#include <numeric>
#include <random>

using namespace std;
using namespace std::chrono;

int partition(vector<int32_t>& arr, int start, int end) {
    int pivot = arr[end];
    int i = start - 1;

    for (int j = start; j <= end - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[end]);
    return i + 1;
}

void quickSort(vector<int32_t>& arr, int start, int end) {

    if (start < end) {
        int32_t pivot = partition(arr, start, end);

        quickSort (arr, start, pivot - 1);
        quickSort (arr, pivot + 1, end);

        } 
}

int main()
{
    //random num gen
    mt19937 gen(time(NULL));
    uniform_int_distribution<int32_t> dis(0, 2'147'483'647);
    
    //vector 10^7
    vector<int32_t> arr(10'000'001);
    for (size_t i = 0; i < arr.size(); ++i) {
        arr[i]=dis(gen);
    }
    
    int n = arr.size();

    auto start = high_resolution_clock::now();
    #pragma omp parallel
    {
        #pragma omp single
        {
            quickSort(arr, 0, n - 1);
        }
    }
    auto stop = high_resolution_clock::now();

    duration<double> time_span = duration_cast<duration<double>>(stop - start);

    /*for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }*/

    cout << "\nFirst: " << arr[0] << " Last: " << arr.back() << endl;

    cout << "\nTime:" << time_span.count() << "s" << endl;
    
}
