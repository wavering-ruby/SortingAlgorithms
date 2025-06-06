#include <iostream>
#include <chrono>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;
using namespace std::chrono;

void merge(int arr[], int left, int mid, int right, unsigned long long& cont1, unsigned long long& cont2) {
    const int n1 = mid - left + 1;
    const int n2 = right - mid;
    int* L = new int[n1]; // Aloca no heap (memória ilimitada)
    int* R = new int[n2]; // Aloca no heap (memória ilimitada)
    // int L[n1], R[n2]; // Aloca no stack (memória limitada)

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        cont1++;  // ← conta comparação: L[i] <= R[j]
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            cont2++;  // ← conta troca: atribuição no arr[]
            i++;
        } else {
            arr[k] = R[j];
            cont2++;  // ← conta troca: atribuição no arr[]
            j++;
        }
        k++;
    }

    // Copia o restante da esquerda (se sobrou)
    while (i < n1) {
        arr[k] = L[i];
        cont2++;  // ← conta troca: atribuição no arr[]
        i++;
        k++;
    }

    // Copia o restante da direita (se sobrou)
    while (j < n2) {
        arr[k] = R[j];
        cont2++;  // ← conta troca: atribuição no arr[]
        j++;
        k++;
    }

    delete[] L; // Libera a memória ao final
    delete[] R; // Libera a memória ao final
}

void mergeSort(int arr[], int n, unsigned long long& cont1, unsigned long long& cont2) {
    for(int cs = 1; cs <= n - 1; cs = 2 * cs){
        for(int leftStart = 0; leftStart < n - 1; leftStart += 2 * cs){
            int mid = min(leftStart + cs - 1, n - 1);
            int rightEnd = min(leftStart + 2 * cs - 1, n - 1);
        
            merge(arr, leftStart, mid, rightEnd, cont1, cont2);
        }

    }
}

void bubbleSort(int arr[], int n, unsigned long long& cont1, unsigned long long& cont2){
    bool swapped;
    for(int i = 0; i < n - 1; i++) {
        swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            cont1++;
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1]; 
                arr[j + 1] = temp; cont2++; //conta troca
                swapped = true;
            }
        }
        
        if (swapped == false)
            break;
    }
}


// A utility function to get maximum
// value in arr[]
int getMax(int arr[], int n, unsigned long long* cont1){ // Radix sort
    int mx = arr[0];
    for (int i = 1; i < n; i++){
        (*cont1)++;
        if (arr[i] > mx)
            mx = arr[i];
    }
    return mx;
}

// A function to do counting sort of arr[]
// according to the digit
// represented by exp.
void countSortR(int arr[], int n, int exp, unsigned long long* cont2){ // Biblioteca do RadixSort
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
        (*cont2)++;
        count[(arr[i] / exp) % 10]--;
    }

    // Copy the output array to arr[],
    // so that arr[] now contains sorted
    // numbers according to current digit
    for (i = 0; i < n; i++){
        arr[i] = output[i];
        (*cont2)++;
    }
    delete[] output; // libera a memória alocada
}

// The main function to that sorts arr[]
// of size n using Radix Sort
void radixSort(int arr[], int n, unsigned long long* cont1, unsigned long long* cont2){ // radixsort
    // Find the maximum number to
    // know number of digits
    int m = getMax(arr, n, cont1);

    // Do counting sort for every digit.
    // Note that instead of passing digit
    // number, exp is passed. exp is 10^i
    // where i is current digit number
    for (int exp = 1; m / exp > 0; exp *= 10){
        countSortR(arr, n, exp, cont2);
    }
}


void insertionSort(int arr[], int n, unsigned long long& cont1, unsigned long long& cont2){
    for (int i = 1; i < n; ++i) {
        int key = arr[i];
        int j = i - 1;

        /* Move elements of arr[0..i-1], that are
           greater than key, to one position ahead
           of their current position */
        while (j >= 0 && arr[j] > key) { cont1++;//conta comparação
            arr[j + 1] = arr[j]; cont2++; //conta troca
            j = j - 1;
        }
        cont1++;
        arr[j + 1] = key; //conta troca
        cont2++;
    }
}


int partition(int arr[], int low, int high, unsigned long long& cont1, unsigned long long& cont2){
    // Selecting last element as the pivot
    int pivot = arr[high];

    // Index of elemment just before the last element
    // It is used for swapping
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++){
        // If current element is smaller than or
        // equal to pivot
        cont1++;  // ← conta comparação: arr[j] <= pivot
        if (arr[j] <= pivot){
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            cont2++;
        }
    }

    // Put pivot to its position
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    cont2++;
    // Return the point of partition
    return (i + 1);
}

void quickSort(int arr[], int low, int high, unsigned long long& cont1, unsigned long long& cont2){
    // Create an auxiliary stack
    int* stack = new int[high - low + 1];

	// initialize top of stack 
	int top = -1; 

	// push initial values of l and h to stack 
	stack[++top] = low; 
	stack[++top] = high; 

	// Keep popping from stack while is not empty 
	while (top >= 0) { 
		// Pop h and l 
		high = stack[top--]; 
		low = stack[top--]; 

		int p = partition(arr, low, high, cont1, cont2); 

		// If there are elements on left side of pivot, 
		// then push left side to stack 
		if (p - 1 > low) { 
			stack[++top] = low; 
			stack[++top] = p - 1; 
		} 

		// If there are elements on right side of pivot, 
		// then push right side to stack 
		if (p + 1 < high) { 
			stack[++top] = p + 1; 
			stack[++top] = high; 
		} 
	}

    delete[] stack; // Libera a memória ao final
}


void selectionSort(int arr[], int n, unsigned long long& cont1, unsigned long long& cont2) {

    for (int i = 0; i < n - 1; ++i) {

        // Assume the current position holds
        // the minimum element
        int min_idx = i;

        // Iterate through the unsorted portion
        // to find the actual minimum
        for (int j = i + 1; j < n; ++j) {
            cont1++; // Comparação: arr[j] < arr[min_idx]
            if (arr[j] < arr[min_idx]) {

                // Update min_idx if a smaller
                // element is found
                min_idx = j; 
            }
        }

        // Move minimum element to its
        // correct position
        swap(arr[i], arr[min_idx]);
        cont2++;
    }
}
void heapify(int arr[], int n, int i, unsigned long long& cont1, unsigned long long& cont2){

    // Initialize largest as root
    int largest = i;

    // left index = 2i + 1
    int l = 2 * i + 1;

    // right index = 2i + 2
    int r = 2  * i + 2;

    // If left child is larger than root
    if(l < n && arr[l] > arr[largest]){
        largest = l;
        cont1++;
    }
    // If right child is larger than largest so far
    if(r < n && arr[r] > arr[largest]){
        largest = r;
        cont1++;
    }
    // If largest is not root
    if(largest != i) {
        int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;
        cont2++;
        // Recursively heapify the affected sub-tree
        heapify(arr, n, largest,cont1,cont2);
    }
}

// Main function to do heap sort
void heapSort(int arr[], int n, unsigned long long& cont1, unsigned long long& cont2){

    // Build heap (rearrange vector)
    for (int i = n / 2 - 1; i >= 0; i--){
        heapify(arr, n, i,cont1,cont2);
    }

    // One by one extract an element from heap
    for (int i = n - 1; i > 0; i--){
        // Move current root to end
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
        cont2++;
        // Call max heapify on the reduced heap
        heapify(arr, i, 0,cont1,cont2);
    }
}

int* countSort(int* arr, int tamanho, unsigned long long& cont1, unsigned long long& cont2) {
    if (tamanho <= 0){
        return nullptr;
    }

    int max_val = arr[0];
    for (int i = 1; i < tamanho; i++) {
        cont1++; // Conta a comparação (arr[i] > max_val)
        if (arr[i] > max_val) {
            max_val = arr[i];
        }
    }

    int* count = new int[max_val + 1]();

    for (int i = 0; i < tamanho; i++) {
        count[arr[i]]++;
    }

    for (int i = 1; i <= max_val; i++) {
        count[i] += count[i - 1];
    }

    int* output = new int[tamanho];

    for (int i = tamanho - 1; i >= 0; i--) {
        output[count[arr[i]] - 1] = arr[i];
        cont2++; // Conta cada atribuição como "troca"
        count[arr[i]]--;
    }

    delete[] count;

    return output;
}


void readFile(const string& filename, int arr[], unsigned int N){
    string path = "file/" + filename;
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
    const unsigned int N = 100000;
    int *arr = new int[N]; // Aloca no heap (memória ilimitada)
    unsigned long long cont1=0, cont2=0; //contadores de verificações ou troca de elementos

    //*************************************************
    //********* Mude aqui o nome do arquivo ***********
    //*************************************************
    string fileName = "RandomNumbers3.txt";

    readFile(fileName, arr, N);

    // Algoritmos implementados:
    /*
        - Bubble Sort V
        - Insertion Sort V
        - Radix Sort V
        - Quick Sort V
        - Merge Sort V
        - Selection Sort V
        - Heap Sort V
    */

    auto start = high_resolution_clock::now();

    //quickSort(arr, 0, N - 1, cont1, cont2);
    //mergeSort(arr, N, cont1, cont2);
    //radixSort(arr, N, &cont1, &cont2); // Funciona bem!
    //insertionSort(arr, N, cont1, cont2); // Funciona bem!
    //bubbleSort(arr, N, cont1, cont2); // Funciona bem!
    //selectionSort(arr,N,cont1,cont2);
    //heapSort(arr,N, cont1, cont2);
    arr = countSort(arr, N,cont1,cont2);
    auto end = high_resolution_clock::now();

    unsigned long long value = duration_cast<nanoseconds>(end - start).count();
    cout << "Nanossegundos: " << value << endl;
    cout << "Segundos: " << value / 1e+9 << endl;
    cout << "Comparações:" << cont1 << endl;
    cout << "Trocas:" << cont2 << endl;
    for (int i = 0; i < 100; i++){
        cout << arr[i] << ", ";
    }

    delete[] arr; // Libera a memória ao final

    return 0;
}