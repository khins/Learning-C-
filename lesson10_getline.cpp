#include <iostream>
#include <string>
using namespace std;

/*
lesson10_getline.cpp is a good next step because it teaches full-line input with getline(), which contrasts nicely with the cin >> behavior you just explored in lesson09_strings.cpp. It gives you good things to inspect in the debugger:

fullName after a full line is read
favoriteQuote including spaces
fullName.length()
the if (!favoriteQuote.empty()) check
*/

int main() {
    string fullName;
    string favoriteQuote;

    cout << "Enter your full name: ";
    getline(cin, fullName);

    cout << "Enter your favorite quote: ";
    getline(cin, favoriteQuote);

    cout << endl;
    cout << "Full name: " << fullName << endl;
    cout << "Favorite quote: " << favoriteQuote << endl;
    cout << "Name length: " << fullName.length() << endl;

    if (!favoriteQuote.empty()) {
        cout << "First character of quote: " << favoriteQuote[0] << endl;
    }

    cout << "Press Enter to exit...";
    cin.get();

    return 0;
}
