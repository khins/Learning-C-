// lesson17_vectors_practice.cpp
#include <iostream>
#include <vector>
using namespace std;

// 🔹 Challenge 2: Find max value
// method that takes a vector of integers and returns the maximum value
// returns the maximum value found in the vector as an integer
int findMax(const vector<int>& nums) {
    int maxVal = nums[0];

    for (int num : nums) {
        if (num > maxVal) {
            maxVal = num;
        }
    }

    return maxVal;
}

// 🔹 Challenge 3: Print vector in reverse
// method that takes a vector of integers and prints them in reverse order
// does not return anything, just prints the values in reverse order to the console
void printReverse(const vector<int>& nums) {
    cout << "Reversed: ";
    for (int i = nums.size() - 1; i >= 0; i--) {
        cout << nums[i] << " ";
    }
    cout << endl;
}

// 🔹 Challenge 4: Remove even numbers
// method that takes a vector of integers and removes all even numbers, leaving only odd numbers
// input parameter is a reference to a vector of integers, modifies the original vector by removing all even numbers, does not return anything
void removeEvens(vector<int>& nums) {
    vector<int> result;

    for (int num : nums) {
        if (num % 2 != 0) {  // keep odd numbers
            result.push_back(num); // method to add elements to the end of the vector, automatically resizes memory as needed
        }
    }

    nums = result;  // overwrite original vector
}

// main method to test the above challenges, calls each method and prints results to console
int main() {
    cout << "===== Challenge 1: User Input Vector =====" << endl;

    int n;
    cout << "Enter number of elements: ";
    cin >> n;

    vector<int> numbers;

    // Input values
    for (int i = 0; i < n; i++) {
        int value;
        cout << "Enter value " << i << ": ";
        cin >> value;
        numbers.push_back(value);
    }

    // Print vector
    cout << "\nYou entered: ";
    for (int num : numbers) {
        cout << num << " ";
    }
    cout << endl;

    // 🔹 Challenge 2: Max value
    if (!numbers.empty()) {
        int maxVal = findMax(numbers);
        cout << "Max value: " << maxVal << endl;
    }

    // 🔹 Challenge 3: Reverse print
    printReverse(numbers);

    // 🔹 Challenge 4: Remove evens
    removeEvens(numbers);

    cout << "After removing even numbers: ";
    for (int num : numbers) {
        cout << num << " ";
    }
    cout << endl;

    cout << "\nPress Enter to exit...";
    cin.ignore();
    cin.get();

    return 0;
}