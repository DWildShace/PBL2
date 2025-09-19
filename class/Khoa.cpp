#include "class.h"
using namespace std;


Khoa::Khoa(const string& makhoa,const string& tenkhoa)
{
    this->MaKhoa=makhoa;
    this->TenKhoa=tenkhoa;
}
Khoa::Khoa(const Khoa& k){
    this->MaKhoa=k.MaKhoa;
    this->TenKhoa=k.TenKhoa;
}

void Khoa::setter(const string& makhoa,const string& tenkhoa){
    this->MaKhoa=makhoa;
    this->TenKhoa=tenkhoa;
}

Khoa Khoa::getter(){
    return (*this);
}