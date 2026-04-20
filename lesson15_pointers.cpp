// lesson15_pointers.cpp

#include <iostream>
using namespace std;

int main() {
    int num = 10;

    // Pointer declaration
    // 🔹 1. Pointer Declaration
    // “ptr stores the memory address of num”
    // 🔹 2. Address Operator &
    // 👉 Means:
    // “Where in memory is this variable stored?”
    // 🔹 3. Dereference Operator 
    // 👉 Means:
    // “What value is stored at this memory address?”
    int* ptr = &num;

    cout << "Value of num: " << num << endl;
    cout << "Address of num: " << &num << endl;

    cout << "Pointer ptr (stores address): " << ptr << endl;
    cout << "Value pointed to by ptr: " << *ptr << endl;

    // Modify value using pointer, sets num to 20
    *ptr = 20;

    cout << "\nAfter modifying through pointer:" << endl;
    cout << "num = " << num << endl;
    cout << "*ptr = " << *ptr << endl;

    // Pointer with arrays
    int arr[3] = {100, 200, 300};
    int* arrPtr = arr;  // same as &arr[0]

    cout << "\nArray using pointer:" << endl;
    // loop through array using pointer arithmetic
    for (int i = 0; i < 3; i++) {
        cout << *(arrPtr + i) << " ";
    }
    cout << endl;

    cout << "Press Enter to exit...";
    cin.get();

    return 0;
}