#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Merge function (same as recursive)
void merge(int* arr, int low, int mid, int high, bool isAsc) {
    int n1 = mid - low + 1;
    int n2 = high - mid;

    int* L = malloc(n1 * sizeof(int));
    int* R = malloc(n2 * sizeof(int));

    for (int i = 0; i < n1; i++)
        L[i] = arr[low + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = low;

    while (i < n1 && j < n2) {
        if (isAsc ? (L[i] <= R[j]) : (L[i] >= R[j]))
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }

    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];

    free(L);
    free(R);
}

// Iterative Merge Sort
void merge_sort_iterative(int* arr, int n, bool isAsc) {
    int curr_size;  // Size of subarrays to merge
    int left_start; // Starting index of left subarray

    for (curr_size = 1; curr_size < n; curr_size *= 2) {
        for (left_start = 0; left_start < n - 1; left_start += 2 * curr_size) {
            int mid = left_start + curr_size - 1;
            int right_end = (left_start + 2 * curr_size - 1 < n - 1)
                                ? (left_start + 2 * curr_size - 1)
                                : (n - 1);

            if (mid < right_end)
                merge(arr, left_start, mid, right_end, isAsc);
        }
    }
}

// Utility to print array
void printArray(int* arr, int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

// Test
int main() {
    int arr[] = {5, 2, 9, 1, 6, 3, 1,2,6,16,7};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Original array:\n");
    printArray(arr, n);

    // Sort Ascending
    merge_sort_iterative(arr, n, true);
    printf("\nSorted array (Ascending):\n");
    printArray(arr, n);

    // Sort Descending
    merge_sort_iterative(arr, n, false);
    printf("\nSorted array (Descending):\n");
    printArray(arr, n);

    return EXIT_SUCCESS;
}
