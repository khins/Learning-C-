#include <iostream>
#include <vector>
#include <algorithm>  // 🔥 algorithms live here
using namespace std;

// STL (Standard Template Library) to replace loops with built-in algorithms.
// STL algorithms are a powerful set of functions that operate on ranges of elements, such as those defined by iterators. They provide a way to perform common operations like sorting, searching, counting, and modifying collections without writing explicit loops. This leads to cleaner, more efficient, and often faster code.

int main() {
    vector<int> numbers = {5, 2, 9, 1, 5, 6};

    cout << "Original vector: ";
    for (int n : numbers) cout << n << " ";
    cout << endl;

    // 🔹 1. sort
    // Sorts the range [first, last) in ascending order by default
    // Algorithms Replace Loops
    sort(numbers.begin(), numbers.end());

    cout << "\nSorted vector: ";
    for (int n : numbers) cout << n << " ";
    cout << endl;

    // 🔹 2. find
    // Finds the first occurrence of a value in the range [first, last)
    int target = 5;
    auto it = find(numbers.begin(), numbers.end(), target);

    // Check if found
    // distance calculates the index from the iterator
    if (it != numbers.end()) {
        cout << "\nFound " << target << " at index: "
             << distance(numbers.begin(), it) << endl;
    } else {
        cout << "\nValue not found" << endl;
    }

    // 🔹 3. count
    // Counts the number of occurrences of a value in the range [first, last)
    // Returns the count as an integer
    int countVal = count(numbers.begin(), numbers.end(), 5);
    cout << "\nNumber of 5s: " << countVal << endl;

    // 🔹 4. reverse
    // Reverses the order of elements in the range [first, last)
    // Reverses container in place
    reverse(numbers.begin(), numbers.end());

    cout << "\nReversed vector: ";
    for (int n : numbers) cout << n << " ";
    cout << endl;

    // 🔹 5. for_each (lambda)
    // Applies a function to each element in the range [first, last)
    // This is an inline function that modifies each element by multiplying it by 2
    cout << "\nMultiply each value by 2: ";
    for_each(numbers.begin(), numbers.end(), [](int& n) {
        n *= 2;
        cout << n << " ";
    });
    cout << endl;

    // 🔹 6. min / max
    // Finds the minimum and maximum element in the range [first, last)
    auto minVal = *min_element(numbers.begin(), numbers.end());
    auto maxVal = *max_element(numbers.begin(), numbers.end());

    cout << "\nMin value: " << minVal << endl;
    cout << "Max value: " << maxVal << endl;

    // Sort descending challenge: use a custom comparator (lambda)
    sort(numbers.begin(), numbers.end(), [](int a, int b) {
        return a > b;  // Sort in descending order
    });

    cout << "\nSorted in descending order: ";
    for (int n : numbers) cout << n << " ";
    cout << endl;

    // Remove all 5s using the remove-erase idiom
    // remove shifts non-5s to the front and returns new end
    auto newEnd = remove(numbers.begin(), numbers.end(), 5);
    numbers.erase(newEnd, numbers.end());  // Erase the "removed" elements
    cout << "\nVector after removing 5s: ";
    for (int n : numbers) cout << n << " ";
    cout << endl;

    // Find even numbers only
    cout << "\nEven numbers: ";
    for (int n : numbers) {
        if (n % 2 == 0) {
            cout << n << " ";
        }
    }
    cout << endl;

    // Square all values
    cout << "\nSquared values: ";
    for_each(numbers.begin(), numbers.end(), [](int& n) {
        n *= n;
        cout << n << " ";
    });

    cout << "\nPress Enter to exit...";
    cin.ignore();
    cin.get();

    return 0;
}