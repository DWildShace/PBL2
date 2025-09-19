#include "class.h"
using namespace std;

GiaoVien::GiaoVien(const string& mgv,const string& ho,const string& ten, Khoa* kp)
{
    this->MaGiaoVien=mgv;
    this->Ho=ho;
    this->Ten=ten;
    this->KhoaPtr=kp;
}

GiaoVien::GiaoVien(const GiaoVien& gv){
    *this=gv;
}

void GiaoVien::setter(const string& mgv,const string& ho,const string& ten, Khoa* kp)
{
    this->MaGiaoVien=mgv;
    this->Ho=ho;
    this->Ten=ten;
    this->KhoaPtr=kp;
}

GiaoVien GiaoVien::getter()
{
    return *this;
}