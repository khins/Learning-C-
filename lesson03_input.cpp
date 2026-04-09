#include <iostream>
#include <string>
using namespace std;

int main() {
    string name;
    int age;

    cout << "Enter your name: ";
    cin >> name;

    cout << "Enter your age: ";
    cin >> age;

    cout << "Hello " << name << ", next year you will be " << age + 1 << " years old." << endl;
    cout << "Press Enter to exit...";
    cin.ignore(10000, '\n');
    cin.get();

    return 0;
}
