#include "class.h"
using namespace std;



LopHocPhan::LopHocPhan(const string& mlhp,MonHoc* mh, GiaoVien* gv,const string& hocky)
{
    this->MaLopHocPhan=mlhp;
    this->MonHocPtr=mh;
    this->GiaoVienPtr=gv;
    this->HocKy=hocky;
}
LopHocPhan::LopHocPhan(const LopHocPhan& lhp)
{
    *this=lhp;
}

LopHocPhan LopHocPhan::getter()
{
    return *this;
}

void LopHocPhan::setter(const string& mlhp,MonHoc* mh, GiaoVien* gv,const string& hocky)
{
    this->MaLopHocPhan=mlhp;
    this->MonHocPtr=mh;
    this->GiaoVienPtr=gv;
    this->HocKy=hocky;
}