#include "Entities.h"
#include "Khoa.h"
#include <iostream>
#include <sstream>
#include <iomanip>

using namespace std;

// ==================== STUDENT ====================
Student::Student() : User("", "", nullptr, UserType::STUDENT) {}

Student::Student(string id, string name, Khoa* khoa) 
    : User(id, name, khoa, UserType::STUDENT) {}

void Student::displayInfo() const {
    cout << "Sinh vien - ";
    User::displayInfo();
}

void Student::showMenu() {
    cout << "=== MENU SINH VIEN ===" << endl;
    cout << "1. Xem thong tin ca nhan" << endl;
    cout << "2. Xem lop hoc phan da dang ky" << endl;
    cout << "3. Xem diem cac mon hoc" << endl;
    cout << "4. Dang xuat" << endl;
}

string Student::toString() const {
    return Id + "," + Name + "," + (khoa ? khoa->getMaKhoa() : "NULL");
}

Student::~Student() {}

// ==================== TEACHER ====================
Teacher::Teacher() : User("", "", nullptr, UserType::TEACHER) {}

Teacher::Teacher(string id, string name, Khoa* khoa) 
    : User(id, name, khoa, UserType::TEACHER) {}

void Teacher::displayInfo() const {
    cout << "Giang vien - ";
    User::displayInfo();
}

void Teacher::showMenu() {
    cout << "=== MENU GIANG VIEN ===" << endl;
    cout << "1. Xem thong tin ca nhan" << endl;
    cout << "2. Xem lop hoc phan dang day" << endl;
    cout << "3. Xem va sua diem sinh vien" << endl;
    cout << "4. Dang xuat" << endl;
}

string Teacher::toString() const {
    return Id + "," + Name + "," + (khoa ? khoa->getMaKhoa() : "NULL");
}

Teacher::~Teacher() {}

// ==================== ADMIN ====================
Admin::Admin() : User("", "", nullptr, UserType::ADMIN) {}

void Admin::displayInfo() const {
    cout << "Admin - ";
    User::displayInfo();
}

void Admin::showMenu() {
    cout << "=== MENU ADMIN ===" << endl;
    cout << "1. Quan ly sinh vien" << endl;
    cout << "2. Quan ly giang vien" << endl;
    cout << "3. Quan ly mon hoc" << endl;
    cout << "4. Quan ly lop hoc phan" << endl;
    cout << "5. Quan ly dang ky" << endl;
    cout << "6. Quan ly tai khoan" << endl;
    cout << "7. Dang xuat" << endl;
}

Admin::~Admin() {}

// ==================== MON HOC ====================
MonHoc::MonHoc() : Mamon(""), Tenmon("") {}

void MonHoc::displayInfo() const {
    cout << "Mon hoc: " << Mamon << " - " << Tenmon << endl;
}

MonHoc::~MonHoc() {}

// ==================== LOP HOC PHAN ====================
LopHocPhan::LopHocPhan() : Malophp(""), giangvien(nullptr), monhoc(nullptr) {}

LopHocPhan::LopHocPhan(string malophp, Teacher* gv, MonHoc* mh) 
    : Malophp(malophp), giangvien(gv), monhoc(mh) {}

void LopHocPhan::displayInfo() const {
    cout << "Lop HP: " << Malophp;
    if (monhoc) {
        cout << " - Mon: " << monhoc->getTenMon();
    }
    if (giangvien) {
        cout << " - GV: " << giangvien->getName();
    }
    cout << endl;
}

string LopHocPhan::toString() const {
    return Malophp + "," + 
           (monhoc ? monhoc->getMaMon() : "NULL") + "," +
           (giangvien ? giangvien->getKey() : "NULL");
}

LopHocPhan::~LopHocPhan() {}

// ==================== DANG KY ====================
DangKy::DangKy() : MaLHP_fk(""), MaSV_fk(""), Diem(0.0f) {}

DangKy::DangKy(string malhp, string masv, float diem) 
    : MaLHP_fk(malhp), MaSV_fk(masv), Diem(diem) {}

void DangKy::displayInfo() const {
    cout << "Dang ky - LHP: " << MaLHP_fk << " - SV: " << MaSV_fk 
         << " - Diem: " << fixed << setprecision(2) << Diem << endl;
}

DangKy::~DangKy() {}

// ==================== ACCOUNT ====================
Account::Account() : Username(""), Password(""), user(nullptr) {}

Account::Account(string username, string password, User* userPtr) 
    : Username(username), Password(password), user(userPtr) {}

void Account::displayInfo() const {
    cout << "Tai khoan: " << Username;
    if (user) {
        cout << " - User: " << user->getName();
        switch (user->getUserType()) {
            case UserType::STUDENT: cout << " (Sinh vien)"; break;
            case UserType::TEACHER: cout << " (Giang vien)"; break;
            case UserType::ADMIN: cout << " (Admin)"; break;
        }
    }
    cout << endl;
}

string Account::toString() const {
    string userId = user ? user->getId() : "NULL";
    string userType;
    
    if (user) {
        switch (user->getUserType()) {
            case UserType::STUDENT: userType = "STUDENT"; break;
            case UserType::TEACHER: userType = "TEACHER"; break;
            case UserType::ADMIN: userType = "ADMIN"; break;
            default: userType = "UNKNOWN"; break;
        }
    } else {
        userType = "NULL";
    }
    
    return Username + "," + Password + "," + userId + "," + userType;
}

Account::~Account() {}