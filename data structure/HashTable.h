#pragma once
#include "MyVector.h"
template <typename T>
class HashTable {
private:
    MyVector<MyVector<T>>  table; // mỗi bucket là 1 vector<T>
    size_t capacity;           // số bucket

    size_t hashFunction(const T& obj) const {
        return obj.getKey() % capacity;
    }

public:
    HashTable(size_t cap = 10) : capacity(cap) {
        table.resize(capacity);
    }

    void insert(const T& obj) {
        size_t index = hashFunction(obj);
        table[index].push_back(obj);
    }

    T* search(int key) {
        size_t index = key % capacity;
        for (auto& obj : table[index]) {
            if (obj.getKey() == key) {
                return &obj; // trả về địa chỉ object
            }
        }
        return nullptr;
    }

    void remove(int key) {
        size_t index = key % capacity;
        auto& bucket = table[index];
        for (auto it = bucket.begin(); it != bucket.end(); it++) {
            if (it->getKey() == key) {
                bucket.erase(it);
                return;
            }
        }
    }

    void print() const {
        for (size_t i = 0; i < capacity; i++) {
            if (!table[i].empty()) {
                cout << "Bucket[" << i << "]: ";
                for (auto& obj : table[i]) {
                    obj.displayInfo();
                    // cout << " | ";
                }
                cout << endl;
            }
        }
    }
};
