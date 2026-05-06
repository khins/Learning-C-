#include <iostream>
#include <memory>   // 🔥 required for smart pointers, 👉 Memory is automatically freed
using namespace std;

class Student {
private:
    string name;

public:
    Student(string n) : name(n) {
        cout << "Constructor called for " << name << endl;
    }

    void print() const {
        cout << "Student: " << name << endl;
    }

    ~Student() {
        cout << "Destructor called for " << name << endl;
    }
};

int main() {
    cout << "=== unique_ptr example ===" << endl;

    // 🔹 1. unique_ptr (exclusive ownership)
    // make_unique is the recommended way to create unique_ptr
    //     Rules:
    // Only one owner
    // Cannot copy
    // Can move
    unique_ptr<Student> s1 = make_unique<Student>("Walt Disney");

    s1->print();

    // 🔹 Move ownership
    // unique_ptr cannot be copied, but can be moved
    // Ownership transferred
    // 👉 s1 becomes empty
    unique_ptr<Student> s2 = move(s1);

    if (!s1) {
        cout << "s1 is now empty after move" << endl;
    }

    s2->print();

    cout << "\n=== shared_ptr example ===" << endl;

    // 🔹 2. shared_ptr (shared ownership)
    // make_shared is the recommended way to create shared_ptr
    shared_ptr<Student> sp1 = make_shared<Student>("Alice");

    cout << "Reference count: " << sp1.use_count() << endl;

    shared_ptr<Student> sp2 = sp1; // Multiple owners allowed

    cout << "Reference count after copy: " << sp1.use_count() << endl;

    sp2->print();

    cout << "\n=== weak_ptr example ===" << endl;

    // 🔹 3. weak_ptr (non-owning reference)
    // weak_ptr does not affect reference count and can be used to break cycles
    // Used to:

// avoid circular references
// observe object safely
    weak_ptr<Student> wp = sp1;

    cout << "Reference count (still): " << sp1.use_count() << endl;

    // lock weak_ptr to use it
    if (auto temp = wp.lock()) {
        temp->print();
    }

    cout << "\n=== End of program ===" << endl;
    
    cout << "Press Enter to exit...";
    cin.get();
    return 0;
}