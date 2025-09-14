#include "passserver.h"

void Menu();

int main() {
  unsigned long size;
  cout << "Enter preferred hash table capacity: ";
  cin >> size;
  while(cin.fail()) {
    cout << "*****Error: Invalid entry. try again: ";
    cin.clear();
    cin.ignore(256, '\n');
    cin >> size;
    cout << endl;
  }
  PassServer p(size);
  cin.clear();
  cin.ignore(256, '\n');
  if(size <= 1) {
      cout << "prime_below gives: 0\n";
      cout << "set to default capacity\n" << p.vSize(); 
    }
    else if(size > max_prime) {
      cout << "prime_below gives: 0\n";
      cout << "set to default capacity\n" << p.vSize();
    }
    else{
      cout << "prime_below gives: " << p.vSize() << endl;
      cout << "set to capacity\n" << p.vSize();
    }
  char choice;
  char *file = new char[256];
  string username;
  string password;
  string newpass;
  pair<string, string> user;
  
  while(choice != 'x') {
    Menu();
    cin >> choice;
    if(choice == 'l') {
      cout << "Enter password file name to load from: ";
      cin >> file;
      if(!p.load(file)){
        cout << "Error: cannot open file " << file;
      }
    }
    else if(choice == 'a') {
      cout << "Enter username: ";
      cin >> username;
      cout << "Enter password: ";
      password = p.hideInput();
	cout << endl;
      user = pair(username, password);
      if(p.addUser(user)) {
        cout << "User " << username << " added\n";
      }
      else {
        cout << "*****Error: User already exists. Could not add user.";
      }
    }
    else if(choice == 'r') {
      cout << "Enter username: ";
      cin >> username;
      if(p.removeUser(username)){
        cout << "User " << username << " deleted.";
      }
        else {
          cout << "*****Error: User not found. Could not delete user";
        }
    }
    else if(choice == 'c') {
      cout << "Enter username: ";
      cin >> username;
      cout << "Enter password: ";
      password = p.hideInput();
      cout << "\nEnter new password: ";
      newpass = p.hideInput();
      user = pair(username, password);
      if(p.changePassword(user, newpass)) {
        cout << "\nPassword changed for user " << username;
      }
      else {
        cout << "\n*****Error: Could not change user password";
      }
    }
    else if(choice == 'f') {
      cout << "Enter username: ";
      cin >> username;
      if(p.find(username)) {
        cout << "User '" << username << "' found\n";
      }
      else {
        cout << "User '" << username << "' not found\n";
      }
    }
    else if(choice == 'd') {
      p.dump();
    }
    else if(choice == 's') {
      cout << "Size of hashtable: " << p.size();
    }
    else if(choice == 'w') {
      cout << "Enter password file name to write to: ";
      cin >> file;
      if(!p.write_to_file(file)){
        cout << "Error: cannot open file " << file;
      }
    }
    else if(choice == 'x') {
      exit;
    }
    else {
      cout << "*****Error: Invalid entry. Try again.";
    }
    cin.clear();
    cin.ignore(256, '\n');
  }
  delete [] file;
}


void Menu()
{
  cout << "\n\n";
  cout << "l - Load From File" << endl;
  cout << "a - Add User" << endl;
  cout << "r - Remove User" << endl;
  cout << "c - Change User Password" << endl;
  cout << "f - Find User" << endl;
  cout << "d - Dump HashTable" << endl;
  cout << "s - HashTable Size" << endl;
  cout << "w - Write to Password File" << endl;
  cout << "x - Exit program" << endl;
  cout << "\nEnter choice : ";
}
