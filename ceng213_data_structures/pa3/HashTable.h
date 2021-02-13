#ifndef __HASHTABLE__
#define __HASHTABLE__

#include "HashUtils.h"
#include "ItemNotFoundException.h"
/* Do not add new libraries or files */

#define BUCKET_SIZE 2

// Do not modify the public interface of this class.
// Otherwise, your code will note compile!
template <class K, class T>
class HashTable {
    struct Entry {
        K Key;             // the key of the entry
        T Value;   // the value of the entry
        bool Deleted;        // flag indicating whether this entry is deleted
        bool Active;         // flag indicating whether this item is currently used

        Entry() : Key(), Value(), Deleted(false), Active(false) {}
    };

    struct Bucket {
        Entry entries[BUCKET_SIZE];
    };

    int _capacity; // INDICATES THE TOTAL CAPACITY OF THE TABLE
    int _size; // INDICATES THE NUMBER OF ITEMS IN THE TABLE

    Bucket* _table; // THE HASH TABLE

    // == DEFINE HELPER METHODS & VARIABLES BELOW ==


public:
    // TODO: IMPLEMENT THESE FUNCTIONS.
    // CONSTRUCTORS, ASSIGNMENT OPERATOR, AND THE DESTRUCTOR
    HashTable();
    // COPY THE WHOLE CONTENT OF RHS INCLUDING THE KEYS THAT WERE SET AS DELETED
    HashTable(const HashTable<K, T>& rhs);
    HashTable<K, T>& operator=(const HashTable<K, T>& rhs);
    ~HashTable();

    // TODO: IMPLEMENT THIS FUNCTION.
    // INSERT THE ENTRY IN THE HASH TABLE WITH THE GIVEN KEY & VALUE
    // IF THE GIVEN KEY ALREADY EXISTS, THE NEW VALUE OVERWRITES
    // THE ALREADY EXISTING ONE. IF THE LOAD FACTOR OF THE TABLE IS GREATER THAN 0.6,
    // RESIZE THE TABLE WITH THE NEXT PRIME NUMBER.
    void Insert(const K& key, const T& value);

    // TODO: IMPLEMENT THIS FUNCTION.
    // DELETE THE ENTRY WITH THE GIVEN KEY FROM THE TABLE
    // IF THE GIVEN KEY DOES NOT EXIST IN THE TABLE, THROW ItemNotFoundException()
    void Delete(const K& key);

    // TODO: IMPLEMENT THIS FUNCTION.
    // IT SHOULD RETURN THE VALUE THAT CORRESPONDS TO THE GIVEN KEY.
    // IF THE KEY DOES NOT EXIST, THROW ItemNotFoundException()
    T& Get(const K& key) const;

    // TODO: IMPLEMENT THIS FUNCTION.
    // AFTER THIS FUNCTION IS EXECUTED THE TABLE CAPACITY MUST BE
    // EQUAL TO newCapacity AND ALL THE EXISTING ITEMS MUST BE REHASHED
    // ACCORDING TO THIS NEW CAPACITY.
    // WHEN CHANGING THE SIZE, YOU MUST REHASH ALL OF THE ENTRIES
    void Resize(int newCapacity);

    // THE IMPLEMENTATION OF THESE FUNCTIONS ARE GIVEN TO YOU
    // DO NOT MODIFY!
    int Capacity() const; // RETURN THE TOTAL CAPACITY OF THE TABLE
    int Size() const; // RETURN THE NUMBER OF ACTIVE ITEMS
    void getKeys(K* keys); // PUT THE ACTIVE KEYS TO THE GIVEN INPUT PARAMETER
};


template <class K, class T>
HashTable<K, T>::HashTable() {
    _capacity = NextCapacity(0);
    _table = new Bucket[_capacity];
    _size = 0;
}

template <class K, class T>
HashTable<K, T>::HashTable(const HashTable<K, T>& rhs) {
    this->_size = rhs._size;
    this->_capacity = rhs._capacity;
    this->_table = new Bucket[_capacity];
    int buc, ele;
    for (buc = 0; buc < BUCKET_SIZE; buc++){
        for (ele = 0; ele < this->_capacity; ele++){
            _table[ele].entries[buc].Active = rhs._table[ele].entries[buc].Active;
            _table[ele].entries[buc].Deleted = rhs._table[ele].entries[buc].Deleted;
            _table[ele].entries[buc].Key = rhs._table[ele].entries[buc].Key;
            _table[ele].entries[buc].Value = rhs._table[ele].entries[buc].Value;
        }        
    }
}

template <class K, class T>
HashTable<K, T>& HashTable<K, T>::operator=(const HashTable<K, T>& rhs) {
    if(this != &rhs){
        delete[] _table;
        this->_size = rhs._size;
        this->_capacity = rhs._capacity;
        this->_table = new Bucket[_capacity];
        int buc, ele;
        for(buc=0 ; buc<BUCKET_SIZE ; ++buc){
            for(ele=0 ; ele<_capacity ; ++ele){
                _table[ele].entries[buc].Active = rhs._table[ele].entries[buc].Active;
                _table[ele].entries[buc].Deleted = rhs._table[ele].entries[buc].Deleted;
                _table[ele].entries[buc].Key = rhs._table[ele].entries[buc].Key;
                _table[ele].entries[buc].Value = rhs._table[ele].entries[buc].Value;
            }
        }
    }
    HashTable &ptr = *this; //not sure if this is necesarry but i thought it might give warning
    return ptr;
}

template <class K, class T>
HashTable<K, T>::~HashTable() {
    delete[] _table;
}

template <class K, class T>
void HashTable<K, T>::Insert(const K& key, const T& value) {
    int current = Hash(key);
    bool fl = true;
    for(int q = 0; fl; q++){
        int i = (current + q*q) % _capacity;
        for (int j = 0; j < BUCKET_SIZE; j++){
            if(!_table[i].entries[j].Active){
                _size++;
                _table[i].entries[j].Key = key;
                _table[i].entries[j].Value = value;
                _table[i].entries[j].Active = true;
                _table[i].entries[j].Deleted = false;
                fl = false;
                break;
            }
            else if(_table[i].entries[j].Active && _table[i].entries[j].Key == key){
                _table[i].entries[j].Key = key;
                _table[i].entries[j].Value = value;
                _table[i].entries[j].Active = true;
                fl = false;
                break;
            }
        }
    }
    float thr = BUCKET_SIZE*_capacity;
    if( (_size/ thr ) > 0.6){Resize(NextCapacity(_capacity));}
}

template <class K, class T>
void HashTable<K, T>::Delete(const K& key) {
    if(_size == 0){throw ItemNotFoundException();}
    int current = Hash(key);
    bool fl = true;
    for(int q = 0; fl; q++){
        int i = (current + q*q) % _capacity;
        for (int j = 0; j < BUCKET_SIZE; j++){
            if(_table[i].entries[j].Active && _table[i].entries[j].Key == key){
                _table[i].entries[j].Deleted = true;
                _table[i].entries[j].Active = false;
                _size--;
                fl = false;
                break;
            }
            else if(!_table[i].entries[j].Active){throw ItemNotFoundException();   }
        }
    }
}

template <class K, class T>
T& HashTable<K, T>::Get(const K& key) const {
    if(_size == 0 || _capacity == 0){throw ItemNotFoundException();}
    int current = Hash(key),counter = 0;
    bool fl = true;
    for(int q = 0; fl; q++){
        int i = (current + q*q) % _capacity;
        if (_table[i].entries[0].Active && _table[i].entries[0].Key == key){return _table[i].entries[0].Value;}
        else if(_table[i].entries[1].Active && _table[i].entries[1].Key == key){return _table[i].entries[1].Value; }
        if(counter++ > _capacity){throw ItemNotFoundException();}
    }
}

template <class K, class T>
void HashTable<K, T>::Resize(int newCapacity) {
    Bucket* old_table = _table;
    _table = new Bucket[newCapacity];
    int cap = _capacity;
    _size = 0;
    _capacity = newCapacity;
    for(int i=0 ; i<BUCKET_SIZE ; ++i){
        for(int j=0 ; j<cap ; ++j){
            if (old_table[j].entries[i].Active){Insert(old_table[j].entries[i].Key, old_table[j].entries[i].Value);} 
        }
    }
    delete[] old_table;
}

template <class K, class T>
int HashTable<K, T>::Capacity() const {
    return _capacity;
}

template <class K, class T>
int HashTable<K, T>::Size() const {
    return _size;
}

template <class K, class T>
void HashTable<K, T>::getKeys(K* keys) {
    int index = 0;

    for (int i = 0; i < _capacity; i++) {
        Bucket& bucket = _table[i];
        for (int j = 0; j < BUCKET_SIZE; j++) {
            if (bucket.entries[j].Active && !bucket.entries[j].Deleted) {
                keys[index++] = bucket.entries[j].Key;
            }
        }
    }
}

#endif