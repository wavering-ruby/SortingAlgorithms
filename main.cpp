#include <bits/stdc++.h>
#include <chrono>
using namespace std;
using namespace std::chrono;

void insertionSort(int arr[], int n){
    for (int i = 1; i < n; ++i) {
        int key = arr[i];
        int j = i - 1;

        /* Move elements of arr[0..i-1], that are
           greater than key, to one position ahead
           of their current position */
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

int partition(int arr[], int low, int high) {
    // Selecting last element as the pivot
    int pivot = arr[high];

    // Index of elemment just before the last element
    // It is used for swapping
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {

        // If current element is smaller than or
        // equal to pivot
        if (arr[j] <= pivot) {
            i++;
            // swap(arr[i], arr[j]);
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    // Put pivot to its position
    // swap(arr[i + 1], arr[high]);
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;

    // Return the point of partition
    return (i + 1);
}

void quickSort(int arr[], int low, int high) {

    // Base case: This part will be executed till the starting
    // index low is lesser than the ending index high
    if (low < high) {

        // pi is Partitioning Index, arr[p] is now at
        // right place
        int pi = partition(arr, low, high);

        // Separately sort elements before and after the
        // Partition Index pi
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int main() {
    // Teste
    int array[] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    int n = 10;
  	
  	auto start = high_resolution_clock::now();
  	
  	// Função do QuickSort
    quickSort(array, 0, n - 1);
    
    auto end = high_resolution_clock::now();
    
    cout << duration_cast<nanoseconds>(end - start).count() << " nanoseconds" << endl;
    
    int array1[] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    
    start = high_resolution_clock::now();
  	
  	// Função do InsertionSort
    insertionSort(array, n);
    
    end = high_resolution_clock::now();
    
    cout << duration_cast<nanoseconds>(end - start).count() << " nanoseconds" << endl;

    for (auto i : array) {
        cout << i << " ";
    }
    
    return 0;
}