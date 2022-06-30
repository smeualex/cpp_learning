/* C++ implementation of QuickSort */
#include<iostream>
#include<string>
#include<iomanip>
using namespace std;

// A utility function to swap two elements
void swap(int* a, int* b)
{
    int t = *a;
    *a = *b;
    *b = t;
}


void printArray(int arr[], int size, const std::string msg = "")
{
    cout << msg << ": ";
    for (int i = 0; i < size; i++)
        cout << setw(3) << arr[i] << " ";
    cout << endl;
}

void printArray2(int arr[], const int start, int end, const std::string msg)
{
    cout << msg << ": ";
    
    for (int i = 0; i < start; i++)
        cout << setw(3) << " ";

    for (int i = start; i <= end; i++)
        cout << setw(2) << arr[i] << " ";

    cout << endl;
}


/* This function takes last element as pivot, places
the pivot element at its correct position in sorted
array, and places all smaller (smaller than pivot)
to left of pivot and all greater elements to right
of pivot */
int partition (int arr[], int low, int high)
{
    static int d = 1;

    int pivot = arr[high];  // pivot
    int i = (low - 1);      // Index of smaller element and indicates 
                            // the right position of pivot found so far

    printArray2(arr, low, high, "   partition() before " + std::to_string(d));

    for (int j = low; j <= high - 1; j++)
    {
        // If current element is smaller than the pivot
        if (arr[j] < pivot)
        {
            i++;                        // increment index of smaller element
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);

    printArray2(arr, low, high, "   partition() after  " + std::to_string(d));
    d++;
    return (i + 1);
}

// The main function that implements QuickSort
//      arr[] --> Array to be sorted,
//      low   --> Starting index,
//      high  --> Ending index 
void quickSort(int arr[], int low, int high)
{
    static int i = 1;

    printArray2(arr, low, high, "quickSort() before    " + std::to_string(i));

    if (low < high)
    {
        // pi is partitioning index, arr[p] is now at right place
        int pi = partition(arr, low, high);

        // Separately sort elements before partition and after partition
        quickSort(arr, low, pi - 1);
        printArray2(arr, low, high, "quickSort() after L   " + std::to_string(i));

        quickSort(arr, pi + 1, high);
        printArray2(arr, low, high, "quickSort() after R   " + std::to_string(i));
    }
}


int main()
{
    int arr[] = {10, 7, 3, 9, 1, 5, 4, 2, 6};
    int n = sizeof(arr) / sizeof(arr[0]);
    printArray(arr, n, "Initial array");
    cout << endl;

    quickSort(arr, 0, n - 1);
    
    cout << endl;
    printArray(arr, n, "Sorted array");
    
    return 0;
}
