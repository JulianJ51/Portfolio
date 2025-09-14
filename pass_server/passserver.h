#include "hashtable.h"
using namespace cop4530;

class PassServer {

    public:
        PassServer(size_t size = 101); //constructor
        ~PassServer(); //destructor
        bool load (const char *filename); //loads password file in HashTable
        bool addUser(pair<string, string> & kv); //add new username and password
        bool addUser(pair<string, string> && kv); //move version
        bool removeUser(const string & k); //delete user with username k
        //change existing users password
        bool changePassword(pair<string, string> & p, const string & newpassword); 
        bool find(const string & user); //checks if user exists
        void dump() const; //show structure of contents of HashTable
        size_t size() const; //return size of HashTable
        bool write_to_file(const char *filename) const; //save username and password combo into file
        string hideInput(); //helper function for EC
        int vSize() const; //return underlying vector size

    private:
        HashTable<string, string> users;

        string encrypt(const string & str); //encrypt parameter str and return
};

