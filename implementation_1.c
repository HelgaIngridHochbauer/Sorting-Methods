#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function prototypes
void generateRandomArray(int array[], int size);
void insertionSort(int array[], int size);
void selectionSort(int array[], int size);
void bubbleSort(int array[], int size);
void printLatexTable(int sizes[], double insertionTimes[], double selectionTimes[], double bubbleTimes[]);

int main() {
    srand((unsigned int)time(NULL)); // Seed for random number generation

    int sizes[] = {  1000, 10, 10, 10, 10, }; // Array sizes
    double* insertionTimes = (double*)malloc(5 * sizeof(double)); // Array to store insertion sort times
    double* selectionTimes = (double*)malloc(5 * sizeof(double)); // Array to store selection sort times
    double* bubbleTimes = (double*)malloc(5 * sizeof(double)); // Array to store bubble sort times

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

        free(array); // Free dynamically allocated memory
    }

    // Print LaTeX table
    printLatexTable(sizes, insertionTimes, selectionTimes, bubbleTimes);

    free(insertionTimes); // Free dynamically allocated memory
    free(selectionTimes); // Free dynamically allocated memory
    free(bubbleTimes); // Free dynamically allocated memory

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

// Function to print LaTeX table
void printLatexTable(int sizes[], double insertionTimes[], double selectionTimes[], double bubbleTimes[]) {
    printf("\\begin{table}[H]\n");
    printf("    \\centering\n");
    printf("    \\begin{tabular}{|c|c|c|c|}\n");
    printf("        \\hline\n");
    printf("        \\textbf{Array Size} & \\textbf{Insertion Sort (s)} & \\textbf{Selection Sort (s)} & \\textbf{Bubble Sort (s)} \\\\\n");
    printf("        \\hline\n");
    for (int i = 0; i < 5; i++) {
        printf("        %d & %.6f & %.6f & %.6f \\\\\n", sizes[i], insertionTimes[i], selectionTimes[i], bubbleTimes[i]);
    }
    printf("        \\hline\n");
    printf("    \\end{tabular}\n");
    printf("\\end{table}\n");
}
