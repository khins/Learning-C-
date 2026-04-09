#include <iostream>
using namespace std;

void greet() {
    cout << "Welcome to functions in C++!" << endl;
}

int add(int a, int b) {
    return a + b;
}

int main() {
    greet();

    int result = add(4, 6);
    cout << "4 + 6 = " << result << endl;

    return 0;
}
