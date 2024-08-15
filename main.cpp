#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

void caesar_cipher(vector<char> &data, int key, bool encrypt) {
    for (auto &byte: data) {
        if (encrypt) {
            byte += key; // encrypt bytes
        } else {
            byte -= key; // decrypt bytes
        }
    }
}

void process_file(const string &file_path, int key, bool encrypt) {
    // open file to read
    ifstream file(file_path, ios::binary);
    if (!file) {
        cerr << "Error opening file!" << endl;
        return;
    }

    // read file
    vector<char> data((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    file.close();

    // encrypt or decrypt
    caesar_cipher(data, key, encrypt);

    // open file to write
    ofstream out_file(file_path, ios::binary);
    if (!out_file) {
        cerr << "Error opening file for writing!" << endl;
        return;
    }

    // write new data
    out_file.write(data.data(), data.size());
    out_file.close();

    cout << "Operation completed successfully!" << endl;
}

int main() {
    string file_path;
    int key;
    string choice;

    cout << "Enter the path to the file: ";
    getline(cin, file_path);

    cout << "Enter the key for Caesar Cipher (integer value): ";
    cin >> key;

    cout << "Do you want to (1) encrypt or (2) decrypt the file? Enter 1 or 2: ";
    cin >> choice;

    if (choice == "1") {
        process_file(file_path, key, true);
    } else if (choice == "2") {
        process_file(file_path, key, false);
    } else {
        cerr << "Invalid choice!" << endl;
    }

    return 0;
}
