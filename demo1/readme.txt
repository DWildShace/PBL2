    HashTable<LopHocPhan>& getLopHPTable() { return lopHPTable; }
    HashTable<DangKy>& getDangKyTable() { return dangKyTable; }
    HashTable<Student>& getStudentTable() { return studentTable; }
    HashTable<Teacher>& getTeacherTable() { return teacherTable; }
    HashTable<MonHoc>& getMonHocTable() { return monHocTable; }
    HashTable<Khoa>& getKhoaTable() { return khoaTable; }



    g++ User.cpp Account.cpp Admin.cpp DangKy.cpp LopHocPhan.cpp Main.cpp Monhoc.cpp Student.cpp Teacher.cpp -o Main.exe
