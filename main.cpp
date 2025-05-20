#include <iostream>
#include <chrono>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;
using namespace std::chrono;

void merge(int arr[], int left, int mid, int right) {
    const int n1 = mid - left + 1;
    const int n2 = right - mid;
    int *L = new int[n1]; // Aloca no heap (memória ilimitada)
    int *R = new int[n2]; // Aloca no heap (memória ilimitada)
    // int L[n1], R[n2]; // Aloca no stack (memória limitada)

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }

        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }

    delete[] L; // Libera a memória ao final
    delete[] R; // Libera a memória ao final
}

void mergeSort(int arr[], int left, int right) {
    if (left >= right){
        return;
    }

    int mid = left + (right - left) / 2;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    merge(arr, left, mid, right);
}

void bubbleSort(int arr[], int n){
    bool swapped;
    for(int i = 0; i < n - 1; i++) {
        swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = true;
            }
        }
        
        if (swapped == false)
            break;
    }
}

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
void countSortR(int arr[], int n, int exp){ // Radix sort
    // Output array
    int* output = new int[n]; // aloca dinamicamente
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
    for (i = n - 1; i >= 0; i--){
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }

    // Copy the output array to arr[],
    // so that arr[] now contains sorted
    // numbers according to current digit
    for (i = 0; i < n; i++)
        arr[i] = output[i];

    delete[] output; // libera a memória alocada
}

// The main function to that sorts arr[]
// of size n using Radix Sort
void radixSort(int arr[], int n){ // radixsort
    // Find the maximum number to
    // know number of digits
    int m = getMax(arr, n);

    // Do counting sort for every digit.
    // Note that instead of passing digit
    // number, exp is passed. exp is 10^i
    // where i is current digit number
    for (int exp = 1; m / exp > 0; exp *= 10){
        countSortR(arr, n, exp);
    }
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

int partition(int arr[], int low, int high){
    // Selecting last element as the pivot
    int pivot = arr[high];

    // Index of elemment just before the last element
    // It is used for swapping
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++){
        // If current element is smaller than or
        // equal to pivot
        if (arr[j] <= pivot) {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    // Put pivot to its position
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;

    // Return the point of partition
    return (i + 1);
}

void quickSort(int arr[], int low, int high){
    // Base case: This part will be executed till the starting
    // index low is lesser than the ending index high
    if (low < high) {

        // pi is Partitioning Index, arr[p] is now at
        // right place
        int pi = partition(arr, low, high);
        // cout << "PI: " << pi << endl;

        // Separately sort elements before and after the
        // Partition Index pi
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void readFile(const string& filename, int arr[], unsigned int N){
    //*************************************************
    //******* Mude aqui o caminho do arquivo **********
    //*************************************************
    string path = "../test/" + filename;
    ifstream file(path);

    if (!file.is_open()){
        cerr << "Error opening file: " << path << endl;
        return;
    }

    string line;

    if (getline(file, line)){
        stringstream ss(line);
        string value;
        unsigned int i = 0;

        while (getline(ss, value, ',') && i < N){
            arr[i] = stoi(value);
            i++;
        }
    }

    file.close();
}

int main(){
    //*************************************************
    //********* Mude aqui o qtd de elementos **********
    //*************************************************
    const unsigned int N = 80000;
    int *arr = new int[N]; // Aloca no heap (memória ilimitada)

    //*************************************************
    //********* Mude aqui o nome do arquivo ***********
    //*************************************************
    string fileName = "RandomNumbers2.txt";

    readFile(fileName, arr, N);

    // Algoritmos implementados:
    /*
        - Bubble Sort 
        - Insertion Sort
        - Radin Sort
        - Quick Sort
        - Merge Sort
    */

    auto start = high_resolution_clock::now();

    // quickSort(arr, 0, N - 1); // Não está funcionando
    // mergeSort(arr, 0, N - 1); // Não está funcionando
    // radixSort(arr, N); // Funciona bem!
    insertionSort(arr, N); // Funciona bem!
    // bubbleSort(arr, N); // Funciona bem!

    auto end = high_resolution_clock::now();

    unsigned long long value = duration_cast<nanoseconds>(end - start).count();
    cout << "Nanossegundos: " << value << endl;
    cout << "Segundos: " << value / 1e+9 << endl;

    for (int i = 0; i < 100; i++){
        cout << arr[i] << ", ";
    }

    delete[] arr; // Libera a memória ao final

    return 0;
}