#include <iostream>
#include <random>
using namespace std;

int main() {
    // Tạo một đối tượng generator ngẫu nhiên
    random_device rd;
    mt19937 generator(rd());

    // Tạo một phạm vi ngẫu nhiên từ 1 đến 100
    uniform_int_distribution<int> rand_0_34(0, 34);
    uniform_int_distribution<int> rand_0_29(0, 29);
    uniform_int_distribution<int> rand_1_30(1, 30);
    uniform_int_distribution<int> rand_1_12(1, 12);
    uniform_int_distribution<int> rand_0_1(0, 1);
    uniform_int_distribution<int> rand_100000_999999(100000, 999999);

    // Sinh số ngẫu nhiên
    int random_number = rand_0_1(generator);
    string hoNam[35] = { "Nguyen Van", "Tran Minh", "Le Tuan", "Pham Hoai", "Huynh Van", "Hoang Minh", "Vo Cao", "Vu Tuan", "Phan Chau", "Truong Thanh", "Bui Xuan" , "Dang Vinh", "Do Hung", "Ngo", "Ho Quy", "Duong Dinh", "Dinh Van", "Doan Thanh", "Lam Vu", "Mai Thua", "Trinh Thanh", "Dao Cao", "Cao Vu", "Ly Van","Ha Giang", "Luu Quang", "Luong Khuc", "Thai My", "Chau Thanh", "Ha Van", "Phung Van", "To Quach", "Quach Tuan", "Hua Vinh", "Tu Quang" };
    string hoNu[35] = { "Nguyen Thi", "Tran Thi", "Le Ngoc", "Pham Kieu", "Huynh Thi" , "Hoang Chau", "Vo Thi", "Vu Ngoc", "Phan Phuong", "Truong Ngoc", "Bui Xuan", "Dang Kieu", "Do Thi My", "Ngo Cao Ngoc", "Ho Xuan", "Duong Tran", "Dinh Uyeng", "Doan Uyen", "Lam My", "Mai Huyng", "Trinh Vy", "Dao Anh", "Cao Anh", "Ly Yen","Ha Ho", "Luu Ngoc", "Luong Gia", "Thai Tran", "Chau Thanh", "Ha Thi", "Phung Thi", "To Huynh", "Quach Ngoc", "Hua My My", "Tu Tu" };
    string tenNam[30] = { "An", "Binh", "Chi", "Dat", "Dung", "Ha", "Hoang", "Hung", "Khanh", "Kien", "Lam", "Long", "Minh", "Nam", "Nghia", "Phong", "Quan", "Son", "Tien", "Trung", "Tuan", "Tung", "Vinh", "Vu", "Khanh", "Huy", "Quang", "Thanh", "Thien", "Truong" };
    string tenNu[30] = { "Anh", "Bich", "Cam", "Diem", "Dao", "Ha", "Hanh", "Hien", "Hoai", "Hue", "Huong", "Huong", "Lan", "Linh", "Ly", "Mai", "My", "Ngoc", "Nhi", "Nhung", "Oanh", "Phuong", "Quynh", "Thuy", "Tuyet", "Uyen", "Van", "Yen", "Trang", "Khanh" };
    int mssv = 22127001;
    int nam = 2004;
  /*  for (int i = 1; i < 31; i++) {
        int gioitinh= rand_0_1(generator);
        string honguoinam = hoNam[rand_0_34(generator)];
        string honguoinu = hoNu[rand_0_34(generator)];
        string tennguoinam = tenNam[rand_0_29(generator)]; 
        string tennguoinu = tenNu[rand_0_29(generator)];
        cout << mssv<<",";
        if (gioitinh == 0) {
            cout << honguoinam << "," << tennguoinam << ",";
        }
        if (gioitinh == 1) {
            cout << honguoinu << "," << tennguoinu << ",";
        }
        cout << rand_1_30(generator) << "/" << rand_1_12(generator) << "/" << nam << ",";
        if (gioitinh == 0) cout << "Nam";
        if (gioitinh == 1) cout << "Nu";
        cout << "," <<rand_100000_999999(generator);
        cout << endl;
        mssv++;

    }*/
    for (int i = 22120001; i <= 22120030; i++) {
        cout << i << "," << 123 << endl;
    }
    for (int i = 22125001; i <= 22125030; i++) {
        cout << i << "," << 123 << endl;
    }
    for (int i = 22126001; i <= 22126030; i++) {
        cout << i << "," << 123 << endl;
    }
    for (int i = 22127001; i <= 22127030; i++) {
        cout << i << "," << 123 << endl;
    }
    return 0;
}
