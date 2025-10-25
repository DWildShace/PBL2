#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <limits>
#include "LoginSystem.h"

using namespace std;

void clearScreen() {
    system("cls"); // Windows
    // system("clear"); // Linux/Mac
}

// Hàm kiểm tra input số nguyên hợp lệ
int getValidIntInput(const string& prompt, int minChoice = 1, int maxChoice = 10) {
    int choice;
    while (true) {
        cout << prompt;
        cin >> choice;
        
        if (cin.fail()) {
            // Nếu nhập không phải số
            cin.clear(); // Xóa trạng thái lỗi
            cin.ignore(10000, '\n'); // Xóa bộ đệm
            cout << "Loi: Vui long nhap so nguyen hop le!" << endl;
            continue;
        }
        
        cin.ignore(10000, '\n'); // Xóa ký tự thừa trong bộ đệm
        
        if (choice >= minChoice && choice <= maxChoice) {
            return choice;
        } else {
            cout << "Loi: Lua chon phai tu " << minChoice << " den " << maxChoice << "!" << endl;
        }
    }
}

// Hàm kiểm tra input số thực hợp lệ (cho điểm)
float getValidFloatInput(const string& prompt, float minValue = 0.0f, float maxValue = 10.0f) {
    float value;
    while (true) {
        cout << prompt;
        cin >> value;
        
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Loi: Vui long nhap so hop le!" << endl;
            continue;
        }
        
        cin.ignore(10000, '\n');
        
        if (value >= minValue && value <= maxValue) {
            return value;
        } else {
            cout << "Loi: Diem phai tu " << minValue << " den " << maxValue << "!" << endl;
        }
    }
}

// Hàm cho sinh viên xem điểm
// Hàm cho sinh viên xem điểm - SỬA LẠI ĐỂ ĐỒNG BỘ
void studentViewScores(Student* student, LoginSystem& loginSystem) {
    clearScreen();
    cout << "=== DIEM CUA SINH VIEN ===" << endl;
    student->displayInfo();
    cout << endl << endl;
    
    auto& dangKyTable = loginSystem.getDangKyTable(); // Lấy reference đến HashTable
    auto allDangKy = dangKyTable.getAllElements(); // Lấy danh sách mới nhất
    bool found = false;
    
    cout << setw(10) << left << "Ma LHP" 
         << setw(20) << left << "Ten Mon Hoc" 
         << setw(10) << right << "Diem" << endl;
    cout << string(50, '-') << endl;
    
    for (auto& dk : allDangKy) {
        if (dk.getMaSV_FK() == student->getId()) {
            // Tìm thông tin lớp học phần
            LopHocPhan* lophp = loginSystem.getLopHPTable().searchByString(dk.getMaLHP_FK());
            if (lophp && lophp->getMonHoc()) {
                cout << setw(10) << left << lophp->getMaLopHP()
                     << setw(20) << left << lophp->getMonHoc()->getTenMon()
                     << setw(10) << right << fixed << setprecision(2) << dk.getDiem() << endl;
                found = true;
            }
        }
    }
    
    if (!found) {
        cout << "Khong co du lieu diem!" << endl;
    }
}

// Hàm cho sinh viên xem lớp học phần đã đăng ký
// Hàm cho sinh viên xem lớp học phần đã đăng ký - SỬA LẠI ĐỒNG BỘ
// Hàm cho sinh viên xem lớp học phần đã đăng ký - THÊM DEBUG
void studentViewRegisteredClasses(Student* student, LoginSystem& loginSystem) {
    clearScreen();
    cout << "=== LOP HOC PHAN DA DANG KY ===" << endl;
    student->displayInfo();
    cout << endl << endl;
    
    auto& dangKyTable = loginSystem.getDangKyTable();
    auto allDangKy = dangKyTable.getAllElements();
    
    // DEBUG: Hiển thị tất cả đăng ký của sinh viên này
    // cout << "DEBUG: Tim kiem dang ky cho SV: " << student->getId() << endl;
    // int count = 0;
    // for (auto& dk : allDangKy) {
    //     cout << "DEBUG: Dang ky " << count++ << ": " << dk.getMaLHP_FK() << "-" << dk.getMaSV_FK() << "-" << dk.getDiem() << endl;
    //     if (dk.getMaSV_FK() == student->getId()) {
    //         cout << "DEBUG: ==> Tim thay dang ky cho SV!" << endl;
    //     }
    // }
    // cout << "Tong so dang ky: " << allDangKy.size() << endl;
    // cout << endl;
    
    bool found = false;
    
    cout << setw(10) << left << "Ma LHP" 
         << setw(20) << left << "Ten Mon Hoc"
         << setw(15) << left << "Giang Vien" << endl;
    cout << string(50, '-') << endl;
    
    for (auto& dk : allDangKy) {
        if (dk.getMaSV_FK() == student->getId()) {
            // Tìm thông tin lớp học phần
            LopHocPhan* lophp = loginSystem.getLopHPTable().searchByString(dk.getMaLHP_FK());
            if (lophp) {
                if (lophp->getMonHoc() && lophp->getGiangVien()) {
                    cout << setw(10) << left << lophp->getMaLopHP()
                         << setw(20) << left << lophp->getMonHoc()->getTenMon()
                         << setw(15) << left << lophp->getGiangVien()->getName() << endl;
                    found = true;
                } else {
                    cout << "DEBUG: Loi - Lop HP " << dk.getMaLHP_FK() << " thieu mon hoc hoac giang vien!" << endl;
                }
            } else {
                cout << "DEBUG: Loi - Khong tim thay Lop HP: " << dk.getMaLHP_FK() << endl;
            }
        }
    }
    
    if (!found) {
        cout << "Khong co lop hoc phan nao da dang ky!" << endl;
    }
}

// Hàm cho giảng viên xem các lớp đã dạy
void teacherViewClasses(Teacher* teacher, LoginSystem& loginSystem) {
    clearScreen();
    cout << "=== CAC LOP HOC PHAN DA DAY ===" << endl;
    teacher->displayInfo();
    cout << endl << endl;
    
    auto allLopHP = loginSystem.getLopHPTable().getAllElements();
    bool found = false;
    
    cout << setw(10) << left << "Ma LHP" 
         << setw(20) << left << "Ten Mon Hoc" << endl;
    cout << string(30, '-') << endl;
    
    for (auto& lophp : allLopHP) {
        if (lophp.getGiangVien() && lophp.getGiangVien()->getId() == teacher->getId()) {
            cout << setw(10) << left << lophp.getMaLopHP()
                 << setw(20) << left << lophp.getMonHoc()->getTenMon() << endl;
            found = true;
        }
    }
    
    if (!found) {
        cout << "Khong co lop hoc phan nao!" << endl;
    }
}

// Hàm kiểm tra điểm hợp lệ
bool isValidScore(float diem) {
    return diem >= 0.0f && diem <= 10.0f;
}

// Hàm cho giảng viên xem và sửa điểm sinh viên - ĐÃ SỬA ĐỒNG BỘ
// Hàm cho giảng viên xem và sửa điểm sinh viên - SỬA LẠI ĐỒNG BỘ HOÀN TOÀN
// Hàm cho giảng viên xem và sửa điểm sinh viên - SỬA LẠI INPUT
void teacherViewAndEditScores(Teacher* teacher, LoginSystem& loginSystem) {
    clearScreen();
    cout << "=== XEM VA SUA DIEM SINH VIEN ===" << endl;
    
    // Hiển thị các lớp học phần của giảng viên
    auto allLopHP = loginSystem.getLopHPTable().getAllElements();
    MyVector<string> teacherClasses;
    
    cout << "Cac lop hoc phan cua ban:" << endl;
    for (auto& lophp : allLopHP) {
        if (lophp.getGiangVien() && lophp.getGiangVien()->getId() == teacher->getId()) {
            cout << "- " << lophp.getMaLopHP() << " (" << lophp.getMonHoc()->getTenMon() << ")" << endl;
            teacherClasses.push_back(lophp.getMaLopHP());
        }
    }
    
    if (teacherClasses.empty()) {
        cout << "Khong co lop hoc phan nao!" << endl;
        return;
    }
    
    cout << "\nNhap ma lop hoc phan de xem diem: ";
    string maLHP;
    getline(cin, maLHP);
    
    // Kiểm tra lớp học phần có thuộc về giảng viên không
    bool validClass = false;
    for (auto& malop : teacherClasses) {
        if (malop == maLHP) {
            validClass = true;
            break;
        }
    }
    
    if (!validClass) {
        cout << "Lop hoc phan khong hop le hoac khong thuoc ve ban!" << endl;
        return;
    }
    
    // Hiển thị danh sách sinh viên và điểm
    clearScreen();
    cout << "=== DANH SACH DIEM - LOP " << maLHP << " ===" << endl;
    
    auto& dangKyTable = loginSystem.getDangKyTable();
    auto allDangKy = dangKyTable.getAllElements();
    bool foundAny = false;
    
    cout << setw(10) << left << "Ma SV"
         << setw(20) << left << "Ten Sinh Vien" 
         << setw(10) << right << "Diem" << endl;
    cout << string(50, '-') << endl;
    
    // Hiển thị tất cả sinh viên trong lớp
    for (auto& dk : allDangKy) {
        if (dk.getMaLHP_FK() == maLHP) {
            Student* student = loginSystem.getStudentTable().searchByString(dk.getMaSV_FK());
            if (student) {
                cout << setw(10) << left << student->getId()
                     << setw(20) << left << student->getName()
                     << setw(10) << right << fixed << setprecision(2) << dk.getDiem() << endl;
                foundAny = true;
            }
        }
    }
    
    if (!foundAny) {
        cout << "Khong co sinh vien nao trong lop hoc phan nay!" << endl;
        return;
    }
    
    // Chức năng sửa điểm
    cout << "\n=== SUA DIEM ===" << endl;
    cout << "Nhap ma sinh vien de sua diem (hoac nhan Enter de bo qua): ";
    string maSV;
    getline(cin, maSV);
    
    if (!maSV.empty()) {
        // Tìm đối tượng DangKy TRỰC TIẾP trong HashTable bằng key
        string searchKey = maLHP + "-" + maSV;
        DangKy* targetDangKy = dangKyTable.searchByString(searchKey);
        
        if (targetDangKy != nullptr) {
            Student* student = loginSystem.getStudentTable().searchByString(maSV);
            if (student) {
                cout << "Sinh vien: " << student->getName() << endl;
                cout << "Diem hien tai: " << fixed << setprecision(2) << targetDangKy->getDiem() << endl;
                
                // Sử dụng hàm input điểm mới
                float diemMoi = getValidFloatInput("Nhap diem moi (0.0 - 10.0): ");
                
                // Cập nhật điểm TRỰC TIẾP trong HashTable
                targetDangKy->setDiem(diemMoi);
                
                cout << "Da cap nhat diem thanh cong!" << endl;
                
                // Hiển thị lại để xác nhận
                cout << "\nDiem da duoc cap nhat:" << endl;
                cout << setw(10) << left << "Ma SV"
                     << setw(20) << left << "Ten Sinh Vien" 
                     << setw(10) << right << "Diem" << endl;
                cout << string(50, '-') << endl;
                cout << setw(10) << left << student->getId()
                     << setw(20) << left << student->getName()
                     << setw(10) << right << fixed << setprecision(2) << targetDangKy->getDiem() << endl;
            } else {
                cout << "Khong tim thay thong tin sinh vien!" << endl;
            }
        } else {
            cout << "Khong tim thay sinh vien trong lop hoc phan nay!" << endl;
        }
    }
}

// Hàm lưu tất cả dữ liệu
bool saveAllData(LoginSystem& loginSystem) {
    try {
        cout << "Dang luu du lieu..." << endl;
        
        // CHỈ lưu những file thực sự cần thiết (DangKy.txt là quan trọng nhất)
        if (!loginSystem.getDangKyTable().saveToFile("dangky.txt")) {
            cout << "Loi khi luu du lieu dang ky!" << endl;
            return false;
        }
        
        cout << "Da luu du lieu thanh cong!" << endl;
        return true;
    } catch (const exception& e) {
        cout << "Loi khi luu du lieu: " << e.what() << endl;
        return false;
    }
}

// Hàm hỏi lưu dữ liệu khi thoát
void askToSaveData(LoginSystem& loginSystem) {
    char choice;
    while (true) {
        cout << "\n=== LUU DU LIEU ===" << endl;
        cout << "Ban co muon luu lai tat ca thay doi? (y/n): ";
        cin >> choice;
        cin.ignore(10000, '\n');
        
        if (choice == 'y' || choice == 'Y' || choice == 'n' || choice == 'N') {
            break;
        } else {
            cout << "Loi: Vui long nhap 'y' hoac 'n'!" << endl;
        }
    }
    
    if (choice == 'y' || choice == 'Y') {
        if (saveAllData(loginSystem)) {
            cout << "Du lieu da duoc luu thanh cong!" << endl;
        } else {
            cout << "Co loi khi luu du lieu!" << endl;
        }
    } else {
        cout << "Thay doi chua duoc luu!" << endl;
    }
}

// Hàm hiển thị menu chính
void showMainMenu() {
    clearScreen();
    cout << "=== HE THONG QUAN LY SINH VIEN ===" << endl;
    cout << "1. Dang nhap" << endl;
    cout << "2. Thoat" << endl;
    cout << "Lua chon: ";
}

// Hàm xử lý menu sinh viên
void handleStudentMenu(Student* student, LoginSystem& loginSystem, int choice, bool& logout) {
    switch (choice) {
        case 1: // Xem thông tin cá nhân
            clearScreen();
            cout << "=== THONG TIN CA NHAN ===" << endl;
            student->displayInfo();
            cout << endl;
            break;
            
        case 2: // Xem lớp học phần đã đăng ký
            studentViewRegisteredClasses(student, loginSystem);
            break;
            
        case 3: // Xem điểm các môn học
            studentViewScores(student, loginSystem);
            break;
            
        case 4: // Đăng xuất
            logout = true;
            cout << "Dang xuat..." << endl;
            break;
            
        default:
            cout << "Lua chon khong hop le!" << endl;
    }
}

// Hàm xử lý menu giảng viên
void handleTeacherMenu(Teacher* teacher, LoginSystem& loginSystem, int choice, bool& logout) {
    switch (choice) {
        case 1: // Xem thông tin cá nhân
            clearScreen();
            cout << "=== THONG TIN CA NHAN ===" << endl;
            teacher->displayInfo();
            cout << endl;
            break;
            
        case 2: // Xem lớp học phần đang dạy
            teacherViewClasses(teacher, loginSystem);
            break;
            
        case 3: // Xem danh sách sinh viên và sửa điểm
            teacherViewAndEditScores(teacher, loginSystem);
            break;
            
        case 4: // Đăng xuất
            logout = true;
            cout << "Dang xuat..." << endl;
            break;
            
        default:
            cout << "Lua chon khong hop le!" << endl;
    }
}
void AdminviewAllStudents(LoginSystem& loginSystem){
    clearScreen();
    cout << "=== DANH SACH SINH VIEN ===" << endl;
    auto& StudentTB = loginSystem.getStudentTable();
    cout << setw(10) << left << "Ma SV" 
         << setw(20) << left << "Ten Sinh Vien" 
         << setw(15) << left << "Khoa" << endl;
    cout << string(50, '-') << endl;

    for (auto& student:StudentTB.getAllElements()){
        cout << setw(10) << left << student.getId()
             << setw(20) << left << student.getName()
             << setw(15) << left << (student.getKhoa() ? student.getKhoa()->getTenKhoa() : "Chua xac dinh") << endl;
    }
}
void AdminviewAllClasses(LoginSystem& loginSystem){
    clearScreen();
    cout << "=== DANH SACH LOP HOC PHAN ===" << endl;
    auto& LopHPtb = loginSystem.getLopHPTable();
    cout << setw(10) << left << "Ma LHP" 
         << setw(20) << left << "Ten Mon Hoc" 
         << setw(15) << left << "Giang Vien" << endl;
    cout << string(50, '-') << endl;

    for (auto& lophp:LopHPtb.getAllElements()){
        cout << setw(10) << left << lophp.getMaLopHP()
             << setw(20) << left << (lophp.getMonHoc() ? lophp.getMonHoc()->getTenMon() : "Chua xac dinh")
             << setw(15) << left << (lophp.getGiangVien() ? lophp.getGiangVien()->getName() : "Chua xac dinh") << endl;
    }
}
void AdminviewAllRegistrations(LoginSystem& LoginSystem){
    clearScreen();
    cout << "=== DANH SACH DANG KY ===" << endl;
    auto& DangKyTB = LoginSystem.getDangKyTable();
    cout << setw(10) << left << "Ma LHP" 
         << setw(10) << left << "Ma SV" 
         << setw(10) << right << "Diem" << endl;
    cout << string(40, '-') << endl;

    for (auto& dk : DangKyTB.getAllElements()){
        cout << setw(10) << left << dk.getMaLHP_FK()
             << setw(10) << left << dk.getMaSV_FK()
             << setw(10) << right << fixed << setprecision(2) << dk.getDiem() << endl;
    }
}
void AdminviewAllTeachers(LoginSystem& loginSystem){
    clearScreen();
    cout << "=== DANH SACH GIANG VIEN ===" << endl;
    auto& TeacherTB = loginSystem.getTeacherTable();
    cout << setw(10) << left << "Ma GV" 
         << setw(20) << left << "Ten Giang Vien" 
         << setw(15) << left << "Khoa" << endl;
    cout << string(50, '-') << endl;

    for (auto& teacher:TeacherTB.getAllElements()){
        cout << setw(10) << left << teacher.getId()
             << setw(20) << left << teacher.getName()
             << setw(15) << left << (teacher.getKhoa() ? teacher.getKhoa()->getTenKhoa() : "Chua xac dinh") << endl;
    }
}
void AdminviewAllDepartments(LoginSystem& loginSystem){
    clearScreen();
    cout << "=== DANH SACH KHOA ===" << endl;
    auto& KhoaTB = loginSystem.getKhoaTable();
    cout << setw(10) << left << "Ma Khoa" 
         << setw(20) << left << "Ten Khoa" << endl;
    cout << string(30, '-') << endl;

    for (auto& khoa:KhoaTB.getAllElements()){
        cout << setw(10) << left << khoa.getMaKhoa()
             << setw(20) << left << khoa.getTenKhoa() << endl;
    }
}

// Hiển thị tất cả môn học
void AdminviewAllSubjects(LoginSystem& loginSystem){
    clearScreen();
    cout << "=== DANH SACH MON HOC ===" << endl;
    auto& MonTB = loginSystem.getMonHocTable();
    cout << setw(10) << left << "Ma MH" << setw(30) << left << "Ten Mon" << endl;
    cout << string(40, '-') << endl;
    for (auto& mh : MonTB.getAllElements()){
        cout << setw(10) << left << mh.getMaMon()
             << setw(30) << left << mh.getTenMon() << endl;
    }
}

// Quản lý tài khoản (hiển thị và thêm tài khoản vào file Account.txt)
void AdminManageAccounts(LoginSystem& loginSystem){
    clearScreen();
    cout << "=== QUAN LY TAI KHOAN ===" << endl;
    // Hiển thị nội dung file Account.txt
    ifstream inFile("Account.txt");
    if (!inFile.is_open()){
        cout << "Khong the mo Account.txt" << endl;
        return;
    }
    string line;
    int idx = 0;
    cout << "STT\tUsername,password" << endl;
    cout << string(30, '-') << endl;
    while (getline(inFile, line)){
        cout << ++idx << "\t" << line << endl;
    }
    inFile.close();

    cout << "\nBan co muon them tai khoan moi vao file Account.txt? (y/n): ";
    char c; cin >> c; cin.ignore(10000, '\n');
    if (c == 'y' || c == 'Y'){
        string username, password, typeCode;
        cout << "Nhap username: "; getline(cin, username);
        cout << "Nhap password: "; getline(cin, password);
        cout << "Nhap ma loai nguoi dung (SV/GV/AD) [mac dinh SV]: "; getline(cin, typeCode);
        if (typeCode.empty()) typeCode = "SV";

        // Luu vao file
        ofstream outFile("Account.txt", ios::app);
        if (!outFile.is_open()){
            cout << "Khong the mo Account.txt de ghi!" << endl;
            return;
        }
        outFile << username << "," << password << "\n";
        outFile.close();
        cout << "Da them tai khoan. Luu y: thay doi chi co hieu luc sau khi khoi dong lai chuong trinh hoac tai lai file." << endl;
    }
}
// Hàm thêm hoặc xóa sinh viên khỏi lớp học phần
void removeAndAddStudentfromlhp(string LopHocPhan,string Student,LoginSystem& loginSystem){
    auto& DangKyTB = loginSystem.getDangKyTable();
    auto& LopHocPhanTB = loginSystem.getLopHPTable();
    auto& StudentTB = loginSystem.getStudentTable();
    bool check=0;
    bool removeHayAdd=(LopHocPhanTB.contains(LopHocPhan) && StudentTB.contains(Student))?0:1;

    if (removeHayAdd==0){
        for (auto& dk:DangKyTB.getAllElements()){
            if (dk.getMaLHP_FK()==LopHocPhan && dk.getMaSV_FK()==Student){
                DangKyTB.remove(LopHocPhan+"-"+Student);
                check=1;
            }
        }
    }else {
        DangKy dk(LopHocPhan,Student,0);
        DangKyTB.insert(dk.getMaLHP_FK()+"-"+dk.getMaSV_FK(),dk);
        cout<<"sinh vien da dc them vao";
    }   


    if (check && removeHayAdd==0){
        cout<<"da xoa thanh cong"<<endl;
    }
    else if(!check && removeHayAdd==0){
        cout<<"sinh vien ko ton tai trong lop hoc phan"<<endl;
    }
}
//chuyển đổi khoa cho sinh viên ,giảng viên
void changeDepartmentforUser(string UserID,string KhoaID,LoginSystem& loginSystem){
    if (UserID=="p") return;
    auto& KhoaTB = loginSystem.getKhoaTable();
    Khoa* khoaPtr = KhoaTB.searchByString(KhoaID);
    if (khoaPtr){
        auto& StudentTB = loginSystem.getStudentTable();
        auto& TeacherTB = loginSystem.getTeacherTable();
        if (StudentTB.contains(UserID)){
            Student* studentPtr=StudentTB.searchByString(UserID);
            studentPtr->setKhoa(khoaPtr);
            cout<<"da chuyen khoa cho sinh vien"<<endl;
        }else if (TeacherTB.contains(UserID)){
            Teacher* teacherPtr=TeacherTB.searchByString(UserID);
            teacherPtr->setKhoa(khoaPtr);
            cout<<"da chuyen khoa cho giang vien"<<endl;
        }else {
            cout<<"khong tim thay nguoi dung"<<endl;
        }
    }else {
        cout<<"khong tim thay khoa"<<endl;
    }
}
//giảng viên viết báo cáo thống kê về lớp học phần(số sinh viên khá giỏi, trung bình, yếu) rồi in ra file
void teacherGenerateClassReport(string LopHocPhan,LoginSystem& LoginSystem){
    auto& DangKyTB=LoginSystem.getDangKyTable();
    ofstream outFile("ClassReport_"+LopHocPhan+".txt");
    if (!outFile.is_open()) {
        cout << "Khong the mo file de ghi bao cao!" << endl;
        return;
    }

    int countKhaGioi=0;
    int countTrungBinh=0;
    int countYeu=0;

    for (auto& dk:DangKyTB.getAllElements()){
        if (dk.getMaLHP_FK()==LopHocPhan){
            float diem=dk.getDiem();
            if (diem>=7.0f){
                countKhaGioi++;
            }else if (diem>=5.0f){
                countTrungBinh++;
            }else {
                countYeu++;
            }
        }
    }

    outFile<<"Bao cao lop hoc phan: "<<LopHocPhan<<endl;
    outFile<<"So sinh vien kha gioi: "<<countKhaGioi<<endl;
    outFile<<"So sinh vien trung binh: "<<countTrungBinh<<endl;
    outFile<<"So sinh vien yeu: "<<countYeu<<endl;

    outFile.close();
    cout<<"Da tao bao cao lop hoc phan: ClassReport_"<<LopHocPhan<<".txt"<<endl;
}
//admin đọc file thống kê do giảng viên tạo ra và hiển thị nội dung
void AdminviewClassReport(string LopHocPhan){
    ifstream inFile("ClassReport_"+LopHocPhan+".txt");
    if (!inFile.is_open()) {
        cout << "Khong the mo file bao cao!" << endl;
        return;
    }

    string line;
    cout << "=== BAO CAO LOP HOC PHAN: " << LopHocPhan << " ===" << endl;
    while (getline(inFile, line)) {
        cout << line << endl;
    }

    inFile.close();
}
// Hàm xử lý menu admin
void handleAdminMenu(LoginSystem& loginSystem, int choice, bool& logout) {
    switch (choice) {
        case 1:
            {
                AdminviewAllStudents(loginSystem);
                // ví dụ: cho phép đổi khoa
                string id, khoa;
                cout << "Muon doi khoa cho nguoi dung? (nhap ID nguoi dung hoac ENTER de bo qua): ";
                if (getline(cin,id) && !id.empty()) {
                    cout << "Nhap ma khoa: ";
                    cin >> khoa;
                    changeDepartmentforUser(id, khoa, loginSystem);
                }
            }
            break;
        case 2:
            {
                AdminviewAllTeachers(loginSystem);
                string id, khoa;
                cout << "Muon doi khoa cho nguoi dung? (nhap ID nguoi dung hoac ENTER de bo qua): ";
                if (getline(cin,id) && !id.empty()) {
                    cout << "Nhap ma khoa: ";
                    cin >> khoa;
                    changeDepartmentforUser(id, khoa, loginSystem);
                }
            }
            break;

        case 3:
            AdminviewAllSubjects(loginSystem);
            break;

        case 4:
            {
                AdminviewAllClasses(loginSystem);
                // submenu: quan ly lop hoc phan
                cout << "1. Tro ve\n2. Them/Xoa sinh vien\n3. Tao bao cao\n4. Xem bao cao\nLua chon: ";
                int sub; cin >> sub;
                if (sub == 2) {
                    string lhp, sv;
                    cout << "Nhap ma LopHocPhan: "; cin >> lhp;
                    cout << "Nhap ma SinhVien: "; cin >> sv;
                    removeAndAddStudentfromlhp(lhp, sv, loginSystem);
                } else if (sub == 3) {
                    string lhp; cout << "Nhap ma LopHocPhan de tao bao cao: "; cin >> lhp;
                    teacherGenerateClassReport(lhp, loginSystem);
                    cout<<"Nhap bat ky de tiep tuc...";
                } else if (sub == 4) {
                    string lhp; cout << "Nhap ma LopHocPhan de xem bao cao: "; cin >> lhp;
                    AdminviewClassReport(lhp);
                    cout<<"Nhap bat ky de tiep tuc...";
                }
            }
            break;

        case 5:
            AdminviewAllRegistrations(loginSystem);
            break;

        case 6:
            AdminManageAccounts(loginSystem);
            break;

        case 7:
            logout = true;
            break;

        default:
            cout << "Lua chon khong hop le\n";
            break;
    }
}
int main() {
    LoginSystem loginSystem;
    
    // Load dữ liệu khi khởi động
    try {
        cout << "Dang tai du lieu..." << endl;
        if (!loginSystem.loadAllData()) {
            cout << "Loi khi tai du lieu! Kiem tra cac file du lieu." << endl;
            cout << "Nhan Enter de thoat...";
            cin.get();
            return 1;
        }
        cout << "Tai du lieu thanh cong!" << endl;
    } catch (const exception& e) {
        cout << "Loi khong mong muon khi tai du lieu: " << e.what() << endl;
        cout << "Nhan Enter de thoat...";
        cin.get();
        return 1;
    }
    
    // Biến cho giao diện đăng nhập
    string username, password;
    User* currentUser = nullptr;
    bool exitProgram = false;
    
    while (!exitProgram) {
        showMainMenu();
        
        // Sử dụng hàm input mới
        int mainChoice = getValidIntInput("", 1, 2);
        
        if (mainChoice == 2) {
            // Thoát chương trình
            askToSaveData(loginSystem);
            cout << "Tam biet!" << endl;
            exitProgram = true;
            continue;
        }
        
        if (mainChoice == 1) {
            // Đăng nhập
            cout << "Username: ";
            getline(cin, username);
            cout << "Password: ";
            getline(cin, password);
            
            currentUser = loginSystem.login(username, password);
            
            if (currentUser != nullptr) {
                bool logout = false;
                
                while (!logout) {
                    clearScreen();
                    cout << "=== CHAO MUNG ===" << endl;
                    currentUser->displayInfo();
                    cout << endl;
                    
                    // Hiển thị menu theo loại user
                    currentUser->showMenu();
                    
                    // Xác định số lượng lựa chọn tối đa theo loại user
                    int maxChoice = 4; // Mặc định cho Student và Teacher
                    if (currentUser->getUserType() == UserType::ADMIN) {
                        maxChoice = 7;
                    }
                    
                    // Sử dụng hàm input mới
                    int userChoice = getValidIntInput("Lua chon: ", 1, maxChoice);
                    
                    // Lưu loại người dùng vào biến local để sử dụng trong các so sánh
                    UserType userType = currentUser->getUserType();
                    
                    if (userType == UserType::STUDENT) {
                        Student* student = dynamic_cast<Student*>(currentUser);
                        handleStudentMenu(student, loginSystem, userChoice, logout);
                    }
                    else if (userType == UserType::TEACHER) {
                        Teacher* teacher = dynamic_cast<Teacher*>(currentUser);
                        handleTeacherMenu(teacher, loginSystem, userChoice, logout);
                    }
                    else if (userType == UserType::ADMIN) {
                        handleAdminMenu(loginSystem, userChoice, logout);
                    }
                    
                    // Tạm dừng trước khi hiển thị menu lại (trừ khi logout)
                    if (!logout) {
                        cout << "\nNhan Enter de tiep tuc...";
                        cin.get();
                    }
                }
                
                cout << "Da dang xuat thanh cong!" << endl;
            } else {
                cout << "Dang nhap that bai! Sai username hoac password." << endl;
            }
            
            // Tạm dừng trước khi quay lại menu chính
            if (!exitProgram) {
                cout << "Nhan Enter de quay lai menu chinh...";
                cin.get();
            }
        }
    }
    
    return 0;
}