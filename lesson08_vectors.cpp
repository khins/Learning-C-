#include <iostream>
#include <vector>
using namespace std;

/*
The next lesson is lesson08_vectors.cpp, which introduces the vector container from the C++ Standard Library. Vectors are dynamic arrays that can grow in size as needed, making them more flexible than fixed-size arrays.

This is a great next step after arrays because it lets you investigate:

how vector grows with push_back()
how size() works
how to loop through dynamic collections
why vector is often preferred over fixed-size arrays
A few good things to debug while stepping through:

watch scores before and after each push_back()
inspect scores.size()
step through the loop and watch total change each iteration
inspect the average calculation at the end
*/

int main() {
    vector<int> scores = {90, 85, 88};

    scores.push_back(92);
    scores.push_back(95);

    cout << "Vector size: " << scores.size() << endl;
    cout << "Student scores:" << endl;

    int total = 0;

    for (int i = 0; i < scores.size(); i++) {
        cout << "Score " << i + 1 << ": " << scores[i] << endl;
        total += scores[i];
    }

    double average = total / static_cast<double>(scores.size());
    cout << "Average score: " << average << endl;
    cout << "Press Enter to exit...";
    cin.get();

    return 0;
}
