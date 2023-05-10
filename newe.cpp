#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <openssllib/include/openssl/evp.h>

using namespace std;

// function to encrypt data
void encrypt(const char *key, const unsigned char *plaintext, const size_t plaintext_len, unsigned char *ciphertext, size_t &ciphertext_len) {
    EVP_CIPHER_CTX *ctx;

    int len;

    // create and initialize the context
    if (!(ctx = EVP_CIPHER_CTX_new()))
        cout << "Error creating context\n";

    // initialize the encryption operation
    if (1 != EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, (unsigned char*)key, (unsigned char*)"0123456789012345"))
        cout << "Error initializing encryption\n";

    // encrypt the plaintext
    if (1 != EVP_EncryptUpdate(ctx, ciphertext, (int*)&len, plaintext, plaintext_len))
        cout << "Error encrypting data\n";
    ciphertext_len = len;

    // finalize the encryption
    if (1 != EVP_EncryptFinal_ex(ctx, ciphertext + len, (int*)&len))
        cout << "Error finalizing encryption\n";
    ciphertext_len += len;

    // clean up the context
    EVP_CIPHER_CTX_free(ctx);
}

int main() {
    string masterPassword;
    cout << "Create your master password: ";
    cin >> masterPassword;

    string filename = "passwords.bin";

    // get password from user
    string password;
    cout << "Enter password: ";
    cin >> password;

    // convert password to unsigned char array
    unsigned char *plaintext = new unsigned char[password.length() + 1];
    strcpy((char*)plaintext, password.c_str());

    // encrypt the password using the master password as the encryption key
    unsigned char ciphertext[1024];
    size_t ciphertext_len;
    encrypt(masterPassword.c_str(), plaintext, password.length(), ciphertext, ciphertext_len);

    // write the encrypted password to the file
    ofstream file(filename, ios::binary);
    file.write((char*)&ciphertext_len, sizeof(size_t));
    file.write((char*)ciphertext, ciphertext_len);

    // clean up memory
    delete[] plaintext;

    // close the file
    file.close();

    cout << "Password file created and encrypted successfully.\n";

    return 0;
}
