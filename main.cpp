#include <bits/stdc++.h>
#include <chrono>
using namespace std;
using namespace std::chrono;

// A utility function to get maximum
// value in arr[]
int getMax(int arr[], int n){ // Radix sort
    int mx = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > mx)
            mx = arr[i];
    return mx;
}

// A function to do counting sort of arr[]
// according to the digit
// represented by exp.
void countSort(int arr[], int n, int exp){ // Radix sort
    // Output array
    int output[n];
    int i, count[10] = { 0 };

    // Store count of occurrences
    // in count[]
    for (i = 0; i < n; i++)
        count[(arr[i] / exp) % 10]++;

    // Change count[i] so that count[i]
    // now contains actual position
    // of this digit in output[]
    for (i = 1; i < 10; i++)
        count[i] += count[i - 1];

    // Build the output array
    for (i = n - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }

    // Copy the output array to arr[],
    // so that arr[] now contains sorted
    // numbers according to current digit
    for (i = 0; i < n; i++)
        arr[i] = output[i];
}

// The main function to that sorts arr[]
// of size n using Radix Sort
void radixsort(int arr[], int n){ // radixsort
    // Find the maximum number to
    // know number of digits
    int m = getMax(arr, n);

    // Do counting sort for every digit.
    // Note that instead of passing digit
    // number, exp is passed. exp is 10^i
    // where i is current digit number
    for (int exp = 1; m / exp > 0; exp *= 10)
        countSort(arr, n, exp);
}

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
    insertionSort(array1, n);
    
    end = high_resolution_clock::now();
    
    cout << duration_cast<nanoseconds>(end - start).count() << " nanoseconds" << endl;
    
    int array2[] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    
    start = high_resolution_clock::now();
  	
  	// Função do InsertionSort
    radixsort(array2, n);
    
    end = high_resolution_clock::now();
    
    cout << duration_cast<nanoseconds>(end - start).count() << " nanoseconds" << endl;

    for (auto i : array) {
        cout << i << " ";
    }
    
    return 0;
}