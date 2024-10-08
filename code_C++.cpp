#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include"1.h"
using namespace std;

// Hàm tạo mới 1 sản phẩm
Stationery::Stationery(int _id, string _n, double _p, int _q) {
    id = _id;
    name = _n;
    price = _p;
    quantity = _q;
}

// Hàm lấy id sản phẩm
int Stationery::getId() const { return id; } 

// Hàm lấy tên sản phẩm
string Stationery::getName() const { return name; } 

// Hàm lấy giá tiền của sản phẩm
double Stationery::getPrice() const { return price; } 

// Hàm lấy số lượng sản phẩm
int Stationery::getQuantity() const { return quantity; } 

// Hàm thay đổi id của sản phẩm
void Stationery::setId(int _id) { id = _id; }

// Hàm thay đổi tên của sản phẩm
void Stationery::setName(string _n) { name = _n; }

// Hàm thay đổi giá tiền của sản phẩm
void Stationery::setPrice(double _p) { price = _p; }

// Hàm thay đổi số lượng của sản phẩm
void Stationery::setQuantity(int _q) { quantity = _q; }

// Hàm nhập thông tin 1 sản phẩm
void Stationery::nhaptt() {
    cout << "Nhap ID san pham: ";
    cin >> id;
    cin.ignore();
    cout << "Nhap ten san pham: ";
    getline(cin, name);
    cout << "Nhap gia san pham: ";
    cin >> price;
    cout << "Nhap so luong san pham: ";
    cin >> quantity;
}

// Hàm hiển thị thông tin sản phẩm
void Stationery::hienthitt() const {
    cout << "Ma so san pham: " << id << endl;
    cout << "Ten san pham: " << name << endl;
    cout << "Gia san pham: " << price << " vnd" << endl;
    cout << "So luong san pham: " << quantity << endl;
}

// Hàm hiển thị menu
void displayMenu() {
    cout << "\n--- MENU ---\n";
    cout << "1. Them moi san pham\n";
    cout << "2. Sua thong tin san pham\n";
    cout << "3. Xoa san pham\n";
    cout << "4. Hien thi danh sach san pham\n";
    cout << "5. Sap xep san pham\n";
    cout << "6. Luu danh sach san pham\n";
    cout << "7. Tim kiem san pham\n";
    cout << "8. Thoat chuong trinh.\n";
    cout << "Nhap lua chon: ";
}

// Hàm tìm kiếm sản phẩm theo ID
int findProductById(const vector<Stationery>& products, int id) {
    for (size_t i = 0; i < products.size(); ++i) {
        if (products[i].getId() == id) {
            return i;
        }
    }
    return -1; // Không tìm thấy
}

//hàm tìm kiếm sản phẩm theo tên
int findProductByName(const vector<Stationery>& products, string name){
    for (size_t i = 0; i < products.size(); ++i) {
        if (products[i].getName() == name) {
            return i;
        }
    }
    return -1; // Không tìm thấy
}

//hàm xuất thông tin ra 1 file
void saveToFile(const vector<Stationery>& products) {
    ofstream outputFile("information.txt");
    if (!outputFile) {
        cerr << "Khong the xuat file!" << endl;
        return;
    }
    for (const auto& product : products) {
        outputFile << product.getId() << ","
                   << product.getName() << ","
                   << product.getPrice() << ","
                   << product.getQuantity() << "\n";
    }
    outputFile.close();
}

//hàm sắp xếp theo ID
void selectionSortById(vector<Stationery>& products) {
    for (size_t i = 0; i < products.size() - 1; ++i) {
        size_t minIndex = i;
        for (size_t j = i + 1; j < products.size(); ++j) {
            if (products[j].getId() < products[minIndex].getId()) {
                minIndex = j;
            }
        }
        swap(products[i], products[minIndex]);
    }
}
//hàm sắp xếp theo tên
void selectionSortByName(vector<Stationery>& products) {
    for (size_t i = 0; i < products.size() - 1; ++i) {
        size_t minIndex = i;
        for (size_t j = i + 1; j < products.size(); ++j) {
            if (products[j].getName() < products[minIndex].getName()) {
                minIndex = j;
            }
        }
        swap(products[i], products[minIndex]);
    }
}

// hàm sắp xếp theo giá tiền
void selectionSortByPrice(vector<Stationery>& products) {
    for (size_t i = 0; i < products.size() - 1; ++i) {
        size_t minIndex = i;
        for (size_t j = i + 1; j < products.size(); ++j) {
            if (products[j].getPrice() < products[minIndex].getPrice()) {
                minIndex = j;
            }
        }
        swap(products[i], products[minIndex]);
    }
}


int main() {
    vector<Stationery> products;
    ifstream inputFile("data.txt"); // Mở file để đọc

    if (!inputFile) {
        cerr << "Khong tim thay file!" << endl;
        return 1;
    }
//Đọc dữ liệu từ file
    string line;

    while (getline(inputFile, line)) {
        stringstream ss(line);
        string token;
        int id;
        string name;
        double price;
        int quantity;

        if (getline(ss, token, ',')) { id = stoi(token); }
        if (getline(ss, token, ',')) { name = token; }
        if (getline(ss, token, ',')) { price = stod(token); }
        if (getline(ss, token, ',')) { quantity = stoi(token); }

        if (!name.empty()) {
            products.push_back(Stationery(id, name, price, quantity));
        }
    }

    inputFile.close();

    int choice;

    do {
        displayMenu();
        cin >> choice;

        switch (choice) {
            case 1: {
                Stationery newProduct;
                newProduct.nhaptt();
                products.push_back(newProduct);
                break;
            }
            case 2: {
                int findchoice;
                cout << "Tim kiem san pham theo : \n1.ID \n2.Ten \nNhap lua chon : ";
                cin >> findchoice;
                cin.ignore(); 

                switch(findchoice) {
                    case 1: {
                        int id;
                        cout << "Nhap ID san pham can sua: ";
                        cin >> id;
                        cin.ignore();
                        int index = findProductById(products, id);
                        if (index != -1) {
                            products[index].nhaptt();
                        } else {
                            cout << "San pham khong ton tai.\n";
                        }
                        break;
                    }
                    case 2: {
                        string name;
                        cout << "Nhap ten san pham can sua: ";
                        getline(cin, name);
                        int index = findProductByName(products, name);
                        if (index != -1) {
                            products[index].nhaptt();
                        } else {
                            cout << "San pham khong ton tai.\n";
                        }
                        break;
                    }
                    default:
                        cout << "Lua chon khong hop le.\n";
                        break;
                }
                break;
            }
            case 3: {
                int id;
                cout << "Nhap ID san pham can xoa: ";
                cin >> id;
                int index = findProductById(products, id);
                if (index != -1) {
                    products.erase(products.begin() + index);
                    cout << "San pham da duoc xoa.\n";
                } else {
                    cout << "San pham khong ton tai.\n";
                }
                break;
            }
            case 4: {
                for (const auto& product : products) {
                    product.hienthitt();
                    cout << "----------------\n";
                }
                break;
            }
            case 5: {
                int sortChoice;
                cout << "\nSap xep theo: \n1. ID\n2. Ten\n3. Gia\nNhap lua chon: ";
                cin >> sortChoice;
                switch (sortChoice) {
                    case 1: selectionSortById(products); break;
                    case 2: selectionSortByName(products); break;
                    case 3: selectionSortByPrice(products); break;
                    default: cout << "Lua chon khong hop le.\n"; break;
                }
                break;
            }
            case 6: {
                saveToFile(products);
                cout << "Da luu danh sach san pham vao file information.txt\n";
                break;
            }
            case 7: {
                int findchoice;
                cout << "Tim kiem san pham theo : \n1.ID \n2.Ten \nNhap lua chon : ";
                cin >> findchoice;
                cin.ignore(); 

                switch(findchoice) {
                    case 1: {
                        int id;
                        cout << "Nhap ID san pham can xem thong tin: ";
                        cin >> id;
                        cin.ignore();
                        int index = findProductById(products, id);
                        if (index != -1) {
                            products[index].hienthitt();
                        } else {
                            cout << "San pham khong ton tai.\n";
                        }
                        break;
                    }
                    case 2: {
                        string name;
                        cout << "Nhap ten san pham can xem thong tin: ";
                        getline(cin, name);
                        int index = findProductByName(products, name);
                        if (index != -1) {
                            products[index].hienthitt();
                        } else {
                            cout << "San pham khong ton tai.\n";
                        }
                        break;
                    }
                    default:
                        cout << "Lua chon khong hop le.\n";
                        break;
                }
                break;
            }
            case 8:
                cout << "Thoat chuong trinh.\n";
                break;
            default:
                cout << "Lua chon khong hop le. Vui long chon lai.\n";
                break;
        }
    } while (choice != 8);

    return 0;
}
