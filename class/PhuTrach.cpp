#include "class.h"
using namespace std;

PhuTrach::PhuTrach( GiaoVien* gv, MonHoc* mh)
{
    this->GiaoVienPtr=gv;
    this->MonHocPtr=mh;
}
PhuTrach::PhuTrach(const PhuTrach& pt)
{
    *this=pt;
}

PhuTrach PhuTrach:: getter()
{
    return *this;
}
void PhuTrach::setter( GiaoVien* gv, MonHoc* mh)
{
    this->GiaoVienPtr=gv;
    this->MonHocPtr=mh;
}