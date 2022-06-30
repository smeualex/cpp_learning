#include <iostream>

using namespace std;

// Function to print an array
void printArray(int A[], int size)
{
    cout << "Array: ";
    for (auto i = 0; i < size; i++)
        cout << A[i] << " ";
    cout << endl;
}


// Merges two subarrays of array[].
// First subarray is  arr[begin..mid]
// Second subarray is arr[mid+1..end]
void merge(int array[], const int left, const int mid, const int right) 
{
    static int i = 1;
    cout << " merge " << i++ << ": left=" << left 
        << "; mid=" << mid << "; right=" << right << "; ";
    
    const int s1Size = mid - left + 1;
    const int s2Size = right - mid;

    // Create temp arrays
    int* leftArray  = new int[s1Size];
    int* rightArray = new int[s2Size];
 
    // Copy data to temp arrays leftArray[] and rightArray[]
    for (auto i = 0; i < s1Size; i++)
        leftArray[i] = array[left + i];

    for (auto j = 0; j < s2Size; j++)
        rightArray[j] = array[mid + 1 + j];
 
    int indexOfSubArrayOne = 0;    // Initial index of first sub-array
    int indexOfSubArrayTwo = 0;    // Initial index of second sub-array
    int indexOfMergedArray = left; // Initial index of merged array
 
    // Merge the temp arrays back into array[left..right]
    while (indexOfSubArrayOne < s1Size && indexOfSubArrayTwo < s2Size) 
    {
        if (leftArray[indexOfSubArrayOne] <= rightArray[indexOfSubArrayTwo]) 
        {
            array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
            indexOfSubArrayOne++;
        }
        else 
        {
            array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
            indexOfSubArrayTwo++;
        }
        indexOfMergedArray++;
    }
    // Copy the remaining elements of
    // left[], if there are any
    while (indexOfSubArrayOne < s1Size) 
    {
        array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
        indexOfSubArrayOne++;
        indexOfMergedArray++;
    }
    // Copy the remaining elements of
    // right[], if there are any
    while (indexOfSubArrayTwo < s2Size) 
    {
        array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
        indexOfSubArrayTwo++;
        indexOfMergedArray++;
    }

    delete[] leftArray;
    delete[] rightArray;

    printArray(array, 6);
}

void mergeSort(int array[], const int begin, const int end) 
{
    if(begin >= end)
        return;

    auto mid = begin + (end - begin) / 2;

    mergeSort(array, begin, mid);       // left half
    mergeSort(array, mid + 1, end);     // right half
    merge(array, begin, mid, end);      // merge the 2 halves + sort the values
}



int main() {
    int arr[] = { 12, 11, 13, 7, 6, 5 };
    auto size = sizeof(arr) / sizeof(arr[0]);

    printArray(arr, size);

    mergeSort(arr, 0, size - 1);

    printArray(arr, size);

    return 0;
}