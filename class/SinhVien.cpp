#include "class.h"
using namespace std;


SinhVien::SinhVien(const string& mssv,const string& ho,const string& ten,Khoa* kp)
{
    this->maSoSinhVien=mssv;
    this->Ho=ho;
    this->Ten=ten;
    this->KhoaPtr=kp;
}

SinhVien::SinhVien(const SinhVien& sv){
    *this=sv;
}

void SinhVien::setter(const string& mssv,const string& ho,const string& ten,Khoa* kp)
{
    this->maSoSinhVien=mssv;
    this->Ho=ho;
    this->Ten=ten;
    this->KhoaPtr=kp;
}

SinhVien SinhVien::getter(){
    return *this;
}