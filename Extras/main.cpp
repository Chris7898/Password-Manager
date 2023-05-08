#include <iostream>
#include <fstream>
using namespace std;


int main() {

 string masterPassword = "myMasterPassword";
 string password;
 string readPassword;
 string fileName = "passwords.txt";
 ofstream outFile;
 ifstream inFile;

cout << "Enter your master password: ";
cin >> password;

if (password != masterPassword) {
    cout << "Incorrect password, access denied." << endl;
    return 1; // exit the program
}

cout << "Access granted." << endl;

// allow user to access the password database
  // open the output file stream for writing
  outFile.open(fileName, ios::out | ios::app);

  // write data to the file
  cout <<"Enter the password you would like to store: ";
  cin >> password;
  outFile << password << endl;

  outFile.close();

  // open the input file stream for reading
  inFile.open(fileName, ios::in);

  // read data from the file
  while (inFile >> readPassword) {

    // process the password data
    cout << readPassword << endl;
  }

  // close the input file stream
  inFile.close();

  return 0;
}
