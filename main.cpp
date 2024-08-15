#include <iostream>
#include <fstream>
#include <vector>
#include <filesystem>
using namespace std;
namespace fs = filesystem;
const string ENCRYPTED_EXTENSION = ".Hashira";

void caesar_cipher(vector<char> &data, int key) {
    for (char &byte: data) {
        byte += key;
    }
}

void process_file(const string &file_path, int key) {
    // open file to read
    ifstream file(file_path, ios::binary);
    if (!file) {
        cerr << "Error opening file!" << std::endl;
        return;
    }

    // read file
    vector<char> data((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    file.close();

    // encrypt or decrypt
    caesar_cipher(data, key);

    string output_file_path;
    if (key > 0) {
        // encrypt
        output_file_path = file_path + ENCRYPTED_EXTENSION;
    } else {
        // decrypt
        output_file_path = file_path.substr(0, file_path.size() - ENCRYPTED_EXTENSION.size());
    }

    ofstream output_file(output_file_path, ios::binary);
    if (!output_file) {
        cerr << "Error opening file for writing!" << endl;
        return;
    }

    // write new data
    output_file.write(data.data(), data.size());
    output_file.close();

    // delet origin file
    fs::remove(file_path);

    cout << "Process completed successfully!" << endl;
}

int main() {
    string file_path;
    int key;
    cout << "Enter the path to the file: ";
    getline(cin, file_path);

    cout << "Enter the key for Caesar Cipher (integer value): ";
    cin >> key;

    if (fs::path(file_path).extension() == ENCRYPTED_EXTENSION) {
        process_file(file_path, -key); // decrypt
    } else {
        process_file(file_path, key); // encrypt
    }

    return 0;
}