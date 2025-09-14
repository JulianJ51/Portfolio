#include "hashtable.h"

using namespace std;
//constructor
template <typename K, typename V>
HashTable<K, V>::HashTable(size_t size) {
  list<pair<K, V>> first;
  hashTable = vector<list<pair<K, V>>> (prime_below(size), list<pair<K, V>>(first));
  current = 0;
}

//destructor
template <typename K, typename V>
HashTable<K, V>::~HashTable() {
  makeEmpty();
}

//checks if key value k is in hash table
template <typename K, typename V>
bool HashTable<K, V>::contains(const K & k) {
  auto & thisList = hashTable[myhash(k)];
  for(typename list<pair<K, V>>::iterator itr = thisList.begin(); itr != thisList.end(); ++itr) {
    if(k == itr -> first) {
      return true;
    }
  }
  return false;
}

//checks if key value pair is in hashtable
template<typename K, typename V>
bool HashTable<K, V>::match(const pair<K, V> & kv) {
  auto & thisList = hashTable[myhash(kv.first)];
  for(typename list<pair<K, V>>::iterator itr = thisList.begin(); itr != thisList.end(); ++itr) {
    if(kv.first == itr -> first && kv.second == itr -> second) {
      return true;
    }
  }
  return false;
}

//insert, returns false if kv matches one already existing
template <typename K, typename V>
bool HashTable<K, V>::insert(const pair<K, V> &kv) {
  auto & thisList = hashTable[myhash(kv.first)];
  for(typename list<pair<K, V>>::iterator itr = thisList.begin(); itr != thisList.end(); ++itr) {
    if(kv.first == itr -> first) {
      if(kv.second == itr -> second) {
        return false;
      }
      else {
        itr -> second = kv.second;
        return true;
      }
    }
  }
  
  thisList.push_back(kv);
  if(++current > hashTable.size()) 
  {
    rehash();
  }
  return true;
}

//move version of insert
template<typename K, typename V>
bool HashTable<K, V>::insert(pair<K, V> && kv) {
  auto & thisList = hashTable[myhash(kv.first)];
  typename list<pair<K, V>>::iterator itr = thisList.begin();
  for(typename list<pair<K, V>>::iterator itr = thisList.begin(); itr != thisList.end(); ++itr) {
    if(kv.first == itr -> first) {
      if(kv.second == itr -> second) {
        return false;
      }
      else {
        itr -> second = kv.second;
        return true;
      }
    }
  }
  
  thisList.push_back(kv);
  if(++current > hashTable.size()) 
  {
    rehash();
  }
  return true;
}

//removes key and corresponding value
template<typename K, typename V>
bool HashTable<K, V>::remove(const K & k) {
  auto & thisList = hashTable[myhash(k)];
  for(typename list<pair<K, V>>::iterator itr = thisList.begin(); itr != thisList.end(); ++itr) {
    if(k == itr -> first) {
      thisList.erase(itr);
      current--;
      return true;
    }
  }
  return false;
}

//clear
template<typename K, typename V>
void HashTable<K, V>::clear() {
  makeEmpty();
}

//loads contents of file into hash table
template<typename K, typename V>
bool HashTable<K, V>::load(const char *filename) {
  ifstream in1;
  in1.open(filename);
  if(!in1) {
    return false;
  }
  K k1;
  V v1;

  while(!in1.eof()) {
    in1 >> k1;
    in1 >> v1;
    pair<K, V> entry (k1, v1);
    insert(entry);
  }
  in1.close();
  return true;
}

//prints all entries in hashtable
template<typename K, typename V>
void HashTable<K, V>::dump() const {
  int j = 0;
  int i = 0;
  for(auto & thisList : hashTable) {
    i = 0;
    cout << "v[" << j << "] ";
    for(auto & x : thisList) {
      if(i > 0) {
        cout << ":";
      }
      cout << x.first << ' ' << x.second;
      i++;
    }
    cout << endl;
    j++;
  }
}

//returns number of elements
template<typename K, typename V>
size_t HashTable<K, V>::size() const {
  return current;
}

//writes all elements to file
template<typename K, typename V>
bool HashTable<K, V>::write_to_file(const char *filename) const {
  ofstream out1;
  out1.open(filename);
  if(!out1) {
    return false;
  }
  for(auto thisList : hashTable) {
    if(!empty(thisList)) {
      for(auto & x : thisList) {
        out1 << x.first << ' ' << x.second << endl;
      }
    }
  }
  return true;
}

template <typename K, typename V>
int HashTable<K, V>::vSize() const {
  return hashTable.size();
}

//clears all elements
template <typename K, typename V>
void HashTable<K, V>::makeEmpty() {
  for(int i = 0; i < hashTable.size(); i++) {
    hashTable[i].clear();
  }
}

//rehash function for when we have too many elements
template <typename K, typename V>
void HashTable<K, V>::rehash() {
  vector<list<pair<K, V>>> oldTable = hashTable;
  hashTable.resize(prime_below(2 * hashTable.size()));
  for(auto & thisList: hashTable) {
    thisList.clear();
  }
  current = 0;
  for(auto & thisList : oldTable) {
    for(auto & x : thisList) {
      insert(move(x));
    }
  }
}

//returns value of where corresponding index is for key
template <typename K, typename V>
size_t HashTable<K, V>::myhash(const K & k) const {
  static hash<K> K_hash;
  return K_hash(k) % hashTable.size();
}



// returns largest prime number <= n or zero if input is too large
// This is likely to be more efficient than prime_above(), because
// it only needs a vector of size n
template <typename K, typename V>
unsigned long HashTable<K, V>::prime_below (unsigned long n)
{
  if (n > max_prime)
    {
      std::cerr << "** input too large for prime_below()\n";
      return 0;
    }
  if (n == max_prime)
    {
      return max_prime;
    }
  if (n <= 1)
    {
		std::cerr << "** input too small \n";
      return 0;
    }

  // now: 2 <= n < max_prime
  std::vector <unsigned long> v (n+1);
  setPrimes(v);
  while (n > 2)
    {
      if (v[n] == 1)
	return n;
      --n;
    }

  return 2;
}

//Sets all prime number indexes to 1. Called by method prime_below(n) 
template <typename K, typename V>
void HashTable<K, V>::setPrimes(std::vector<unsigned long>& vprimes)
{
  int i = 0;
  int j = 0;

  vprimes[0] = 0;
  vprimes[1] = 0;
  int n = vprimes.capacity();

  for (i = 2; i < n; ++i)
    vprimes[i] = 1;

  for( i = 2; i*i < n; ++i)
    {
      if (vprimes[i] == 1)
        for(j = i + i ; j < n; j += i)
          vprimes[j] = 0;
    }
}

