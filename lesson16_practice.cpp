// lesson16_practice.cpp
// Dynamic allocation from user input
// Using new[] and indexing
#include <iostream>
using namespace std;

// 🔹 Challenge 2: Sum array using pointer
int sum(int* arr, int size) {
    int total = 0;

    // loop through array using pointer arithmetic
    // passing arr is like passing &arr[0], so we can use pointer arithmetic to access elements
    for (int i = 0; i < size; i++) {
        total += arr[i];  // could also use *(arr + i)
    }

    return total;
}

// 🔹 Challenge 3: Resize array manually
int* resizeArray(int* oldArr, int oldSize, int newSize) {
    // Allocate new array
    int* newArr = new int[newSize];

    // Copy values from old array
    for (int i = 0; i < oldSize && i < newSize; i++) {
        newArr[i] = oldArr[i];
    }

    // Initialize remaining elements if new array is bigger
    for (int i = oldSize; i < newSize; i++) {
        newArr[i] = 0;
    }

    // Free old memory
    delete[] oldArr;

    return newArr;  // return new pointer
}

int main() {
    cout << "===== Challenge 1: Dynamic Input Array =====" << endl;

    int size;
    cout << "Enter number of elements: ";
    cin >> size;

    // Allocate dynamically
    int* arr = new int[size];

    // Fill array
    for (int i = 0; i < size; i++) {
        cout << "Enter value for index " << i << ": ";
        cin >> arr[i];
    }

    // Print array
    cout << "\nYou entered:" << endl;
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    // 🔹 Challenge 2: Sum
    int total = sum(arr, size);
    cout << "Sum of elements: " << total << endl;

    // 🔹 Challenge 3: Resize
    cout << "\n===== Resizing Array =====" << endl;
    int newSize;
    cout << "Enter new size: ";
    cin >> newSize;

    arr = resizeArray(arr, size, newSize);

    // Update size variable
    size = newSize;

    // Print resized array
    cout << "\nResized array:" << endl;
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    // Cleanup
    delete[] arr;
    arr = nullptr;

    cout << "\nMemory cleaned up successfully!" << endl;

    cout << "Press Enter to exit...";
    cin.ignore();
    cin.get();

    return 0;
}