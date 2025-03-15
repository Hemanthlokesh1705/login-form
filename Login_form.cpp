#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class UserAuth {
private:
    string userName, userEmail, userPass;
    string searchName, searchEmail, newPassword;
    fstream file;

public:
    void signUp();
    bool login();
    void forgetPass();
};

// Function to register a new user
void UserAuth::signUp() {
    cout << "\n********** SIGN-UP **********\n";
    cout << "Enter Username: ";
    cin.ignore();
    getline(cin, userName);
    cout << "Enter Email: ";
    getline(cin, userEmail);
    cout << "Enter Password: ";
    getline(cin, userPass);

    file.open("login_info.txt", ios::out | ios::app);
    if (!file) {
        cout << "\n❌ Error: Unable to access the database.\n";
        return;
    }

    file << userName << "*" << userEmail << "*" << userPass << endl;
    file.close();

    cout << "\n✅ Sign-Up Successful! You can now log in.\n";
}

// Function to log in
bool UserAuth::login() {
    cout << "\n********** LOGIN **********\n";
    cout << "Enter Username: ";
    cin.ignore();
    getline(cin, searchName);
    cout << "Enter Password: ";
    getline(cin, userPass);

    file.open("login_info.txt", ios::in);
    if (!file) {
        cout << "\n❌ Error: No user data found. Please sign up first.\n";
        return false;
    }

    bool found = false;
    while (getline(file, userName, '*')) {
        getline(file, userEmail, '*');
        getline(file, userPass, '\n');

        if (userName == searchName) {
            if (userPass == userPass) {
                found = true;
                cout << "\n✅ Login Successful!";
                cout << "\nUsername: " << userName;
                cout << "\nEmail: " << userEmail << endl;
                break;
            } else {
                cout << "\n❌ Incorrect Password!\n";
                file.close();
                return false;
            }
        }
    }

    file.close();
    if (!found) {
        cout << "\n❌ Username not found!\n";
    }
    return found;
}

// Function to reset password
void UserAuth::forgetPass() {
    cout << "\n********** RESET PASSWORD **********\n";
    cout << "Enter Username: ";
    cin.ignore();
    getline(cin, searchName);
    cout << "Enter Email: ";
    getline(cin, searchEmail);

    file.open("login_info.txt", ios::in);
    if (!file) {
        cout << "\n❌ Error: No user data found. Please sign up first.\n";
        return;
    }

    bool found = false;
    string tempData = "";
    while (getline(file, userName, '*')) {
        getline(file, userEmail, '*');
        getline(file, userPass, '\n');

        if (userName == searchName && userEmail == searchEmail) {
            found = true;
            cout << "\n✅ Account Found! Enter New Password: ";
            getline(cin, newPassword);
            tempData += userName + "*" + userEmail + "*" + newPassword + "\n";
        } else {
            tempData += userName + "*" + userEmail + "*" + userPass + "\n";
        }
    }

    file.close();

    if (!found) {
        cout << "\n❌ No matching account found. Please check your details.\n";
        return;
    }

    // Update file with new password
    file.open("login_info.txt", ios::out);
    file << tempData;
    file.close();

    cout << "\n✅ Password Updated Successfully! You can now log in with your new password.\n";
}

// Main function with iterative menu
int main() {
    UserAuth obj;
    char choice;

    while (true) {
        cout << "\n========== MENU ==========\n";
        cout << "1. Sign-Up\n";
        cout << "2. Login\n";
        cout << "3. Forget Password\n";
        cout << "4. Exit\n";
        cout << "Enter Your Choice: ";
        cin >> choice;

        switch (choice) {
            case '1':
                obj.signUp();
                break;
            case '2':
                obj.login();
                break;
            case '3':
                obj.forgetPass();
                break;
            case '4':
                cout << "\n👋 Exiting Program. Goodbye!\n";
                return 0;
            default:
                cout << "\n❌ Invalid Choice! Please try again.\n";
        }
    }
} 
