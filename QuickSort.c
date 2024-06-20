int partition(int array[], int low, int high) {
    int pivot = array[high]; // Pivot
    int i = (low - 1); // Index of smaller element

    for (int j = low; j <= high - 1; j++) {
        // If current element is smaller than or equal to pivot
        if (array[j] <= pivot) {
            i++; // Increment index of smaller element
            int temp = array[i];
            array[i] = array[j];
            array[j] = temp;
        }
    }
    int temp = array[i + 1];
    array[i + 1] = array[high];
    array[high] = temp;
    return (i + 1);
}

// Quick sort algorithm
void quickSort(int array[], int low, int high) {
    if (low < high) {
        // pi is partitioning index, array[pi] is now at right place
        int pi = partition(array, low, high);

        // Separately sort elements before partition and after partition
        quickSort(array, low, pi - 1);
        quickSort(array, pi + 1, high);
    }
}
