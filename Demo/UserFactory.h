#ifndef USER_FACTORY_H
#define USER_FACTORY_H

#include "Entities.h"
#include "User.h"
#include <iostream>
#include <string>
using namespace std;

class UserFactory {
public:
    // Hàm tạo user theo loại
    static User* createUser(const string& type, const string& id, const string& name, Khoa* khoaPtr = nullptr) {
        if (type == "Student") {
            return new Student(id, name, khoaPtr);
        } else if (type == "Teacher") {
            return new Teacher(id, name, khoaPtr);
        } else if (type == "Admin") {
            // return new Admin(id, name);
            cout << "[Warning] Admin class chưa được kích hoạt!\n";
            return nullptr;
        } else {
            cout << "Unknown user type: " << type << endl;
            return nullptr;
        }
    }
};

#endif // USER_FACTORY_H
