#include <iostream>
#include <vector>
using namespace std;

// 🔹 Define a class (like a struct, but with behavior + access control)
class Student {
private:
    string name;
    int age;
    double gpa;

public:
    // 🔹 Constructor (runs when object is created)
    // prevent negative age and gpa > 4.0
    Student(string n, int a, double g) {
        // check for valid age and gpa, if invalid set to default values
        if (a < 0) {
            age = 0; // default to 0 if negative
        } else {
            age = a;
        }
        name = n;
        if (g < 0.0 || g > 4.0) {
            gpa = 0.0; // default to 0.0 if invalid
        } else {
            gpa = g;
        }
    }

    // 🔹 Method to display student info
    void printInfo() const {
        cout << "Name: " << name << endl;
        cout << "Age: " << age << endl;
        cout << "GPA: " << gpa << endl;
        cout << "----------------------" << endl;
    }

    // 🔹 Getter methods (access private data)
    string getName() const {
        return name;
    }

    double getGpa() const {
        return gpa;
    }

    // 🔹 Setter method (modify data safely)
    void setGpa(double newGpa) {
        if (newGpa >= 0.0 && newGpa <= 4.0) {
            gpa = newGpa;
        }
    }

    bool isHonors() const {
        return gpa >= 3.5;
    }

    void increaseGpa(double amount) {
        setGpa(gpa + amount); // use setter to ensure valid GPA
    }
};

int main() {
    // 🔹 1. Create objects using constructor
    Student s1("Kevin", 25, 3.8);
    Student s2("Alice", 20, 2.5);
    Student s3("Invalid", -5, 5.0); // should default to age=0 and gpa=0.0

    cout << "Single Student:" << endl;
    s1.printInfo();

    // 🔹 2. Store objects in vector
    vector<Student> students;
    students.push_back(s1);
    students.push_back(s2);
    students.push_back(Student("Bob", 22, 3.2));

    cout << "\nAll Students:" << endl;
    for (const Student& s : students) {
        s.printInfo();
        s.isHonors() ? cout << "Honors Student!" : cout << "Not Honors";
        cout << "\n----------------------" << endl;
    }

    // 🔹 3. Modify object using setter
    students[0].setGpa(4.0); // Encapsulation (CORE OOP IDEA)
    students[0].isHonors();
    students[0].increaseGpa(0.5); // should not exceed 4.0

    cout << "\nAfter GPA Update:" << endl;
    cout << (students[0].isHonors() ? "Honors Student!" : "Not Honors") << endl;
    cout << "Updated GPA: " << students[0].getGpa() << endl;
    students[0].printInfo();

    // 🔹 4. Access data using getter
    cout << "\nAccess via getter:" << endl;
    cout << students[1].getName() << "'s GPA: " 
         << students[1].getGpa() << endl;

    cout << "\nPress Enter to exit...";
    cin.get();

    return 0;
}