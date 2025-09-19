#include<string>
#include<vector>

using namespace std;


class Khoa {
private:
    string MaKhoa;
    string TenKhoa;
public:
    // getter, setter, constructor

};

class MonHoc {
private:
    string MaMonHoc;
    string tenMonHoc;
    string TenMonHoc;
    int SoTC;
    string CongThucTinhDiem;
    // getter, setter, constructor
    vector<MonHoc> getter();
    vector<MonHoc> getter();
    
    void setter(string maMonHojc);
};
vector<MonHoc> MonHoc::getter(){
    vector<MonHoc> monhoc={*this};
    return monhoc;
}
class GiaoVien {
private:
    string MaGiaoVien;
    string Ho;
    string Ten;
    Khoa* KhoaPtr; // FK: mỗi GV thuộc 1 khoa
public:
    // getter, setter, constructor
};

class SinhVien {
private:
    string maSoSinhVien;
        string Ho;
        string Ten;
        Khoa* KhoaPtr; // FK: mỗi SV thuộc 1 khoa
public:
    // getter, setter, constructor
};

class LopHocPhan {
private:
    string MaLopHocPhan;
    MonHoc* MonHocPtr;       // FK
    GiaoVien* GiaoVienPtr;   // FK
    vector<SinhVien*> DanhSachSV; // nhiều SV đăng ký
public:
    // methods: themSV, xoaSV, inDanhSach
};

class DangKy {
private:
    SinhVien* SinhVienPtr;     
    LopHocPhan* LopHocPhanPtr; 
    float GK; 
    float TP;
    float CK;
public:
    float TinhDiemTongKet(); // có thể implement theo CongThucTinhDiem của môn học
};

class PhuTrach {
private:
    GiaoVien* GiaoVienPtr;
    MonHoc* MonHocPtr;
public:
    // có thể mở rộng: học kỳ, năm học...
};
