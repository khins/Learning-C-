// lesson17_vectors_stretch.cpp
#include <iostream>
#include <vector>
#include <algorithm> // for sort
using namespace std;

// 🔹 Challenge 1: Sort vector
// method that takes a vector of integers and sorts it in ascending order
// input parameter is a reference to a vector of integers, modifies the original vector by sorting it
void sortVector(vector<int>& nums) {
    sort(nums.begin(), nums.end());
}

// 🔹 Challenge 2: Count occurrences
// method that takes a vector of integers and a target integer, counts how many times the target appears in the vector
// input parameters are a reference to a vector of integers and an integer target, returns the count
int countOccurrences(const vector<int>& nums, int target) {
    int count = 0;

    // loop through vector and count occurrences of target
    for (int num : nums) {
        if (num == target) {
            count++;
        }
    }

    return count;
}

// 🔹 Challenge 3: Remove duplicates
// method that takes a vector of integers and returns a new vector with all duplicate values removed
// input parameter is a reference to a vector of integers, returns a new vector with duplicates removed
vector<int> removeDuplicates(const vector<int>& nums) {
    vector<int> result; // new vector to store unique values

    for (int num : nums) {
        bool found = false;

        for (int existing : result) {
            if (existing == num) {
                found = true;
                break;
            }
        }

        if (!found) {
            result.push_back(num);
        }
    }

    return result;
}

// 🔹 Challenge 4: Compute average
// method that takes a vector of integers and computes the average value
// input parameter is a reference to a vector of integers, returns the average as a double
double computeAverage(const vector<int>& nums) {
    if (nums.empty()) return 0.0;

    int sum = 0;
    for (int num : nums) {
        sum += num;
    }

    return (double)sum / nums.size();
}

// 🔹 Bonus 🔥: Find second largest number
// method that takes a vector of integers and returns the second largest value
// input parameter is a reference to a vector of integers, returns the second largest value as an integer
int secondLargest(const vector<int>& nums) {
    if (nums.size() < 2) return -1;

    int largest = nums[0];
    int second = -1;

    for (int num : nums) {
        if (num > largest) {
            second = largest;
            largest = num;
        } else if (num > second && num != largest) {
            second = num;
        }
    }

    return second;
}

int main() {
    vector<int> numbers;
    int n;

    cout << "===== VECTOR STRETCH CHALLENGES =====" << endl;
    cout << "Enter number of elements: ";
    cin >> n;

    // Input
    for (int i = 0; i < n; i++) {
        int value;
        cout << "Enter value " << i << ": ";
        cin >> value;
        numbers.push_back(value);
    }

    cout << "\nOriginal vector: ";
    for (int num : numbers) cout << num << " ";
    cout << endl;

    // 🔹 1. Sort
    sortVector(numbers);
    cout << "Sorted vector: ";
    for (int num : numbers) cout << num << " ";
    cout << endl;

    // 🔹 2. Count occurrences
    int target;
    cout << "\nEnter number to count: ";
    cin >> target;

    int count = countOccurrences(numbers, target);
    cout << "Occurrences of " << target << ": " << count << endl;

    // 🔹 3. Remove duplicates
    vector<int> uniqueNums = removeDuplicates(numbers);
    cout << "\nWithout duplicates: ";
    for (int num : uniqueNums) cout << num << " ";
    cout << endl;

    // 🔹 4. Average
    double avg = computeAverage(numbers);
    cout << "\nAverage: " << avg << endl;

    // 🔹 Bonus: Second largest
    int second = secondLargest(numbers);
    cout << "Second largest: " << second << endl;

    cout << "\nPress Enter to exit...";
    cin.ignore();
    cin.get();

    return 0;
}