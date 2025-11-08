    HashTable<LopHocPhan>& getLopHPTable() { return lopHPTable; }
    HashTable<DangKy>& getDangKyTable() { return dangKyTable; }
    HashTable<Student>& getStudentTable() { return studentTable; }
    HashTable<Teacher>& getTeacherTable() { return teacherTable; }
    HashTable<MonHoc>& getMonHocTable() { return monHocTable; }
    HashTable<Khoa>& getKhoaTable() { return khoaTable; }


    chưa hiểU lắm về việc trả về &

virtual void displayInfo() const;

Teacher* teacher = dynamic_cast<Teacher*>(currentUser);

GIẢI THÍCH LẠI DÒNG CODE NÀY


username của account vừa là tên đăng nhập vừa là key 
g++ User.cpp Account.cpp Admin.cpp DangKy.cpp LopHocPhan.cpp Main.cpp Monhoc.cpp Student.cpp Teacher.cpp -o Main.exe
