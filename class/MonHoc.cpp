#include "class.h"
using namespace std;


MonHoc::MonHoc(const string& mamonhoc,const string& tenmonhoc,const int& sotc,const string& congthuctinhdiem)
{
    this->MaMonHoc=mamonhoc;
    this->TenMonHoc=tenmonhoc;
    this->SoTC=sotc;
    this->CongThucTinhDiem=congthuctinhdiem;
}

MonHoc::MonHoc(const MonHoc& mh)
{
    this->MaMonHoc=mh.MaMonHoc;
    this->TenMonHoc=mh.TenMonHoc;
    this->SoTC=mh.SoTC;
    this->CongThucTinhDiem=mh.CongThucTinhDiem;
}
