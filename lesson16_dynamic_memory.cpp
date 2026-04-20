// lesson16_dynamic_memory.cpp
// The new lesson introduces:

// new for a single dynamic int
// delete and resetting the pointer to nullptr
// new[] for a dynamic array
// delete[] for cleanup
// 🧠 Big Picture: What This Program Teaches

// 👉 Two kinds of memory usage:

// Stack → automatic (local variables)
// Heap → manual (you control allocation + cleanup)

#include <iostream>
using namespace std;

int main() {
    // Dynamic memory stores values on the heap instead of inside main's local stack space.
    // 🧠 What’s happening:
    // new int → asks OS for memory (on heap)
    // Returns an address
    // That address is stored in numberPtr
    int* numberPtr = new int; // allocate memory for a single int on the heap

    *numberPtr = 42; // store value at the allocated memory address
    // 👉 Dereferencing:

    // “Go to the address and store 42”

    // print the value and address
    cout << "Dynamic single value:" << endl;
    cout << "Address stored in numberPtr: " << numberPtr << endl;
    cout << "Value stored at that address: " << *numberPtr << endl;

    *numberPtr = 99; // update the value at the allocated memory address, Changes the same memory location
    cout << "Updated value: " << *numberPtr << endl;

    // Use delete when you are finished with memory created by new.
    delete numberPtr; // free the allocated memory, critical to prevent memory leaks
    numberPtr = nullptr; // reset pointer to nullptr to avoid dangling pointer issues

    cout << "\nAfter delete, numberPtr = " << numberPtr << endl;

    // Dynamic array allocation using new[]
    int size = 3;
    int* scores = new int[size];

    scores[0] = 85;
    scores[1] = 90;
    scores[2] = 95;

    cout << "\nDynamic array values:" << endl;
    // Loop through the dynamic array and print values
    for (int i = 0; i < size; i++) {
        cout << "scores[" << i << "] = " << scores[i] << endl;
    }

    delete[] scores; // free the allocated array memory
    scores = nullptr;

    cout << "\nMemory cleaned up with delete and delete[]!" << endl;

    cout << "Press Enter to exit...";
    cin.get();

    return 0;
}
