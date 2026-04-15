#include <iostream>
using namespace std; // This program demonstrates the difference between pass by value and pass by reference in C++.

// Pass by value (copy)
// funtion receives a copy of the argument, so changes to x do not affect num in main and
// does not reurn any value to the caller
void changeValue(int x) {
    x = 100;
}

// Pass by reference (original)
// &x indicates that x is a reference to the original variable passed in, so changes to x will affect num in main and
// does not return any value to the caller
void changeReference(int &x) {
    x = 100;
}

int main() {
    int num = 10;

    cout << "Original num: " << num << endl;

    // Pass by value: num is passed as a copy, so changes in changeValue do not affect num in main
    changeValue(num);
    cout << "After changeValue: " << num << endl;

    // Pass by reference: num is passed as a reference, so changes in changeReference affect num in main
    changeReference(num);
    cout << "After changeReference: " << num << endl;

    cout << endl;

    cout << "Press Enter to exit...";
    cin.get();

    return 0;
}