#include "passserver.h"

//constructor
PassServer::PassServer(size_t size) {
    users = HashTable<string, string>(size);
}

//destructor
PassServer::~PassServer() {
    users.clear();
}

//load function
bool PassServer::load(const char *filename) {
    ifstream in1;
    string s1;
    string s2;
    in1.open(filename);
    if(!in1) {
        return false;
    }
    while(!in1.eof()) {
        in1 >> s1;
        in1 >> s2;
        pair<string, string> entry (s1, s2);
        addUser(entry);
    }
    in1.close();
    return true;
}

//add user function
bool PassServer::addUser(pair<string, string> & kv) {
    string encrypted = encrypt(kv.second);
    if(users.contains(kv.first)) {
        return false;
    }
    return users.insert(pair<string, string> (kv.first, encrypted));
}

//move version
bool PassServer::addUser(pair<string, string> && kv) {
    string encrypted = encrypt(kv.second);
    if(users.contains(kv.first)) {
        return false;
    }
    return users.insert(pair<string, string> (kv.first, encrypted));
}

//remove user
bool PassServer::removeUser(const string & k) {
    return users.remove(k);
}

//change password
bool PassServer::changePassword(pair<string, string> &p, const string & newpassword) {
    string encryptedOld = encrypt(p.second);
    string encryptedNew = encrypt(newpassword);
    if(users.match(pair<string, string> (p.first, encryptedOld)) == false) {
        return false;
    }
    else if(encryptedOld == encryptedNew) {
        return false;
    }
    else {
        users.remove(p.first);
        users.insert(pair<string, string> (p.first, encryptedNew));
    }
    return true;
}

//find function
bool PassServer::find(const string & user){
    if(users.contains(user)) {
        return true;
    }
    else {
        return false;
    }
}

//dump function
void PassServer::dump() const {
    users.dump();
}

//returns size of hashtable
size_t PassServer::size() const {
    return users.size();
}

//write to file function
bool PassServer::write_to_file(const char* filename) const {
    return users.write_to_file(filename);
}

//helper function to hide user input when entering password
string PassServer::hideInput() {
    string s;
    termios oldt;
    tcgetattr(STDIN_FILENO, &oldt);
    termios newt = oldt;
    newt.c_lflag &= ~ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    cin >> s;
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

    return s;
}

int PassServer::vSize() const {
    return users.vSize();
}

//encrypt function
string PassServer::encrypt(const string & str) {
    char salt[] = "$1$########";
    int length = str.size();
    char password[length + 1];
    strcpy(password, str.c_str());
    string encrypted = crypt(password, salt);
    return (encrypted.substr(12));
}