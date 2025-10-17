#include <iostream>
#include <iomanip>
#include <fstream>
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

// Hàm xử lý menu admin
void handleAdminMenu(User* admin, int choice, bool& logout) {
    switch (choice) {
        case 1: case 2: case 3: case 4: case 5: case 6:
            clearScreen();
            cout << "=== CHUC NANG QUAN TRI ===" << endl;
            cout << "Cac chuc nang quan tri dang duoc phat trien..." << endl;
            cout << "Ban da chon chuc nang: " << choice << endl;
            break;
            
        case 7: // Đăng xuất
            logout = true;
            cout << "Dang xuat..." << endl;
            break;
            
        default:
            cout << "Lua chon khong hop le!" << endl;
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
                    
                    // Xử lý lựa chọn theo loại user
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
                        handleAdminMenu(currentUser, userChoice, logout);
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