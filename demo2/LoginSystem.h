#ifndef LOGIN_SYSTEM_H
#define LOGIN_SYSTEM_H

#include "HashTable.h"
#include "Account.h"
#include "Khoa.h"
#include "MonHoc.h"
#include "Student.h"
#include "Teacher.h"
#include "LopHocPhan.h"
#include "DangKy.h"
#include "UserFactory.h"
#include <fstream>
#include <sstream>
#include <memory>

class LoginSystem {
private:
    HashTable<Account> accountTable;
    HashTable<Khoa> khoaTable;
    HashTable<MonHoc> monHocTable;
    HashTable<Student> studentTable;
    HashTable<Teacher> teacherTable;
    HashTable<LopHocPhan> lopHPTable;
    HashTable<DangKy> dangKyTable;
    
public:
    LoginSystem() : accountTable(10), khoaTable(5), monHocTable(5), 
                   studentTable(10), teacherTable(5), lopHPTable(10), 
                   dangKyTable(20) {}
    
    // Load Khoa từ file
    bool loadKhoaFromFile(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cout << "Khong the mo file: " << filename << endl;
            return false;
        }
        
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string makhoa, tenkhoa, nam;
            
            if (getline(ss, makhoa, ',') && getline(ss, tenkhoa, ',') && getline(ss, nam)) {
                Khoa newKhoa(makhoa, tenkhoa);
                khoaTable.insert(newKhoa.getKey(),newKhoa);
            }
        }
        file.close();
        cout << "Da tai " << khoaTable.getSize() << " khoa" << endl;
        return true;
    }
    
    // Load MonHoc từ file
    bool loadMonHocFromFile(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cout << "Khong the mo file: " << filename << endl;
            return false;
        }
        
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string mamon, tenmon;
            
            if (getline(ss, mamon, ',') && getline(ss, tenmon)) {
                MonHoc newMonHoc(mamon, tenmon);
                monHocTable.insert(newMonHoc.getKey(),newMonHoc);
            }
        }
        file.close();
        cout << "Da tai " << monHocTable.getSize() << " mon hoc" << endl;
        return true;
    }
    
    // Load Student từ file
    bool loadStudentFromFile(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cout << "Khong the mo file: " << filename << endl;
            return false;
        }
        
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string masv, tensv, makhoa;
            
            if (getline(ss, masv, ',') && getline(ss, tensv, ',') && getline(ss, makhoa)) {
                // Tìm khoa trong bảng khoa
                Khoa* khoaPtr = khoaTable.searchByString(makhoa);
                if (khoaPtr) {
                    Student newStudent(masv, tensv, khoaPtr);
                    studentTable.insert(newStudent.getKey(),newStudent);
                } else {
                    cout << "Khong tim thay khoa " << makhoa << " cho sinh vien " << masv << endl;
                }
            }
        }
        file.close();
        cout << "Da tai " << studentTable.getSize() << " sinh vien" << endl;
        return true;
    }
    
    // Load Teacher từ file
    bool loadTeacherFromFile(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cout << "Khong the mo file: " << filename << endl;
            return false;
        }
        
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string magv, tengv, makhoa;
            
            if (getline(ss, magv, ',') && getline(ss, tengv, ',') && getline(ss, makhoa)) {
                Khoa* khoaPtr = khoaTable.searchByString(makhoa);
                if (khoaPtr) {
                    Teacher newTeacher(magv, tengv, khoaPtr);
                    teacherTable.insert(newTeacher.getKey(),newTeacher);
                } else {
                    cout << "Khong tim thay khoa " << makhoa << " cho giang vien " << magv << endl;
                }
            }
        }
        file.close();
        cout << "Da tai " << teacherTable.getSize() << " giang vien" << endl;
        return true;
    }
    
    // Load LopHocPhan từ file
    bool loadLopHPFromFile(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cout << "Khong the mo file: " << filename << endl;
            return false;
        }
        
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string malophp, magv, mamh;
            
            if (getline(ss, malophp, ',') && getline(ss, magv, ',') && getline(ss, mamh)) {
                
                // Tìm teacher và monhoc trong các bảng
                Teacher* teacherPtr = teacherTable.searchByString(magv);
                MonHoc* monHocPtr = monHocTable.searchByString(mamh);
                
                if (teacherPtr && monHocPtr) {
                    LopHocPhan newLopHP(malophp, teacherPtr, monHocPtr);
                    lopHPTable.insert(newLopHP.getKey(),newLopHP);
                } else {
                    cout << "Khong tim thay giang vien hoac mon hoc cho lop HP " << malophp << endl;
                    if (!teacherPtr) cout << "  - Khong tim thay giang vien: " << magv << endl;
                    if (!monHocPtr) cout << "  - Khong tim thay mon hoc: " << mamh << endl;
                }
            }
        }
        file.close();
        cout << "Da tai " << lopHPTable.getSize() << " lop hoc phan" << endl;
        return true;
    }
    
    // Load DangKy từ file
    bool loadDangKyFromFile(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cout << "Khong the mo file: " << filename << endl;
            return false;
        }
        
        string line;
        int lineCount = 0;
        while (getline(file, line)) {
            lineCount++;
            stringstream ss(line);
            string malophp, masv, diemStr;
            
            if (getline(ss, malophp, ',') && getline(ss, masv, ',') && getline(ss, diemStr)) {
                try {
                    float diem = stof(diemStr);
                    DangKy newDangKy(malophp, masv, diem);
                    dangKyTable.insert(newDangKy.getKey(), newDangKy);
                    cout << "DEBUG: Da them dang ky " << malophp << "-" << masv << " - Diem: " << diem << endl;
                } catch (const std::exception& e) {
                    cout << "Loi chuyen doi diem cho " << malophp << "-" << masv << " - Line " << lineCount << ": " << e.what() << endl;
                }
            } else {
                cout << "DEBUG: Loi dinh dang dong " << lineCount << ": " << line << endl;
            }
        }
        file.close();
        cout << "Da tai " << dangKyTable.getSize() << " dang ky (tu " << lineCount << " dong)" << endl;
        return true;
    }
    
    // Load accounts từ file
    bool loadAccountsFromFile(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cout << "Khong the mo file: " << filename << endl;
            return false;
        }
        
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string username, password;
            
            if (getline(ss, username, ',') && getline(ss, password)) {
                string userTypeCode = username.substr(0, 2);
                User* user = nullptr;
                
                if (userTypeCode == "SV") {
                    // Tìm sinh viên trong bảng student
                    Student* studentPtr = studentTable.searchByString(username);
                    if (studentPtr) {
                        user = studentPtr;
                    } else {
                        cout << "Khong tim thay sinh vien " << username << endl;
                    }
                } else if (userTypeCode == "GV") {
                    // Tìm giảng viên trong bảng teacher
                    Teacher* teacherPtr = teacherTable.searchByString(username);
                    if (teacherPtr) {
                        user = teacherPtr;
                    } else {
                        cout << "Khong tim thay giang vien " << username << endl;
                    }
                } else if (userTypeCode == "AD") {
                    user = UserFactory::createUser("Admin", username, "Admin " + username);
                }
                
                if (user != nullptr) {
                    Account newAccount(username, password, user);
                    accountTable.insert(newAccount.getKey(),newAccount);
                }
            }
        }
        file.close();
        cout << "Da tai " << accountTable.getSize() << " tai khoan" << endl;
        return true;
    }
    
    // Load tất cả dữ liệu
    bool loadAllData() {
        cout << "=== TAI DU LIEU ===" << endl;
        bool success = true;
        success &= loadKhoaFromFile("Khoa.txt");
        success &= loadMonHocFromFile("MonHoc.txt");
        success &= loadStudentFromFile("SinhVien.txt");
        success &= loadTeacherFromFile("GiangVien.txt");
        success &= loadLopHPFromFile("LopHP.txt");
        success &= loadDangKyFromFile("DangKy.txt");
        success &= loadAccountsFromFile("Account.txt");
        cout << "=== HOAN TAT TAI DU LIEU ===" << endl;
        return success;
    }
    
    // Đăng nhập
    User* login(const string& username, const string& password) {
        Account* account = accountTable.searchByString(username);
        if (account == nullptr) {
            cout << "Tai khoan khong ton tai!" << endl;
            return nullptr;
        }
        
        if (account->getPassword() != password) {
            cout << "Mat khau khong chinh xac!" << endl;
            return nullptr;
        }
        
        cout << "Dang nhap thanh cong!" << endl;
        return account->getUser();
    }
    
    // Các phương thức getter để truy cập dữ liệu
    HashTable<LopHocPhan>& getLopHPTable() { return lopHPTable; }
    HashTable<DangKy>& getDangKyTable() { return dangKyTable; }
    HashTable<Student>& getStudentTable() { return studentTable; }
    HashTable<Teacher>& getTeacherTable() { return teacherTable; }
    HashTable<MonHoc>& getMonHocTable() { return monHocTable; }
    HashTable<Khoa>& getKhoaTable() { return khoaTable; }
};

#endif