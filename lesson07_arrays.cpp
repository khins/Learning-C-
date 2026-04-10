#include <iostream>
using namespace std;

int main() {
    int scores[5] = {90, 85, 88, 92, 95};
    int total = 0;

    cout << "Student scores:" << endl;

    for (int i = 0; i < 5; i++) {
        cout << "Score " << i + 1 << ": " << scores[i] << endl;
        total += scores[i];
    }

    double average = total / 5.0;
    cout << "Average score: " << average << endl;
    cout << "Press Enter to exit...";
    cin.get();

    return 0;
}
