#include <iostream>
#include <fstream>
#include "functions.h"

using namespace std;

const string FILENAME = "passwords.txt";

// function to check if a file exists
bool fileExists(string fileName) {
  ifstream infile(fileName.c_str());
  return infile.good();
}

int main() {
  

  return 0;
}
