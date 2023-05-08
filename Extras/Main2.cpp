#include <iostream>
#include <fstream>

using namespace std;

const string FILENAME = "passwords.txt";

// function to check if a file exists
bool fileExists(string fileName) {
  ifstream infile(fileName.c_str());
  return infile.good();
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
    return 0;
  }

  // ask user to enter their master password
  ifstream inFile(FILENAME);
  string storedMasterPassword;
  getline(inFile, storedMasterPassword);
  string enteredMasterPassword;
  cout << "Enter your master password: ";
  cin >> enteredMasterPassword;

  // if the entered master password is incorrect, exit the program
  if (enteredMasterPassword != storedMasterPassword) {
    cout << "\nIncorrect password. Access denied." << endl;
    return 1;
  }

  // if the master password is correct, allow user to access password database
  cout << "\nAccess granted." << endl;

 int main(){

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

  return 0;
}
