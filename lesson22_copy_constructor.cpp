#include <iostream>
using namespace std;

// Rule of 3

// If your class uses:

// dynamic memory (new)

// You MUST implement:

// Destructor
// Copy Constructor
// Copy Assignment Operator (next lesson)

class Student {
private:
    string name;
    int* scores;
    int size;
    double* grades; // Just to show multiple dynamic members

public:
    // 🔹 Constructor
    Student(string n, int s) : name(n), size(s) {
        cout << "Constructor called for " << name << endl;

        scores = new int[size];
        grades = new double[size];

        for (int i = 0; i < size; i++) {
            scores[i] = 0;
            grades[i] = 0.0;
        }
    }

    // 🔹 Copy Constructor (DEEP COPY)
    // “Create a new object from an existing one”
    Student(const Student& other) {
        cout << "Copy constructor called for " << other.name << endl;

        name = other.name;
        size = other.size;
        grades = new double[size];

        // allocate new memory
        scores = new int[size];

        // copy values
        for (int i = 0; i < size; i++) {
            scores[i] = other.scores[i];
            grades[i] = other.grades[i];
        }
    }

    // 🔹 Method to set score
    void setScore(int index, int value) {
        if (index >= 0 && index < size) {
            scores[index] = value;
        }
    }

    // 🔹 Print
    void printScores() const {
        cout << name << "'s scores: ";
        for (int i = 0; i < size; i++) {
            cout << scores[i] << " ";
        }
        cout << endl;
    }

    // 🔹 Destructor
    ~Student() {
        cout << "Destructor called for " << name << endl;
        delete[] scores;
        delete[] grades;
    }
};

int main() {
    cout << "=== Creating original object ===" << endl;
    Student s1("Pat Metheny", 3);

    s1.setScore(0, 85);
    s1.setScore(1, 90);
    s1.setScore(2, 95);

    s1.printScores();

    cout << "\n=== Copying object ===" << endl;
    Student s2 = s1;  // COPY CONSTRUCTOR CALLED

    s2.printScores();

    cout << "\n=== Modify copied object ===" << endl;
    s2.setScore(0, 100);

    cout << "Original:" << endl;
    s1.printScores();

    cout << "Copy:" << endl;
    s2.printScores();

    // print memory addresses to show they are different
    cout << "\nMemory addresses:" << endl;
    cout << "Original: " << &s1 << endl;
    cout << "Copy: " << &s2 << endl;


    cout << "=== End of main ===" << endl;

    cout << "Press Enter to exit...";
    cin.get();

    return 0;
}