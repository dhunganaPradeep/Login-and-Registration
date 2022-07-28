#include <fstream>
#include <ctime>
#include <regex>
#include <vector>
#include <sstream>
#include <stdlib.h>
#include <conio.h>

#include "userInterface.h" // userInterface.h is the header file for the register-login.cpp file

UserInterface box;
class Users
{
  string name, email, username, password;

public:
  Users() {}
  Users(string n, string em, string un, string pw)
  {
    name = n;
    email = em;
    username = un;
    password = pw;
  }

  void registerAcc();
  string generatePassword();

  void fileHandling(string choice); //string choice is the choice of the user
  void displayInfo();

  void login();
  void menu();
};

// Register New Users
void Users::registerAcc()
{
  getchar();
  system("CLS");
  box.borderBox("Register Account", 20, 2, true);
  cout << endl
       << endl
       << "Please fill out the following information to register!";

  cout << endl
       << "Enter name: " << endl;
  getline(cin, name); //cin is the input stream and name is the variable that stores the name of the user
  // Validate name
  while (!regex_match(name, regex("([A-Za-z]+)(\\s[A-Za-z]+){1,3}")))
  {
    cout << endl
         << endl
         << "Please enter a valid name!";
    getline(cin, name); // Re-enter name
  }

  cout << endl
       << "Enter email: " << endl;
  cin >> email;
  // Validate Email
  while (!regex_match(email, regex("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+")))
  {
    cout << endl
         << "Please enter a valid email! " << endl;
    cin >> email;
  }

  // Check username dublication
  cout << endl
       << "Enter username: " << endl;
  cin >> username;
  while (!regex_match(username, regex("([A-Za-z0-9_]+){3,}")))
  {
    cout << endl
         << "Please enter upto 3 characters and use only letters, digits and underscore(_)!" << endl;
    cin >> username;
  }
  // validate password
  cout << endl
       << "Enter password(or press 1 to autogenerate!): " << endl;
  cin >> password;
  if (password == "1")
  {
    password = generatePassword();
  }
  else
  {
    // Check password (minimum 6 characters)
    while (!regex_match(password, regex("(\\w+){6,}")))
    {
      cout << endl
           << "Please enter minimum of 6 characters!" << endl;
      cin >> password;
    }
  }

  fileHandling("register"); // Write to file
}

// Generate Random Password if user requires
string Users::generatePassword()
{
  string alphaNum = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$%^&*()-_+=";
  srand(time(0)); // Seed random number generator //time(0) is the current time
  for (int i = 0; i < 10; i++)
  {
    password += alphaNum[rand() % alphaNum.size()];
  }
  return password;
}

// Insert data to file
void Users::fileHandling(string choice)
{ 
  int id = 1, i = 0, j = 0, flag = 0; 
  fstream file("UserData.dat", ios::in | ios::out | ios::app); // ios::in is for reading, ios::out is for writing, ios::app is for appending
  if (file)
  {

    // Getting File data
    string data;
    vector<string> results; //vector is a dynamic array
    while (getline(file, data))
    {
      stringstream ss(data); //split the data into individual strings
      string str;
      while (getline(ss, str, ';')) 
      {
        results.push_back(str); //to add new elements to the end of the vector
      }
    }
    results.shrink_to_fit();

    // get id
    i = 0;
    for (auto word : results) 
    {
      if (i % 5 == 0) 
      {
        id++;
      }
      i++;
    }

    // Registering
    if (choice == "register")
    {
      file.clear(); //clear the file
      file.seekp(0, ios::end); 
      for (i = 0; i < results.size(); i++)
      {
        if (i == 3 || i == j + 5) 
        {
          j = i;
          if (username == results.at(i))
          {
            flag = 1;
            break;
          }
        }
      }

      // if user does not exist, add new user to file
      if (!flag)
      {
        file << id << ";" << name << ";" << email << ";" << username << ";" << password << ";" << endl;
        system("CLS");
        cout << endl
             << "Account Registration Completed!";
        displayInfo();
      }
      else
      {
        cout << endl
             << endl
             << "Sorry username already exists!" << endl;
        cout << endl
             << endl;
        system("PAUSE"); // pauses the program execution until a key is pressed.
        menu();
      }
    }

    // Logging In
    if (choice == "login")
    {
      for (i = 0; i < results.size(); i++)
      { // Check if username and password is correct
        if (i == 3 || i == j + 5)
        {
          j = i;
          if (username == results.at(i))
          {
            flag = 0;
            if (password == results.at(i + 1))
            {
              system("CLS");
              cout << endl
                   << "Authenticated!" << endl;
              cout << endl
                   << "Welcome " << username << "!";
              name = results.at(i - 2);
              email = results.at(i - 1);
              displayInfo();
            }
            else
            {
              cout << endl
                   << endl
                   << "Sorry Username or Password is incorrect!" << endl;
              cout << endl
                   << endl;
              system("PAUSE");
              menu();
            }
          }
          else
          {
            flag = 1; // if user does not exist
          }
        }
      }
      if (flag == 1)
      {
        cout << endl
             << endl
             << "Your username didn't match! Register Instead!" << endl;
        cout << endl
             << endl;
        system("PAUSE");
        menu();
      }
    }
  }
  else
  {
    cout << endl
         << endl
         << "Failed to open file!";
  }
  file.close();
}

// Display Users Information
void Users::displayInfo()
{
  box.borderBox("User Info", 20, 2, true);
  cout << "Name     : " << name << endl
       << "Email    : " << email << endl
       << "Username : " << username << endl
       << "Password : " << password << endl;

  cout << endl
       << endl;
  system("PAUSE");
  menu();
}

// Login to existing accounts
void Users::login()
{
  system("CLS");
  box.borderBox("Hello Again!", 20, 2, true);
  cout << endl
       << "Username : ";
  cin >> username;
  cout << endl
       << "Password : ";
  cin >> password;
  cout << endl
       << "Authenticating...";
  fileHandling("login"); // Login to file
}

void Users::menu()
{
  int choice;

  system("CLS");
  while (1)
  {
    box.borderBox("Login And Registration System by Pradip Dhungana", 20, 3);
    cout << endl
         << endl
         << "What do you want to do ?" << endl
         << endl
         << endl
         << "1. Register" << endl
         << endl
         << "2. Login" << endl
         << endl
         << "3. Exit" << endl
         << endl;
    cin >> choice;

    switch (choice)
    {
    case 1:
      registerAcc();
      break;
    case 2:
      login();
      break;
    case 3:
      exit(0);
    default:
      cout << endl
           << endl
           << "Please enter the correct option!";
    }
  }
}

int main()
{
  system("CLS");
  Users User;
  system("COLOR 9");
  User.menu(); // Call menu function
}