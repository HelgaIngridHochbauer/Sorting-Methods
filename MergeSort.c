void merge(int array[], int low, int mid, int high) {
    int n1 = mid - low + 1;
    int n2 = high - mid;

    // Create temporary arrays
    int* L = (int*)malloc(n1 * sizeof(int));
    int* R = (int*)malloc(n2 * sizeof(int));

    // Copy data to temporary arrays L[] and R[]
    for (int i = 0; i < n1; i++)
        L[i] = array[low + i];
    for (int j = 0; j < n2; j++)
        R[j] = array[mid + 1 + j];

    // Merge the temporary arrays back into array[low..high]
    int i = 0; // Initial index of first subarray
    int j = 0; // Initial index of second subarray
    int k = low; // Initial index of merged subarray
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            array[k] = L[i];
            i++;
        }
        else {
            array[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of L[], if any
    while (i < n1) {
        array[k] = L[i];
        i++;
        k++;
    }

    // Copy the remaining elements of R[], if any
    while (j < n2) {
        array[k] = R[j];
        j++;
        k++;
    }

    // Free temporary arrays
    free(L);
    free(R);
}

// Merge sort algorithm
void mergeSort(int array[], int low, int high) {
    if (low < high) {
        // Same as (low+high)/2, but avoids overflow
        int mid = low + (high - low) / 2;

        // Sort first and second halves
        mergeSort(array, low, mid);
        mergeSort(array, mid + 1, high);

        // Merge the sorted halves
        merge(array, low, mid, high);
    }
}
