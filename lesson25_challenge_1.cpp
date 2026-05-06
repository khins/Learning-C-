#include <iostream>
#include <memory>
using namespace std;

class Student {
private:
    string name;
    unique_ptr<int[]> scores;  // 🔥 smart pointer array
    int size;

public:
    // 🔹 Constructor
    Student(string n, int s) : name(n), size(s), scores(make_unique<int[]>(s)) {
        cout << "Constructor called for " << name << endl;

        for (int i = 0; i < size; i++) {
            scores[i] = 0;
        }
    }

    // 🔹 Copy Constructor (must manually handle since unique_ptr can't copy)
    Student(const Student& other) : name(other.name), size(other.size), scores(make_unique<int[]>(other.size)) {
        cout << "Copy constructor called for " << other.name << endl;

        for (int i = 0; i < size; i++) {
            scores[i] = other.scores[i];
        }
    }

    // 🔹 Copy Assignment
    Student& operator=(const Student& other) {
        cout << "Copy assignment called for " << other.name << endl;

        if (this == &other) return *this;

        name = other.name;
        size = other.size;

        scores = make_unique<int[]>(size);

        for (int i = 0; i < size; i++) {
            scores[i] = other.scores[i];
        }

        return *this;
    }

    // 🔹 Move Constructor (automatic behavior works, but we define for clarity)
    Student(Student&& other) noexcept
        : name(move(other.name)), size(other.size), scores(move(other.scores)) {
        cout << "Move constructor called" << endl;
    }

    // 🔹 Move Assignment
    Student& operator=(Student&& other) noexcept {
        cout << "Move assignment called" << endl;

        if (this == &other) return *this;

        name = move(other.name);
        size = other.size;
        scores = move(other.scores);

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

    // 🔹 Destructor (no manual delete needed!)
    ~Student() {
        cout << "Destructor called for " << name << endl;
    }
};

int main() {
    cout << "=== Creating student ===" << endl;
    Student s1("Pat Metheny", 3);

    s1.setScore(0, 85);
    s1.setScore(1, 90);
    s1.setScore(2, 95);

    cout << "\n=== Copying student ===" << endl;
    Student s2 = s1;

    cout << "\n=== Moving student ===" << endl;
    Student s3 = move(s1);

    cout << "\n=== Results ===" << endl;
    s2.print();
    s3.print();

    cout << "\n=== End of program ===" << endl;
    return 0;
}