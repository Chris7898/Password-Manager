#include <iostream>
#include "openssllib/include/openssl/aes.h"
#include "openssllib/include/crypto/evp.h"
#include "openssllib/rand.h"
#include <fstream>
#include <cstring>

using namespace std;

const int KEY_SIZE = 256;
const int IV_SIZE = 128;
const int BLOCK_SIZE = 128;

int encryptFile(string inputFile, string outputFile, unsigned char* key, unsigned char* iv) {
    AES_KEY aesKey;
    if (AES_set_encrypt_key(key, KEY_SIZE, &aesKey) < 0) {
        cout << "Could not set encryption key." << endl;
        return -1;
    }

    unsigned char inputBuffer[BLOCK_SIZE];
    unsigned char outputBuffer[BLOCK_SIZE + AES_BLOCK_SIZE];
    int bytesRead = 0;
    int bytesWritten = 0;

    ifstream inFile(inputFile, ios::binary);
    ofstream outFile(outputFile, ios::binary);
    while (inFile.read((char*)inputBuffer, BLOCK_SIZE)) {
        bytesRead = (int)inFile.gcount();
        if (bytesRead < BLOCK_SIZE) {
            memset(inputBuffer + bytesRead, 0, BLOCK_SIZE - bytesRead);
        }

        AES_cbc_encrypt(inputBuffer, outputBuffer, BLOCK_SIZE, &aesKey, iv, AES_ENCRYPT);

        outFile.write((char*)outputBuffer, BLOCK_SIZE + AES_BLOCK_SIZE);
        bytesWritten += BLOCK_SIZE + AES_BLOCK_SIZE;
    }

    inFile.close();
    outFile.close();

    return bytesWritten;
}

int decryptFile(string inputFile, string outputFile, unsigned char* key, unsigned char* iv) {
    AES_KEY aesKey;
    if (AES_set_decrypt_key(key, KEY_SIZE, &aesKey) < 0) {
        cout << "Could not set decryption key." << endl;
        return -1;
    }

    unsigned char inputBuffer[BLOCK_SIZE + AES_BLOCK_SIZE];
    unsigned char outputBuffer[BLOCK_SIZE];
    int bytesRead = 0;
    int bytesWritten = 0;

    ifstream inFile(inputFile, ios::binary);
    ofstream outFile(outputFile, ios::binary);
    while (inFile.read((char*)inputBuffer, BLOCK_SIZE + AES_BLOCK_SIZE)) {
        bytesRead = (int)inFile.gcount();

        AES_cbc_encrypt(inputBuffer, outputBuffer, BLOCK_SIZE, &aesKey, iv, AES_DECRYPT);

        outFile.write((char*)outputBuffer, BLOCK_SIZE - (int)(outputBuffer[BLOCK_SIZE - 1]));
        bytesWritten += BLOCK_SIZE - (int)(outputBuffer[BLOCK_SIZE - 1]);
    }

    inFile.close();
    outFile.close();

    return bytesWritten;
}

int main() {
    unsigned char key[KEY_SIZE / 8];
    unsigned char iv[IV_SIZE / 8];
    unsigned char passwordMasterKey[KEY_SIZE / 8];

    // Get the master key from the user
    cout << "Enter the master password: ";
    string masterPassword;
    getline(cin, masterPassword);
    sha256(masterPassword, passwordMasterKey);

    // Use the master key to generate a random key and IV for encryption
    RAND_bytes(key, KEY_SIZE / 8);
    RAND_bytes(iv, IV_SIZE / 8);

    // Encrypt the password file
    encryptFile("password.txt", "password.enc", key, iv);

    // Save the key and IV to a separate file
    ofstream keyFile("key.bin", ios::binary);
    keyFile.write((char*)key, KEY_SIZE / 8);
    keyFile.write((char*)iv, IV_SIZE / 8);
    keyFile.close();

    // Prompt the user for the master password again
    cout << "Enter the master password again: ";
    string confirmPassword;
    getline(cin, confirmPassword);
    unsigned char confirmPasswordMasterKey[KEY_SIZE / 8];
    sha256(confirmPassword, confirmPasswordMasterKey);

    // Check if the master password is correct
    if (memcmp(passwordMasterKey, confirmPasswordMasterKey, KEY_SIZE / 8) != 0) {
        cout << "Incorrect master password. Exiting." << endl;
        return 1;
    }

    // Read the key and IV from the file
    ifstream keyFileIn("key.bin", ios::binary);
    keyFileIn.read((char*)key, KEY_SIZE / 8);
    keyFileIn.read((char*)iv, IV_SIZE / 8);
    keyFileIn.close();

    // Decrypt the password file
    decryptFile("password.enc", "password.dec", key, iv);

    // Load the passwords into a vector and use the vector to manage passwords
    vector<PasswordEntry> passwords = loadPasswords("password.dec");
    managePasswords(passwords);

    // Encrypt the updated password file and overwrite the old one
    encryptFile("password.dec", "password.enc", key, iv);
    remove("password.dec");

    return 0;
}
