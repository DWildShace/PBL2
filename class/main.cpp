#include "class.h"

using namespace std;

int main(){
    SinhVien sv1("102240393","NGUYEN","VAN SON",NULL);

    SinhVien sv2=sv1.getter();

    cout<<sv1.maSoSinhVien<<","<<sv1.Ho<<" "<<sv1.Ten<<","<<sv1.KhoaPtr<<endl;
}