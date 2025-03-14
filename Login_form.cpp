#include<iostream>
#include<fstream>

using namespace std;

class temp{
     string userName,userPass,userEmail;
     string searchName,searchPass,searchEmail;
     fstream file;

     public:
         void login();
         void signUp();
         void forget_pass(); 
}obj;

int main(){
     char choice;
    
     cout<<"1.Login"<<endl;
     cout<<"2.Sign-Up"<<endl;
     cout<<"3.Forget password"<<endl;
     cout<<"4.Exit"<<endl;

     cout<<"Enter your choice:"<<endl;
     cin>>choice;
    
     switch (choice)
     {
     case '1':
        cin.ignore();
        obj.login();
        break;
        case '2':
        cin.ignore();
        obj.signUp();
        break;
        case '3':
        cin.ignore();
        obj.forget_pass();
        break;
        case '4':
        return 0;
        break;
     
     default:
     cout<<"Invalid Choice";
        break;
     }
    

}
void temp::signUp() {
    cout << "\n********** SIGN-UP **********\n";
    cout << "Enter your username: ";
    cin.ignore();
    getline(cin, userName);
    cout << "Enter your email: ";
    getline(cin, userEmail);
    cout << "Enter your password: ";
    getline(cin, userPass);

    // Open file in append mode
    file.open("login_info.txt", ios::out | ios::app);
    if (!file) {
        cout << "\n❌ Error: Unable to access the database.\n";
        return;
    }

    file << userName << "*" << userEmail << "*" << userPass << endl;
    file.close();

    cout << "\n✅ Sign-Up Successful! You can now log in.\n";
}

void temp::login() {
    cout << "\n********** LOGIN **********\n";
    cout << "Enter your username: ";
    cin.ignore();
    getline(cin, searchName);
    cout << "Enter your password: ";
    getline(cin, searchPass);

    file.open("login_info.txt", ios::in);
    if (!file) {
        cout << "\n❌ Error: No user data found. Please sign up first.\n";
        return;
    }

    bool found = false;
    while (getline(file, userName, '*')) {
        getline(file, userEmail, '*');
        getline(file, userPass, '\n');

        if (userName == searchName && userPass == searchPass) {
            found = true;
            cout << "\n✅ Login Successful!";
            cout << "\nUsername: " << userName;
            cout << "\nEmail: " << userEmail << endl;
            break; // Stop searching once found
        }
    }

    file.close();

    if (!found) {
        cout << "\n❌ Incorrect Username or Password. Try again!\n";
    }
}



void temp::forget_pass() {
    cout << "\n********** FORGOT PASSWORD **********\n";
    cout << "Enter your username: ";
    cin.ignore();
    getline(cin, searchName);
    cout << "Enter your email: ";
    getline(cin, searchEmail);

    file.open("login_info.txt", ios::in);
    if (!file) {
        cout << "\n❌ Error: No user data found. Please sign up first.\n";
        return;
    }

    bool found = false;
    while (getline(file, userName, '*')) {
        getline(file, userEmail, '*');
        getline(file, userPass, '\n');

        if (userName == searchName && userEmail == searchEmail) {
            cout << "\n✅ Account Found!";
            cout << "\nYour Password: " << userPass << endl;
            found = true;
            break; // Stop searching once found
        }
    }

    file.close();

    if (!found) {
        cout << "\n❌ No matching account found. Please check your details.\n";
    }
}
