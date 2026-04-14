#include <iostream>
using namespace std;  // Avoids writing std:: before every standard library object or function

// This program demonstrates the use of 2D arrays in C++.
int main() {
    // Declare and initialize a 2D array with 2 rows and 3 columns
    int grid[2][3] = {
        {1, 2, 3},
        {4, 5, 6}
    };

    cout << "2D array values:" << endl; // Print the values of the 2D array using nested loops

    // loop through each row and column to print the values of the 2D array
    for (int row = 0; row < 2; row++) {
        for (int column = 0; column < 3; column++) {
            cout << grid[row][column] << " ";
        }

        cout << endl;
    }

    cout << endl;
    cout << "Value at row 1, column 2: " << grid[1][2] << endl;
    cout << "Press Enter to exit...";
    cin.get();

    return 0;
}
