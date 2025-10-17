#ifndef ENTITIES_H
#define ENTITIES_H

#include "User.h"
#include <sstream>
#include <iomanip>

class Teacher;
class MonHoc;

class Student : public User {
    public:
        Student();
        Student(string id, string name, Khoa* khoa);
        void displayInfo() const override;
        void showMenu() override;
        string getKey() const { return Id; }
        string toString() const;
        virtual ~Student();
};

class Teacher : public User {
    public:
        Teacher();
        Teacher(string id, string name, Khoa* khoa);
        void displayInfo() const override;
        void showMenu() override;
        string getKey() const { return Id; }
        string toString() const;
        virtual ~Teacher();
};

class Admin : public User {
    public:
        Admin();
        Admin(string id, string name) : User(id, name, nullptr, UserType::ADMIN) {}
        void displayInfo() const override;
        void showMenu() override;
        string getKey() const { return Id; }
        
        string toString() const {
            return Id + "," + Name + ",ADMIN";
        }
        
        virtual ~Admin();
};

class MonHoc{
    private:
        string Mamon;
        string Tenmon;
    public:
        MonHoc();
        MonHoc(string mamon, string tenmon) : Mamon(mamon), Tenmon(tenmon) {}
        void displayInfo() const;
        string getMaMon() const { return Mamon; }
        string getTenMon() const { return Tenmon; }
        string getKey() const { return Mamon; }
        
        string toString() const {
            return Mamon + "," + Tenmon;
        }
        
        virtual ~MonHoc();
};

class LopHocPhan{
    private:
        string Malophp;
        Teacher* giangvien;
        MonHoc* monhoc;
    public:
        LopHocPhan();
        LopHocPhan(string malophp, Teacher* gv, MonHoc* mh);
        void displayInfo() const;
        string getMaLopHP() const { return Malophp; }
        Teacher* getGiangVien() const { return giangvien; }
        MonHoc* getMonHoc() const { return monhoc; }
        string getKey() const { return Malophp; }
        string toString() const;
        virtual ~LopHocPhan();
};

class DangKy{
    private:
        string MaLHP_fk;
        string MaSV_fk;
        float Diem;
    public:
        DangKy();
        DangKy(string malhp, string masv, float diem);
        string getMaLHP_FK() const { return MaLHP_fk; }
        string getMaSV_FK() const { return MaSV_fk; }
        void setDiem(float diem) { 
            if (diem >= 0.0f && diem <= 10.0f) {
                Diem = diem; 
            }
        }
        float getDiem() const { return Diem; }     
        void displayInfo() const;
        string getKey() const { return MaLHP_fk + "-" + MaSV_fk; }
        
        string toString() const {
            stringstream ss;
            ss << MaLHP_fk << "," << MaSV_fk << "," << fixed << setprecision(2) << Diem;
            return ss.str();
        }
        
        virtual ~DangKy();
};

class Account{
    private:
        string Username;
        string Password;
        User* user;
    public:
        Account();
        Account(string username, string password, User* userPtr = nullptr);
        string getUsername() const { return Username; }
        string getPassword() const { return Password; }
        string getKey() const { return Username; }
        User* getUser() const { return user; }
        void setUser(User* userPtr) { user = userPtr; }
        void displayInfo() const;
        string toString() const;
        virtual ~Account();
};

#endif // ENTITIES_H