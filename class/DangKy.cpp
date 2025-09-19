#include "class.h"
using namespace std;




DangKy::DangKy( SinhVien* sv, LopHocPhan* lhp,const float& gk,const float& tp,const float& ck)
{
    this->SinhVienPtr=sv;
    this->LopHocPhanPtr=lhp;
    this->GK=gk;
    this->TP=tp;
    this->CK=ck;
}
DangKy::DangKy(const DangKy& dk)
{ 
    *this=dk;
}

DangKy DangKy::getter()
{
    return *this;
}
void DangKy::setter( SinhVien* sv, LopHocPhan* lhp,const float& gk,const float& tp,const float& ck)
{
    this->SinhVienPtr=sv;
    this->LopHocPhanPtr=lhp;
    this->GK=gk;
    this->TP=tp;
    this->CK=ck;
}
//float TinhDiemTongKet(); // có thể implement theo CongThucTinhDiem của môn học