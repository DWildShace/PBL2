#include<string>
#include<vector>

using namespace std;


class Khoa {
private:
    string maKhoa;
    string tenKhoa;
public:
    // getter, setter, constructor
};

class MonHoc {
private:
    string maMonHoc;
    string tenMonHoc;
    int soTC;
    string congThucTinhDiem;
public:
    // getter, setter, constructor
};

class GiaoVien {
private:
    string maGiaoVien;
    string ho;
    string ten;
    Khoa* khoa; // FK: mỗi GV thuộc 1 khoa
public:
    // getter, setter, constructor
};

class SinhVien {
private:
    string maSoSinhVien;
    string ho;
    string ten;
    Khoa* khoa; // FK: mỗi SV thuộc 1 khoa
public:
    // getter, setter, constructor
};

class LopHocPhan {
private:
    string maLopHocPhan;
    MonHoc* monHoc;       // FK
    GiaoVien* giaoVien;   // FK
    vector<SinhVien*> danhSachSV; // nhiều SV đăng ký
public:
    // methods: themSV, xoaSV, inDanhSach
};

class DangKy {
private:
    SinhVien* sinhVien;     
    LopHocPhan* lopHocPhan; 
    float GK; 
    float TP;
    float CK;
public:
    float tinhDiemTongKet(); // có thể implement theo congThucTinhDiem của môn học
};

class PhuTrach {
private:
    GiaoVien* giaoVien;
    MonHoc* monHoc;
public:
    // có thể mở rộng: học kỳ, năm học...
};
