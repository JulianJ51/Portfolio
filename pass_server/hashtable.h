#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <vector>
#include <list>
#include <iostream>
#include <functional>
#include <fstream>
#include <crypt.h>
#include <cstring>
#include <termios.h>
#include <unistd.h>
using namespace std;

// max_prime is used by the helpful functions provided
// to you.
static const unsigned int max_prime = 1301081;
// the default_capacity is used if the initial capacity 
// of the underlying vector of the hash table is zero. 
static const unsigned int default_capacity = 11;
namespace cop4530 {
    template <typename K, typename V>
    class HashTable {
        public:
            HashTable(size_t size = 101); //constructor
            ~HashTable(); //Destructor
            bool contains(const K & k); //checks if key k is in table
            bool match(const std::pair<K, V> &kv); //checks if key value pair is in table
            bool insert(const std::pair<K, V> &kv); //adds key-value pair to hash table
            bool insert(std::pair<K, V> && kv); //move version
            bool remove(const K & k); //removes key and corresponding value
            void clear(); //deletes all elements in hash table
            bool load(const char *filename); //loads contents of file into hash table
            void dump() const; //displays all entries in hash table
            size_t size() const; //returns size of hash table
            bool write_to_file(const char *filename) const; //write all elements in hash table to file
            int vSize() const; //getter for underlying vector size

        private:
            void makeEmpty(); //deletes all elements in hash table, used by clear
            void rehash(); //rehash function, called when need more space
            size_t myhash(const K &k) const; //return index of vector where k should be stored
            unsigned long prime_below(unsigned long);
            void setPrimes(std::vector<unsigned long>&);

            std::vector<std::list<std::pair<K, V>>> hashTable;
            size_t current;
    };

    #include "hashtable.hpp"
}
#endif
