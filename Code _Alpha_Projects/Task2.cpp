#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class FileEncryptor {
public:
    void run() {
        while (true) {
            int choice = displayMenu();
            handleChoice(choice);
        }
    }

private:
    int displayMenu() {
        int choice;
        cout << "File Encryption/Decryption Program\n";
        cout << "1. Encrypt a file\n";
        cout << "2. Decrypt a file\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        return choice;
    }

    void handleChoice(int choice) {
        string inputFile, outputFile;
        int shift;

        switch (choice) {
            case 1:
                cout << "Enter input file name: ";
                cin >> inputFile;
                cout << "Enter output file name: ";
                cin >> outputFile;
                cout << "Enter shift value: ";
                cin >> shift;
                encryptFile(inputFile, outputFile, shift);
                cout << "File encrypted successfully.\n";
                break;
            case 2:
                cout << "Enter input file name: ";
                cin >> inputFile;
                cout << "Enter output file name: ";
                cin >> outputFile;
                cout << "Enter shift value: ";
                cin >> shift;
                decryptFile(inputFile, outputFile, shift);
                cout << "File decrypted successfully.\n";
                break;
            case 3:
                cout << "Exiting...\n";
                exit(0);
            default:
                cout << "Invalid choice. Please enter 1, 2, or 3.\n";
        }
        cout << endl;  // Add a blank line for better readability
    }

    char encryptChar(char ch, int shift) {
        if (isalpha(ch)) {
            char base = islower(ch) ? 'a' : 'A';
            return (ch - base + shift) % 26 + base;
        }
        return ch;
    }

    char decryptChar(char ch, int shift) {
        if (isalpha(ch)) {
            char base = islower(ch) ? 'a' : 'A';
            return (ch - base - shift + 26) % 26 + base;
        }
        return ch;
    }

    void encryptFile(const string& inputFile, const string& outputFile, int shift) {
        ifstream inFile(inputFile);
        ofstream outFile(outputFile);

        if (!inFile || !outFile) {
            cerr << "Error opening file." << endl;
            return;
        }

        char ch;
        while (inFile.get(ch)) {
            outFile.put(encryptChar(ch, shift));
        }

        inFile.close();
        outFile.close();
    }

    void decryptFile(const string& inputFile, const string& outputFile, int shift) {
        ifstream inFile(inputFile);
        ofstream outFile(outputFile);

        if (!inFile || !outFile) {
            cerr << "Error opening file." << endl;
            return;
        }

        char ch;
        while (inFile.get(ch)) {
            outFile.put(decryptChar(ch, shift));
        }

        inFile.close();
        outFile.close();
    }
};

int main() {
    FileEncryptor fileEncryptor;
    fileEncryptor.run();
    return 0;
}
