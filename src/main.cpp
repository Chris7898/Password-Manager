#include <iostream>
#include <fstream>
#include "Variables.h"

using namespace std;

int main() {
  string fileName = "passwords.txt";
  ofstream outFile;
  ifstream inFile;
  string password;
  string readPassword;

  // open the output file stream for writing
  outFile.open(fileName, ios::out | ios::app);

  // write data to the file
  std::cin << password;
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
