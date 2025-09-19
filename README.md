# PBL2

thư viện Vector

khai báo thư viện include<vector>

Vector<kieu du lieu co the la class> v("số phần tử","giá trị phần tử mặt định") . vd: vector<int> v(5,0)=>{0,0,0,0,0}

them xoa:
    V.push_back() //them phan tu o cuoi
    V.pop_back() //xoa phan tu o cuoi
    V.clear()  //xoa sach
    V.erase()  /xoa 1 hoac nhieu phan tu o vi tri chi dinh

cac lenh truy cap:
    V.at(vi tri truy cap)  => dung an toan hon so voi V.[] va co hien thi loi


lay kich thuoc:
    V.sizeof();
    V.empty() tra ve true va false

co for-each