#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function prototypes
void generateRandomArray(int array[], int size);
void insertionSort(int array[], int size);
void selectionSort(int array[], int size);
void bubbleSort(int array[], int size);
void heapSort(int array[], int size);
void mergeSort(int array[], int low, int high);
void merge(int array[], int low, int mid, int high);
void quickSort(int array[], int low, int high);
int partition(int array[], int low, int high);
void radixSort(int array[], int size);
void printLatexTable(int sizes[], double insertionTimes[], double selectionTimes[], double bubbleTimes[], double heapTimes[], double mergeTimes[], double quickTimes[], double radixTimes[]);

int main() {
    srand((unsigned int)time(NULL)); // Seed for random number generation

    int sizes[] = { 1000, 10000, 100000, 1000000, 10000000 }; // Array sizes
    double* insertionTimes = (double*)malloc(5 * sizeof(double)); // Array to store insertion sort times
    double* selectionTimes = (double*)malloc(5 * sizeof(double)); // Array to store selection sort times
    double* bubbleTimes = (double*)malloc(5 * sizeof(double)); // Array to store bubble sort times
    double* heapTimes = (double*)malloc(5 * sizeof(double)); // Array to store heap sort times
    double* mergeTimes = (double*)malloc(5 * sizeof(double)); // Array to store merge sort times
    double* quickTimes = (double*)malloc(5 * sizeof(double)); // Array to store quick sort times
    double* radixTimes = (double*)malloc(5 * sizeof(double)); // Array to store radix sort times

    // Loop through different array sizes
    for (int i = 0; i < 5; i++) {
        int* array = (int*)malloc(sizes[i] * sizeof(int)); // Declare array of current size
        generateRandomArray(array, sizes[i]); // Generate random array

        clock_t start, end;

        // Measure insertion sort time
        start = clock();
        insertionSort(array, sizes[i]);
        end = clock();
        insertionTimes[i] = ((double)(end - start)) / CLOCKS_PER_SEC;

        // Measure selection sort time
        start = clock();
        selectionSort(array, sizes[i]);
        end = clock();
        selectionTimes[i] = ((double)(end - start)) / CLOCKS_PER_SEC;

        // Measure bubble sort time
        start = clock();
        bubbleSort(array, sizes[i]);
        end = clock();
        bubbleTimes[i] = ((double)(end - start)) / CLOCKS_PER_SEC;

        // Measure heap sort time
        start = clock();
        heapSort(array, sizes[i]);
        end = clock();
        heapTimes[i] = ((double)(end - start)) / CLOCKS_PER_SEC;

        // Measure merge sort time
        start = clock();
        mergeSort(array, 0, sizes[i] - 1);
        end = clock();
        mergeTimes[i] = ((double)(end - start)) / CLOCKS_PER_SEC;

        // Measure quick sort time
        start = clock();
        quickSort(array, 0, sizes[i] - 1);
        end = clock();
        quickTimes[i] = ((double)(end - start)) / CLOCKS_PER_SEC;

        // Measure radix sort time
        start = clock();
        radixSort(array, sizes[i]);
        end = clock();
        radixTimes[i] = ((double)(end - start)) / CLOCKS_PER_SEC;

        free(array); // Free dynamically allocated memory
    }

    // Print LaTeX table
    printLatexTable(sizes, insertionTimes, selectionTimes, bubbleTimes, heapTimes, mergeTimes, quickTimes, radixTimes);

    free(insertionTimes); // Free dynamically allocated memory
    free(selectionTimes); // Free dynamically allocated memory
    free(bubbleTimes); // Free dynamically allocated memory
    free(heapTimes); // Free dynamically allocated memory
    free(mergeTimes); // Free dynamically allocated memory
    free(quickTimes); // Free dynamically allocated memory
    free(radixTimes); // Free dynamically allocated memory

    return 0;
}

// Function to generate a random array
void generateRandomArray(int array[], int size) {
    for (int i = 0; i < size; i++) {
        array[i] = rand() % 1000; // Generate random number between 0 and 999
    }
}

// Insertion sort algorithm
void insertionSort(int array[], int size) {
    for (int i = 1; i < size; i++) {
        int key = array[i];
        int j = i - 1;
        while (j >= 0 && array[j] > key) {
            array[j + 1] = array[j];
            j = j - 1;
        }
        array[j + 1] = key;
    }
}

// Selection sort algorithm
void selectionSort(int array[], int size) {
    for (int i = 0; i < size - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < size; j++) {
            if (array[j] < array[minIndex]) {
                minIndex = j;
            }
        }
        int temp = array[i];
        array[i] = array[minIndex];
        array[minIndex] = temp;
    }
}

// Bubble sort algorithm
void bubbleSort(int array[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (array[j] > array[j + 1]) {
                int temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }
}

// Heapify a subtree rooted with node i
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

// Merge two subarrays of array[]
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

// Partition function for quick sort
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

// Counting sort algorithm
void countingSort(int array[], int size, int exp) {
    int output[size]; // Output array
    int count[10] = { 0 };

    // Store count of occurrences in count[]
    for (int i = 0; i < size; i++)
        count[(array[i] / exp) % 10]++;

    // Change count[i] so that count[i] now contains actual position of this digit in output[]
    for (int i = 1; i < 10; i++)
        count[i] += count[i - 1];

    // Build the output array
    for (int i = size - 1; i >= 0; i--) {
        output[count[(array[i] / exp) % 10] - 1] = array[i];
        count[(array[i] / exp) % 10]--;
    }

    // Copy the output array to array[], so that array[] now contains sorted numbers according to current digit
    for (int i = 0; i < size; i++)
        array[i] = output[i];
}

// Radix sort algorithm
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

// Function to print LaTeX table
void printLatexTable(int sizes[], double insertionTimes[], double selectionTimes[], double bubbleTimes[], double heapTimes[], double mergeTimes[], double quickTimes[], double radixTimes[]) {
    printf("\\begin{table}[H]\n");
    printf("    \\centering\n");
    printf("    \\begin{tabular}{|c|c|c|c|c|c|c|c|}\n");
    printf("        \\hline\n");
    printf("        \\textbf{Array Size} & \\textbf{Insertion Sort (s)} & \\textbf{Selection Sort (s)} & \\textbf{Bubble Sort (s)} & \\textbf{Heap Sort (s)} & \\textbf{Merge Sort (s)} & \\textbf{Quick Sort (s)} & \\textbf{Radix Sort (s)} \\\\\n");
    printf("        \\hline\n");
    for (int i = 0; i < 5; i++) {
        printf("        %d & %.6f & %.6f & %.6f & %.6f & %.6f & %.6f & %.6f \\\\\n", sizes[i], insertionTimes[i], selectionTimes[i], bubbleTimes[i], heapTimes[i], mergeTimes[i], quickTimes[i], radixTimes[i]);
    }
    printf("        \\hline\n");
    printf("    \\end{tabular}\n");
    printf("\\end{table}\n");
}
