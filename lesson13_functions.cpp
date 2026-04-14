#include <iostream>
using namespace std;

// Function to calculate sum of two numbers
int add(int a, int b) {
    return a + b;
}

// Function to print a 2D grid
// Note: The size of the grid is fixed to 2 rows and 3 columns for simplicity
// loops through each row and column to print the values of the 2D array
void printGrid(int grid[2][3]) {
    for (int row = 0; row < 2; row++) {
        for (int col = 0; col < 3; col++) {
            cout << grid[row][col] << " ";
        }
        cout << endl;
    }
}

// Main function to demonstrate the use of functions in C++
int main() {
    int result = add(5, 3);
    cout << "Sum: " << result << endl;

    int grid[2][3] = {
        {1, 2, 3},
        {4, 5, 6}
    };

    printGrid(grid);

    cout << endl;
    cout << "Value at row 1, column 2: " << grid[1][2] << endl;
    cout << "Press Enter to exit...";
    cin.get();

    return 0;
}