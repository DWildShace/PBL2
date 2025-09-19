#include <iostream>
#include <cstdlib> // Dùng cho system()

// Sử dụng struct cho Element vẫn phù hợp vì nó chỉ chứa dữ liệu đơn giản
struct Element {
    int key;
};

// Lớp HashTable đóng gói tất cả dữ liệu và hoạt động liên quan
class HashTable {
    private:
        // Định nghĩa Node như một struct lồng bên trong (nested struct)
        // vì nó là một chi tiết triển khai của HashTable
        struct Node {
            Element e;
            Node* next;
        };

        int capacity; // Sức chứa của bảng băm
        Node** T;     // Con trỏ tới mảng các con trỏ Node (các danh sách liên kết)

        // Hàm băm được đặt là private vì nó chỉ được sử dụng bên trong lớp
        int hashFunction(int key) {
            return key % capacity;
        }

    public:
        // 1. Constructor (Hàm khởi tạo) - thay thế cho hàm create()
        HashTable(int size) {
            capacity = size;
            // Sử dụng 'new[]' để cấp phát mảng
            T = new Node*[capacity];
            // Khởi tạo mỗi phần tử trong mảng là nullptr (không có node nào)
            for (int i = 0; i < capacity; ++i) {
                T[i] = nullptr;
            }
        }

        // 2. Destructor (Hàm hủy) - để giải phóng bộ nhớ, tránh rò rỉ
        ~HashTable() {
            for (int i = 0; i < capacity; ++i) {
                Node* current = T[i];
                while (current != nullptr) {
                    Node* toDelete = current;
                    current = current->next;
                    delete toDelete; // Xóa từng node trong danh sách liên kết
                }
            }
            delete[] T; // Xóa mảng các con trỏ
        }

        // 3. Phương thức add (thêm phần tử)
        void add(Element e) {
            // Sử dụng 'new' để tạo node mới
            Node* newNode = new Node;
            newNode->e = e;

            int pos = hashFunction(e.key);

            // Chèn node mới vào đầu danh sách liên kết tại vị trí 'pos'
            newNode->next = T[pos];
            T[pos] = newNode;
        }

        // 4. Phương thức search (tìm kiếm)
        Node* search(int key) {
            int pos = hashFunction(key);
            Node* temp = T[pos];

            while (temp != nullptr && temp->e.key != key) {
                temp = temp->next;
            }
            return temp;
        }

        // 5. Phương thức show (hiển thị bảng băm)
        void show() {
            for (int i = 0; i < capacity; ++i) {
                // Sử dụng std::cout từ thư viện <iostream>
                std::cout << i << "--";
                Node* temp = T[i];
                while (temp != nullptr) {
                    std::cout << temp->e.key << " ";
                    temp = temp->next;
                }
                std::cout << std::endl; // Sử dụng std::endl để xuống dòng
            }
        }
};

int main() {
    // Khởi tạo đối tượng HashTable bằng constructor
    HashTable H(5);

    // Khởi tạo các phần tử một cách ngắn gọn
    Element e1 = {2};
    Element e2 = {55};
    Element e3 = {34};
    Element e4 = {12};
    Element e5 = {1};

    // Gọi các phương thức của đối tượng bằng toán tử '.'
    H.add(e1);
    H.add(e2);
    H.add(e3);
    H.add(e4);
    H.add(e5);

    H.show();

    // system("color F0"); // Lệnh này chỉ hoạt động trên Windows
    return 0;
}