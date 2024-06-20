void heapify(int array[], int size, int i) {
    int largest = i; // Initialize largest as root
    int left = 2 * i + 1; // Left = 2*i + 1
    int right = 2 * i + 2; // Right = 2*i + 2

    // If left child is larger than root
    if (left < size && array[left] > array[largest])
        largest = left;

    // If right child is larger than largest so far
    if (right < size && array[right] > array[largest])
        largest = right;

    // If largest is not root
    if (largest != i) {
        int temp = array[i];
        array[i] = array[largest];
        array[largest] = temp;

        // Recursively heapify the affected sub-tree
        heapify(array, size, largest);
    }
}

// Heap sort algorithm
void heapSort(int array[], int size) {
    // Build heap (rearrange array)
    for (int i = size / 2 - 1; i >= 0; i--)
        heapify(array, size, i);

    // One by one extract an element from heap
    for (int i = size - 1; i > 0; i--) {
        // Move current root to end
        int temp = array[0];
        array[0] = array[i];
        array[i] = temp;

        // call max heapify on the reduced heap
        heapify(array, i, 0);
    }
}
