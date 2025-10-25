#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "MyVector.h"

using namespace std;

// Template class for HashEntry
template<typename T>
class HashEntry {
public:
    string key;
    T value;
    HashEntry* next;

    HashEntry(const string& k, const T& v) : key(k), value(v), next(nullptr) {}
};

// Template class for HashTable
template<typename T>
class HashTable {
private:
    HashEntry<T>** table;
    int capacity;
    int size;

    // Hash function
    int hashFunction(const string& key) {
        int hash = 0;
        for (char c : key) {
            hash = (hash * 31 + c) % capacity;
        }
        return hash;
    }

public:
    // Constructor
    HashTable(int cap = 100) : capacity(cap), size(0) {
        table = new HashEntry<T>*[capacity]();
    }

    // Destructor
    ~HashTable() {
        for (int i = 0; i < capacity; i++) {
            HashEntry<T>* entry = table[i];
            while (entry != nullptr) {
                HashEntry<T>* prev = entry;
                entry = entry->next;
                delete prev;
            }
        }
        delete[] table;
    }

    // Insert method
    bool insert(const string& key, const T& value) {
        int index = hashFunction(key);
        HashEntry<T>* entry = table[index];
        
        // Check if key already exists
        while (entry != nullptr) {
            if (entry->key == key) {
                entry->value = value; // Update existing value
                return true;
            }
            entry = entry->next;
        }

        // Insert new entry
        HashEntry<T>* newEntry = new HashEntry<T>(key, value);
        newEntry->next = table[index];
        table[index] = newEntry;
        size++;
        return true;
    }

    // Search method
    T* searchByString(const string& key) {
        int index = hashFunction(key);
        HashEntry<T>* entry = table[index];
        
        while (entry != nullptr) {
            if (entry->key == key) {
                return &(entry->value);
            }
            entry = entry->next;
        }
        return nullptr;
    }

    // Remove method
    bool remove(const string& key) {
        int index = hashFunction(key);
        HashEntry<T>* entry = table[index];
        HashEntry<T>* prev = nullptr;
        
        while (entry != nullptr) {
            if (entry->key == key) {
                if (prev == nullptr) {
                    table[index] = entry->next;
                } else {
                    prev->next = entry->next;
                }
                delete entry;
                size--;
                return true;
            }
            prev = entry;
            entry = entry->next;
        }
        return false;
    }

    // Get all elements
    MyVector<T> getAllElements() {
        MyVector<T> result;
        for (int i = 0; i < capacity; i++) {
            HashEntry<T>* entry = table[i];
            while (entry != nullptr) {
                result.push_back(entry->value);
                entry = entry->next;
            }
        }
        return result;
    }

    // Get all keys
    MyVector<string> getAllKeys() {
        MyVector<string> result;
        for (int i = 0; i < capacity; i++) {
            HashEntry<T>* entry = table[i];
            while (entry != nullptr) {
                result.push_back(entry->key);
                entry = entry->next;
            }
        }
        return result;
    }

    // Get size
    int getSize() const {
        return size;
    }

    // Get capacity
    int getCapacity() const {
        return capacity;
    }

    // Check if empty
    bool isEmpty() const {
        return size == 0;
    }

    // Display table (for debugging)
    void display() {
        for (int i = 0; i < capacity; i++) {
            cout << "Bucket " << i << ": ";
            HashEntry<T>* entry = table[i];
            while (entry != nullptr) {
                cout << "[" << entry->key << ": " << entry->value.toString() << "] -> ";
                entry = entry->next;
            }
            cout << "nullptr" << endl;
        }
    }

    // Save to file method
    bool saveToFile(const string& filename) {
        ofstream file(filename);
        if (!file.is_open()) {
            cerr << "Khong the mo file: " << filename << endl;
            return false;
        }

        try {
            // Duyệt qua tất cả các bucket
            for (int i = 0; i < capacity; i++) {
                HashEntry<T>* current = table[i];
                while (current != nullptr) {
                    // Gọi phương thức toString() của đối tượng
                    file << current->value.toString() << endl;
                    current = current->next;
                }
            }

            file.close();
            cout << "Da luu " << size << " ban ghi vao " << filename << " thanh cong!" << endl;
            return true;
        } catch (const exception& e) {
            cerr << "Loi khi ghi file " << filename << ": " << e.what() << endl;
            file.close();
            return false;
        }
    }

    // Load from file method (optional - cần biết cách parse từng dòng)
    bool loadFromFile(const string& filename, T (*parser)(const string&)) {
        ifstream file(filename);
        if (!file.is_open()) {
            cerr << "Khong the mo file: " << filename << endl;
            return false;
        }

        try {
            string line;
            int count = 0;
            
            while (getline(file, line)) {
                if (!line.empty()) {
                    T obj = parser(line);
                    // Giả sử mỗi đối tượng T có phương thức getKey()
                    insert(obj.getKey(), obj);
                    count++;
                }
            }

            file.close();
            cout << "Da tai " << count << " ban ghi tu " << filename << " thanh cong!" << endl;
            return true;
        } catch (const exception& e) {
            cerr << "Loi khi doc file " << filename << ": " << e.what() << endl;
            file.close();
            return false;
        }
    }

    // Clear all elements
    void clear() {
        for (int i = 0; i < capacity; i++) {
            HashEntry<T>* entry = table[i];
            while (entry != nullptr) {
                HashEntry<T>* temp = entry;
                entry = entry->next;
                delete temp;
            }
            table[i] = nullptr;
        }
        size = 0;
    }

    // Check if key exists
    bool contains(const string& key) {
        return searchByString(key) != nullptr;
    }

    // Update value
    bool update(const string& key, const T& value) {
        T* existing = searchByString(key);
        if (existing != nullptr) {
            *existing = value;
            return true;
        }
        return false;
    }
};

#endif // HASHTABLE_H