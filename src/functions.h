#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;


void displayPasswords(vector<string>& passwords) {
    if (passwords.size() == 0) {
        cout << "\nYou have no saved passwords.\n" << endl;
        return;
    }
    cout << "\nHere are your saved passwords:\n" << endl;
    for (int i = 0; i < passwords.size(); i++) {
        cout << passwords[i] << endl;
    }
}