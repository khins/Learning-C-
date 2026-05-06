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
            scores[i] = i * 10;
        }
    }

    // 🔹 Copy Constructor
    Student(const Student& other) {
        cout << "Copy constructor called for " << other.name << endl;

        name = other.name;
        size = other.size;

        scores = new int[size];
        for (int i = 0; i < size; i++) {
            scores[i] = other.scores[i];
        }
    }

    // 🔹 Move Constructor
    Student(Student&& other) noexcept {
        cout << "Move constructor called for " << other.name << endl;

        name = other.name;
        size = other.size;
        scores = other.scores;

        other.scores = nullptr;
        other.size = 0;
    }

    // 🔹 Destructor
    ~Student() {
        cout << "Destructor called for " << name << endl;
        delete[] scores;
    }

    void print() const {
        cout << name << ": ";
        for (int i = 0; i < size; i++) {
            cout << scores[i] << " ";
        }
        cout << endl;
    }
};

// 🔥 Function returning object
Student createStudent() {
    Student temp("Roger Penrose", 3);

    cout << "Returning from function..." << endl;
    // return temp;   // ⚡ move or elision happens here
    return std::move(temp); // force move - temp is now in a valid but unspecified state
}

int main() {
    cout << "=== Calling function ===" << endl;

    Student s1 = createStudent();

    cout << "\n=== After return ===" << endl;
    s1.print();

    cout << "\n=== End of program ===" << endl;

    cout << "Press Enter to exit...";
    cin.get();
    return 0;
}