#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "functions.h"

using namespace std;

const string FILENAME = "passwords.txt";

// function to check if a file exists
bool fileExists(string fileName) {
    ifstream infile(fileName.c_str());
    return infile.good();
}

// function to add a new password
void addPassword(vector<string>& passwords) {
    string newPassword;
    cout << "\nEnter a new password: ";
    cin >> newPassword;
    passwords.push_back(newPassword);
    cout << "\nNew password saved.\n" << endl;
}

// function to delete a password
void deletePassword(vector<string>& passwords) {
    if (passwords.size() == 0) {
        cout << "\nYou have no saved passwords to delete.\n" << endl;
        return;
    }
    int index;
    cout << "\nEnter the index of the password you want to delete: ";
    cin >> index;
    if (index < 1 || index > passwords.size()) {
        cout << "\nInvalid index.\n" << endl;
        return;
    }
    passwords.erase(passwords.begin() + index - 1);
    cout << "\nPassword deleted.\n" << endl;
}

int main() {
    // check if the password file exists
    if (!fileExists(FILENAME)) {
        // if it doesn't, create it and prompt user to set a master password
        ofstream outFile(FILENAME);
        string masterPassword;
        cout << "Welcome to Password Manager!\n" << endl;
        cout << "Please set a master password: ";
        cin >> masterPassword;
        outFile << masterPassword << endl;
        cout << "\nMaster password set. Your password file has been created." << endl;
        outFile.close();
    }

    // ask user to enter their master password
    ifstream inFile(FILENAME);
    string storedMasterPassword;
    getline(inFile, storedMasterPassword);
    string enteredMasterPassword;
    cout << "\nEnter your master password: ";
    cin >> enteredMasterPassword;

    // if the entered master password is incorrect, exit the program
    if (enteredMasterPassword != storedMasterPassword) {
        cout << "\nIncorrect password. Access denied." << endl;
        return 1;
    }

    // if the master password is correct, allow user to access password database
    cout << "\nAccess granted. Welcome to Password Manager!" << endl;

    // load passwords from file into vector
    vector<string> passwords;
    string password;
    while (getline(inFile, password)) {
        passwords.push_back(password);
    }

    // display menu options and process user input
    char choice;
    do {
        cout << "\nWhat would you like to do?" << endl;
        cout << "1. View saved passwords" << endl;
        cout << "2. Add a new password" << endl;
        cout << "3. Delete a password" << endl;
        cout << "4. Exit\n" << endl;
        cin >> choice;

        switch (choice) {
            case '1':
                displayPasswords(passwords);
                break;
            case '2':
                addPassword(passwords);
                break;
            case '3':
                deletePassword(passwords);
                break;
            case '4':
                cout << "\nExiting Password Manager. Goodbye!" << endl;
                break;
            default:
                cout << "\nInvalid choice.\n" << endl;
                break;
        }
    } while (choice != '4');

    // save updated password vector to file
    ofstream outFile(FILENAME);
    outFile << storedMasterPassword << endl;
    for (int i = 0; i < passwords.size(); i++) {
        outFile << passwords[i] << endl;
    }
    outFile.close();

    return 0;
}

