#include <iostream>
#include <string>
using namespace std;

/*
This lesson is good for debugging because you can inspect:

firstName and lastName after each cin
fullName after concatenation
fullName.length()
fullName[0] for character indexing
One small thing to observe: cin >> reads one word at a time, so if you type
 a space in a name, it will stop at the first word. That makes a nice setup for a later
  lesson using getline().

*/

int main() {
    string firstName;
    string lastName;

    cout << "Enter your first name: ";
    cin >> firstName;

    cout << "Enter your last name: ";
    cin >> lastName;

    string fullName = firstName + " " + lastName;

    cout << "Full name: " << fullName << endl;
    cout << "Length: " << fullName.length() << endl;
    cout << "First character: " << fullName[0] << endl;
    cout << "Press Enter to exit...";
    cin.ignore(10000, '\n');
    cin.get();

    return 0;
}
