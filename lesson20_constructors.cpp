#include <iostream>
using namespace std;

class Student {
private:
    string name;
    int age;
    double gpa;

public:
    // 🔹 1. Default constructor
    Student() {
        name = "Unknown";
        age = 0;
        gpa = 0.0;
    }

    // 🔹 2. Parameterized constructor
    // Add validation inside constructor
    // Use constructor initializer list
    Student(string n, int a, double g) : name(n), age(a), gpa(g) {
        if (age < 0) {
            age = 0;
        }
        if (g < 0.0 || g > 4.0) {
            gpa = 0.0;
        }
    }

    // 🔹 3. Overloaded constructor (partial data)
    Student(string n) : name(n), age(0), gpa(0.0) {
    }

    Student(int a) {
        name = "Unknown";
        age = a;
        gpa = 0.0;
    }

    // 🔹 Method to display info
    void printInfo() const {
        cout << "Name: " << name << endl;
        cout << "Age: " << age << endl;
        cout << "GPA: " << gpa << endl;
        cout << "----------------------" << endl;
    }
};

// Student(...) = different ways to create the same object
int main() {
    // 🔹 Using default constructor
    Student s1;
    cout << "Default constructor:" << endl;
    s1.printInfo();

    // 🔹 Using full constructor
    Student s2("Davy", 35, 0);
    cout << "\nParameterized constructor:" << endl;
    s2.printInfo();

    // 🔹 Using overloaded constructor
    Student s3("Alice");
    cout << "\nOverloaded constructor (name only):" << endl;
    s3.printInfo();

    Student s4(30);
    cout << "\nOverloaded constructor (age only):" << endl;
    s4.printInfo();

    cout << "Press Enter to exit...";
    cin.get();

    return 0;
}