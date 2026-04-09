#include <iostream>
using namespace std;

int main() {
    int age;

    cout << "Enter your age: ";
    cin >> age;

    if (age >= 18) {
        cout << "You are an adult." << endl;
    } else if (age >= 13) {
        cout << "You are a teenager." << endl;
    } else {
        cout << "You are a child." << endl;
    }
    cout << "Press Enter to exit...";
    cin.ignore(10000, '\n');
    cin.get();

    return 0;
}
