void radixSort(int array[], int size) {
    // Find the maximum number to know number of digits
    int max = array[0];
    for (int i = 1; i < size; i++) {
        if (array[i] > max)
            max = array[i];
    }

    // Do counting sort for every digit
    for (int exp = 1; max / exp > 0; exp *= 10)
        countingSort(array, size, exp);
}
