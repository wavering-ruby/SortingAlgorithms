#ifndef SORTALGORITHMS_H  // Guarda de inclusão para evitar duplicação
#define SORTALGORITHMS_H

class SortAlgorithms {
public:
    //---- Algoritmos Públicos ----//
    static void heapSort(int arr[], int n);
    static void selectionSort(int arr[], int n);
    static int* countSort(int arr[], int tamanho);
    static void mergeSort(int arr[], int n);
    static void bubbleSort(int arr[], int n);
    static void radixSort(int arr[], int n);
    static void insertionSort(int arr[], int n);
    static void quickSort(int arr[], int low, int high);

private:
    //---- Métodos Auxiliares ----//
    // Heap Sort
    static void heapify(int arr[], int n, int i);
    
    // Merge Sort
    static void merge(int arr[], int left, int mid, int right);
    
    // Radix Sort
    static int getMax(int arr[], int n);
    static void countSortR(int arr[], int n, int exp);
    
    // Quick Sort
    static int partition(int arr[], int low, int high);
};

#endif // SORTALGORITHMS_H