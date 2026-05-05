#include <iostream>
using namespace std;

class Student {
private:
    string name;
    int* scores;   // dynamic memory
    int size;

public:
    // 🔹 Constructor
    Student(string n, int s) : name(n), size(s) {
        cout << "Constructor called for " << name << endl;

        // allocate dynamic array
        scores = new int[size];

        // initialize values
        for (int i = 0; i < size; i++) {
            scores[i] = 0;
        }
    }

    // 🔹 Method to set score
    void setScore(int index, int value) {
        if (index >= 0 && index < size) {
            scores[index] = value;
        }
    }

    // 🔹 Method to print scores
    void printScores() const {
        cout << name << "'s scores: ";
        for (int i = 0; i < size; i++) {
            cout << scores[i] << " ";
        }
        cout << endl;
    }

    // 🔹 Destructor
    // Automatically called when:

    // Object goes out of scope
    // Program ends
    // delete is used on object pointer
//     Why Destructors Matter

    // 👉 They clean up:
    // dynamic memory (new)
    // file handles
    // network connections
    ~Student() {
        cout << "Destructor called for " << name << endl;

        // free dynamic memory
        delete[] scores; // Prevents memory leaks
        scores = nullptr;
    }
};

int main() {
    cout << "=== Creating Student Object ===" << endl;

    Student s1("Kevin", 3);

    s1.setScore(0, 85);
    s1.setScore(1, 90);
    s1.setScore(2, 95);

    s1.printScores();

    cout << "=== End of main ===" << endl;

    cout << "Press Enter to exit...";
    cin.get();

    return 0;
}