// lesson17_vectors.cpp
// 🧠 What You’re Learning (Big Shift)
// 🔥 Vectors = Dynamic Arrays (But Safe)
#include <iostream>
#include <vector>
using namespace std;

int main() {
    // 🔹 1. Create a vector (dynamic array)
    vector<int> numbers; // no manual size needed, it grows as we add elements, no leaking memory

    // 🔹 2. Add elements, using push_back, automatically resizes memory
    numbers.push_back(10);
    numbers.push_back(20);
    numbers.push_back(30);

    cout << "Initial vector values:" << endl;
    // loop through vector using index
    for (int i = 0; i < numbers.size(); i++) {
        cout << numbers[i] << " ";
    }
    cout << endl;

    // 🔹 3. Access elements
    cout << "\nFirst element: " << numbers[0] << endl;
    cout << "Last element: " << numbers[numbers.size() - 1] << endl; // Size always accurate (unlike raw arrays)

    // 🔹 4. Modify elements
    numbers[1] = 99;

    cout << "\nAfter modification:" << endl;
    // modern C++ style loop (range-based for loop)
    for (int num : numbers) {   // range-based loop
        cout << num << " ";
    }
    cout << endl;

    // 🔹 5. Vector size
    cout << "\nVector size: " << numbers.size() << endl;

    // 🔹 6. Remove last element
    numbers.pop_back();

    cout << "\nAfter pop_back:" << endl;
    for (int num : numbers) {
        cout << num << " ";
    }
    cout << endl;

    // 🔹 7. Initialize vector with size
    vector<int> scores(3);  // 3 elements initialized to 0

    scores[0] = 85;
    scores[1] = 90;
    scores[2] = 95;

    cout << "\nScores vector:" << endl;
    for (int i = 0; i < scores.size(); i++) {
        cout << "scores[" << i << "] = " << scores[i] << endl;
    }

    // 🔹 8. Resize vector
    scores.resize(5);  // expands to size 5 (new values = 0)

    cout << "\nAfter resizing to 5:" << endl;
    for (int num : scores) {
        cout << num << " ";
    }
    cout << endl;

    // 🔹 9. Clear vector
    scores.clear();

    cout << "\nAfter clear, size = " << scores.size() << endl;

    cout << "Press Enter to exit...";
    cin.get();

    return 0;
}