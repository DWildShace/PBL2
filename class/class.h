#include<string>
#include<vector>
#include<iostream>
using namespace std;


class Khoa {
    private:
        string MaKhoa;
        string TenKhoa;
    public:
        // getter, setter, constructor
        Khoa(const string&,const string&);
        Khoa(const Khoa&);
        ~Khoa();

        void setter(const string&,const string&);
        Khoa getter();

        

};

class MonHoc {
    private:
        string MaMonHoc;
        string TenMonHoc;
        int SoTC;
        string CongThucTinhDiem;
        // getter, setter, constructor

    public:
        MonHoc(const string&,const string&,const int&,const string&);
        MonHoc(const MonHoc&);
        ~MonHoc();

        MonHoc getter();
        void setter(const string&,const string&,const int&,const string&);
};


class GiaoVien {
    private:
        string MaGiaoVien;
        string Ho;
        string Ten;
        Khoa* KhoaPtr; // FK: mỗi GV thuộc 1 khoa
    public:
        // getter, setter, constructor
        GiaoVien(const string&,const string&,const string&,Khoa*);
        GiaoVien(const GiaoVien&);
        ~GiaoVien();

        GiaoVien getter();
        void setter(const string&,const string&,const string&,Khoa*);
    };

class SinhVien {
    public:
        string maSoSinhVien;
        string Ho;
        string Ten;
        Khoa* KhoaPtr; // FK: mỗi SV thuộc 1 khoa
    public:
        // getter, setter, constructor
        SinhVien(const string&,const string&,const string&, Khoa*);
        SinhVien(const SinhVien&);

        SinhVien getter();
        void setter(const string&,const string&,const string&, Khoa*);

};

class LopHocPhan {
    private:
        string MaLopHocPhan;
        MonHoc* MonHocPtr;       // FK
        GiaoVien* GiaoVienPtr;   // FK
        string HocKy;
    public:
        // methods: themSV, xoaSV, inDanhSach
        LopHocPhan(const string&, MonHoc*, GiaoVien*,const string&);
        LopHocPhan(const LopHocPhan&);

        LopHocPhan getter();
        void setter(const string&, MonHoc*, GiaoVien*,const string&);
};

class DangKy {
    private:
        SinhVien* SinhVienPtr;     
        LopHocPhan* LopHocPhanPtr; 
        float GK; 
        float TP;
        float CK;
    public:
        DangKy( SinhVien*, LopHocPhan*,const float&,const float&,const float&);
        DangKy(const DangKy&);

        DangKy getter();
        void setter( SinhVien*, LopHocPhan*,const float&,const float&,const float&);
        float TinhDiemTongKet(); // có thể implement theo CongThucTinhDiem của môn học

};

class PhuTrach {
    private:
        GiaoVien* GiaoVienPtr;
        MonHoc* MonHocPtr;
    public:
        // có thể mở rộng: học kỳ, năm học...
        PhuTrach( GiaoVien*, MonHoc*);
        PhuTrach(const PhuTrach&);

        PhuTrach getter();
        void setter( GiaoVien*, MonHoc*);
};
