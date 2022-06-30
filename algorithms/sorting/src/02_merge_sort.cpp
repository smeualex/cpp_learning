#include <iostream>
#include <memory>

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
    
    auto const arr1Size = mid - left + 1;
    auto const arr2Size = right - mid;
 
    // Create temp arrays
    auto leftArray  = std::make_unique<int[]>(arr1Size);
    auto rightArray = std::make_unique<int[]>(arr2Size);
 
    // Copy data to temp arrays leftArray[] and rightArray[]
    for (auto i = 0; i < arr1Size; i++)
        leftArray[i] = array[left + i];

    for (auto j = 0; j < arr2Size; j++)
        rightArray[j] = array[mid + 1 + j];
 
    int index1 = 0;         // Initial index of first sub-array
    int index2 = 0;         // Initial index of second sub-array
    int indexMerged = left; // Initial index of merged array
 
    // Merge the temp arrays back into array[left..right]
    while (index1 < arr1Size && index2 < arr2Size) 
    {
        if (leftArray[index1] <= rightArray[index2]) 
        {
            array[indexMerged] = leftArray[index1];
            index1++;
        }
        else 
        {
            array[indexMerged] = rightArray[index2];
            index2++;
        }

        indexMerged++;
    }

    // Copy any remaining elements
    // leftArray
    while (index1 < arr1Size) 
    {
        array[indexMerged] = leftArray[index1];
        index1++;
        indexMerged++;
    }
    // rightArray
    while (index2 < arr2Size) 
    {
        array[indexMerged] = rightArray[index2];
        index2++;
        indexMerged++;
    }

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