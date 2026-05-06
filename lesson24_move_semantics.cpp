#include <iostream>
using namespace std;

class Student {
private:
    string name;
    int* scores;
    int size;

public:
    // 🔹 Constructor
    Student(string n, int s) : name(n), size(s) {
        cout << "Constructor called for " << name << endl;

        scores = new int[size];
        for (int i = 0; i < size; i++) {
            scores[i] = 0;
        }
    }

    // 🔹 Copy Constructor (deep copy)
    Student(const Student& other) {
        cout << "Copy constructor called for " << other.name << endl;

        name = other.name;
        size = other.size;

        scores = new int[size];
        for (int i = 0; i < size; i++) {
            scores[i] = other.scores[i];
        }
    }

    // 🔹 Move Constructor (🔥 NEW)
    Student(Student&& other) noexcept {
        cout << "Move constructor called for " << other.name << endl;

        // steal resources
        name = other.name;
        size = other.size;
        scores = other.scores;

        // leave other in safe state
        other.scores = nullptr;
        other.size = 0;
    }

    // 🔹 Copy Assignment
    Student& operator=(const Student& other) {
        cout << "Copy assignment called for " << other.name << endl;

        if (this == &other) return *this;

        delete[] scores;

        name = other.name;
        size = other.size;

        scores = new int[size];
        for (int i = 0; i < size; i++) {
            scores[i] = other.scores[i];
        }

        return *this;
    }

    // 🔹 Move Assignment (🔥 NEW)
    Student& operator=(Student&& other) noexcept {
        cout << "Move assignment called for " << other.name << endl;

        if (this == &other) return *this;

        // free existing memory
        delete[] scores;

        // steal resources
        name = other.name;
        size = other.size;
        scores = other.scores;

        // reset source
        other.scores = nullptr;
        other.size = 0;

        return *this;
    }

    // 🔹 Set score
    void setScore(int i, int val) {
        if (i >= 0 && i < size) {
            scores[i] = val;
        }
    }

    // 🔹 Print
    void print() const {
        cout << name << ": ";
        for (int i = 0; i < size; i++) {
            cout << scores[i] << " ";
        }
        cout << endl;
    }

    // print letter grade based on average score
    void printGrade() const {
        double average = 0.0;
        for (int i = 0; i < size; i++) {
            average += scores[i];
        }
        average /= size;

        char grade;
        if (average >= 90) {
            grade = 'A';
        } else if (average >= 80) {
            grade = 'B';
        } else if (average >= 70) {
            grade = 'C';
        } else {
            grade = 'F';
        }
        cout << name << "'s grade: " << grade << endl;
    }

    // print if student is honors (average >= 90)
    void printHonors() const {
        double average = 0.0;
        for (int i = 0; i < size; i++) {
            average += scores[i];
        }
        average /= size;

        cout << name << " is " << (average >= 90 ? "an honors student" : "not an honors student") << endl;
    }   


    // 🔹 Destructor
    ~Student() {
        cout << "Destructor called for " << name << endl;
        delete[] scores;
    }
};

int main() {
    cout << "=== Creating object ===" << endl;

    Student s1("Bob Eubanks", 3);
    s1.setScore(0, 85);
    s1.setScore(1, 90);
    s1.setScore(2, 95);
    s1.printGrade();
    s1.printHonors();

    cout << "\n=== Copying object ===" << endl;
    Student s2 = s1;  // copy

    cout << "\n=== Moving object ===" << endl;
    Student s3 = std::move(s1);  // move - s1 is now in a valid but unspecified state

    cout << "\n=== After move ===" << endl;
    cout << "s2: ";
    s2.print();

    cout << "s3: ";
    s3.print();

    cout << "\n=== Move assignment ===" << endl;
    Student s4("Temp", 2);
    s4 = std::move(s2); // move transfers ownership of resources from s2 to s4, leaving s2 in a valid but unspecified state

    cout << "s4: ";
    s4.print();

    // Print addresses before/after move
    cout << "Address of s1: " << &s1 << endl;
    cout << "Address of s2: " << &s2 << endl;
    cout << "Address of s3: " << &s3 << endl;
    cout << "Address of s4: " << &s4 << endl;


    cout << "\n=== End of program ===" << endl;
    
    cout << "Press Enter to exit...";
    cin.get();
    return 0;
}