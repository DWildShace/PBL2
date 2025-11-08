#include "User.h"
#include <iostream>
#include <string>
using namespace std;

int to_int(string s) {
    int num = 0;
    for (char c : s) {
        if (c < '0' || c > '9') {return -1;} 
        num = num * 10 + (c - '0');
    }
    return num;
}

User::User(){
    Id = "";
    Name = "";
    khoa = nullptr;
    type = UserType::STUDENT;
}

User::User(string id, string name, Khoa* khoaPtr, UserType userType) 
    : Id(id), Name(name), khoa(khoaPtr), type(userType) {}

User::~User() {};

void User::displayInfo() const {
    cout << "ID: " << Id << " - Name: " << Name;
    if (khoa != nullptr) {
        cout << " - Khoa: " << khoa->getTenKhoa();
    }
}