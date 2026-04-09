#include <iostream>
using namespace std;

int main() {
    cout << "For loop:" << endl;
    for (int i = 1; i <= 5; i++) {
        cout << "Count: " << i << endl;
    }

    cout << endl;
    cout << "While loop:" << endl;

    int number = 3;
    while (number > 0) {
        cout << "Countdown: " << number << endl;
        number--;
    }
    cout << "Press Enter to exit...";
    cin.get();

    return 0;
}
