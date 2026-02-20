#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class UserAuth {
private:
    string username;
    string password;

    bool userExists(const string& user) {
        ifstream file("users.txt");
        string u, p;

        while (file >> u >> p) {
            if (u == user) {
                file.close();
                return true;
            }
        }
        file.close();
        return false;
    }

    bool isPasswordValid(const string& pass) {
        return pass.length() >= 6;
    }

public:
void registerUser() {
    string confirmPassword;

    cout << "\n----- REGISTRATION -----\n";
    cout << "Enter username: ";
    cin >> username;

    if (userExists(username)) {
        cout << "Username already exists.\n";
        return;
    }

    while (true) {
        cout << "Enter password (min 6 chars): ";
        cin >> password;

        if (!isPasswordValid(password)) {
            cout << "Password too short. Try again.\n";
            continue;
        }

        cout << "Confirm password: ";
        cin >> confirmPassword;

        if (password != confirmPassword) {
            cout << "Passwords do not match. Try again.\n";
            continue;
        }

        break;
    }

    ofstream file("users.txt", ios::app);
    file << username << " " << password << endl;
    file.close();

    cout << "Registration successful!\n";
}


    void loginUser() {
        cout << "\n----- LOGIN -----\n";
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;

        ifstream file("users.txt");
        string u, p;
        bool success = false;

        while (file >> u >> p) {
            if (u == username && p == password) {
                success = true;
                break;
            }
        }
        file.close();

        if (success)
            cout << "Login successful. Welcome, " << username << "!\n";
        else
            cout << "Invalid username or password.\n";
    }
};

int main() {
    UserAuth auth;
    int choice;

    do {
        cout << "\n==============================\n";
        cout << "   LOGIN & REGISTRATION MENU\n";
        cout << "==============================\n";
        cout << "1. Register\n";
        cout << "2. Login\n";
        cout << "3. Exit\n";
        cout << "Choose an option: ";
        cin >> choice;

        switch (choice) {
            case 1: auth.registerUser(); break;
            case 2: auth.loginUser(); break;
            case 3: cout << "Program exited.\n"; break;
            default: cout << "Invalid choice.\n";
        }
    } while (choice != 3);

    return 0;
}
