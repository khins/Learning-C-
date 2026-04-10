#include <iostream>
using namespace std;

/*
This lesson introduces nested loops, which are loops inside other loops. This is a powerful concept that allows you to work with two-dimensional data structures like matrices or grids.

Good things to debug while stepping through:

watch row and column variables in the inner loop
inspect the output pattern as it's printed
step through the outer loop and see how it controls the rows

This is a strong next lesson because it helps you debug:

how the outer loop controls rows
how the inner loop runs fully for each outer-loop step
how row, column, i, and j change over time
how output formatting works with endl and \t
*/

int main() {
    for (int row = 1; row <= 3; row++) {
        for (int column = 1; column <= 4; column++) {
            cout << "(" << row << "," << column << ") ";
        }

        cout << endl;
    }

    cout << endl;
    cout << "Multiplication table:" << endl;

    for (int i = 1; i <= 3; i++) {
        for (int j = 1; j <= 3; j++) {
            cout << i * j << "\t";
        }

        cout << endl;
    }

    cout << "Press Enter to exit...";
    cin.get();

    return 0;
}
