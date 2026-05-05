    #include <iostream>
using namespace std;

// 🔹 This class demonstrates the Rule of Three
// If your class uses dynamic memory, you must implement:
// 1. Destructor
// 2. Copy Constructor
// 3. Copy Assignment Operator
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

    // 🔹 Copy Assignment Operator
    Student& operator=(const Student& other) {
        cout << "Copy assignment called for " << other.name << endl;

        // 🔸 1. Self-assignment check
        if (this == &other) {
            return *this;
        }

        // 🔸 2. Free existing memory
        delete[] scores;

        // 🔸 3. Copy values
        name = other.name;
        size = other.size;

        scores = new int[size];
        for (int i = 0; i < size; i++) {
            scores[i] = other.scores[i];
        }

        // 🔸 4. Return current object
        return *this;
    }

    // 🔹 Set score
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

    // print grade letter (just for demonstration)
    void printGrade() const {
        cout << name << "'s grade: ";
        for (int i = 0; i < size; i++) {
            char grade;
            if (scores[i] >= 90) {
                grade = 'A';
            } else if (scores[i] >= 80) {
                grade = 'B';
            } else if (scores[i] >= 70) {
                grade = 'C';
            } else if (scores[i] >= 60) {
                grade = 'D';
            } else {
                grade = 'F';
            }
            cout << grade << " ";
        }
        cout << endl;
    }

    // print is student honors (average >= 90)
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
    cout << "=== Creating objects ===" << endl;

    Student s1("James Bond", 3);
    s1.setScore(0, 85);
    s1.setScore(1, 90);
    s1.setScore(2, 95);
    s1.printGrade();
    s1.printHonors();

    Student s2("Janice West", 3);
    s2.setScore(0, 75);
    s2.setScore(1, 80); 
    s2.setScore(2, 85);
    s2.printGrade();
    s2.printHonors();

    cout << "\n=== Before assignment ===" << endl;
    s1.printScores();
    s2.printScores();
    s2.printGrade();

    // 🔹 Copy assignment happens here
    cout << "\n=== Assigning s2 = s1 ===" << endl;
    s2 = s1;

    cout << "\n=== After assignment ===" << endl;
    s1.printScores();
    s2.printScores();
    s1.printGrade();
    s2.printGrade();


    // 🔹 Modify s2 to prove deep copy
    cout << "\n=== Modify s2 ===" << endl;
    s2.setScore(0, 100);
    s2.printScores();
    s1.printScores();

    cout << "s1:" << endl;
    s1.printScores();
    s1.printGrade();

    cout << "s2:" << endl;
    s2.printScores();
    s2.printGrade();

    cout << "\n=== End of program ===" << endl;

    cout << "Press Enter to exit...";
    cin.get();

    return 0;
}