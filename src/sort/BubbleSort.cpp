#include "../../include/SortAlgorithms.h"

void SortAlgorithms::bubbleSort(int arr[], int n){
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
        
        if (swapped == false){
            break;
        }
    }
}