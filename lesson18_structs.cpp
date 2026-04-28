// lesson18_structs.cpp
#include <iostream>
#include <vector>
using namespace std;

// 🔹 Define a struct (custom data type)
struct Student {
    string name;
    int age;
    double gpa;
};

// 🔹 Function to print a single student
// returns nothing, takes a reference to a Student struct and prints its details to the console
void printStudent(const Student& s) {
    cout << "Name: " << s.name << endl;
    cout << "Age: " << s.age << endl;
    cout << "GPA: " << s.gpa << endl;
    cout << "----------------------" << endl;
}

// method main to demonstrate usage of structs, creating instances, and using vectors of structs
int main() {
    // 🔹 1. Create a single struct instance
    Student student1;

    student1.name = "Kevin";
    student1.age = 25;
    student1.gpa = 3.8;

    cout << "Single Student:" << endl;
    //call the printStudent method to print the details of student1 to the console
    printStudent(student1);

    // 🔹 2. Create another student using initialization
    Student student2 = {"Alice", 20, 3.5};

    cout << "\nAnother Student:" << endl;
    printStudent(student2);

    // 🔹 3. Vector of structs (VERY important)
    vector<Student> students;

    students.push_back(student1); // add student1 to the vector
    students.push_back(student2);
    students.push_back({"Bob", 22, 3.2});

    cout << "\nAll Students:" << endl;

    // loop through vector of students and print each one using the printStudent method
    for (const Student& s : students) {
        printStudent(s);
    }

    // 🔹 4. Modify a struct inside vector
    // access the first student in the vector and update their GPA, then print the updated student details to the console
    students[0].gpa = 4.0;

    cout << "\nAfter GPA Update:" << endl;
    printStudent(students[0]);

    // 🔹 5. User input into struct
    Student newStudent;

    cout << "\nEnter new student name: ";
    cin >> newStudent.name;

    cout << "Enter age: ";
    cin >> newStudent.age;

    cout << "Enter GPA: ";
    cin >> newStudent.gpa;

    students.push_back(newStudent);

    cout << "\nUpdated Student List:" << endl;
    for (const Student& s : students) {
        printStudent(s);
    }

    cout << "Press Enter to exit...";
    cin.ignore();
    cin.get();

    return 0;
}