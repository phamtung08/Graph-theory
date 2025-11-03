#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

class DoThi {
private:
    int soDinh; 
    vector<vector<int>> maTranKe;
    bool laDoThiCoHuong;
    
public:
    DoThi() : soDinh(0), laDoThiCoHuong(false) {}
    
    void nhapDuLieu() {
        cout << endl << "=== NHAP DU LIEU DO THI ===" << endl;
        cout << "Nhap so dinh cua do thi: ";
        cin >> soDinh;
        
        if (soDinh <= 0) {
            cout << "So dinh khong hop le!" << endl;
            soDinh = 0;
            return;
        }
        
        maTranKe.resize(soDinh, vector<int>(soDinh));
        
        cout << "Nhap ma tran ke (moi dong cach nhau boi dau cach):" << endl;
        for (int i = 0; i < soDinh; i++) {
            cout << "Dong " << i + 1 << ": ";
            for (int j = 0; j < soDinh; j++) {
                cin >> maTranKe[i][j];
            }
        }
        
        phatHienLoaiDoThi();
    }
    
    void xuatDuLieu() {
        if (soDinh == 0) {
            cout << "Do thi chua duoc khoi tao!" << endl;
            return;
        }
        
        cout << endl << "=== MA TRAN KE CUA DO THI ===" << endl;
        cout << "So dinh: " << soDinh << endl;
        cout << "Loai: " << (laDoThiCoHuong ? "Do thi co huong" : "Do thi vo huong") << endl << endl;
        
        cout << "    ";
        for (int i = 0; i < soDinh; i++) {
            cout << setw(4) << i;
        }
        cout << endl;
        
        for (int i = 0; i < soDinh; i++) {
            cout << setw(4) << i;
            for (int j = 0; j < soDinh; j++) {
                cout << setw(4) << maTranKe[i][j];
            }
            cout << endl;
        }
    }
    
    bool kiemTraHopLe() {
        if (soDinh == 0) return false;
        
        for (int i = 0; i < soDinh; i++) {
            for (int j = 0; j < soDinh; j++) {
                if (maTranKe[i][j] < 0) {
                    return false;
                }
            }
        }
        return true;
    }
    
    void phatHienLoaiDoThi() {
        if (!kiemTraHopLe()) {
            cout << "Ma tran khong hop le!" << endl;
            return;
        }
        
        laDoThiCoHuong = false;
        for (int i = 0; i < soDinh; i++) {
            for (int j = 0; j < soDinh; j++) {
                if (maTranKe[i][j] != maTranKe[j][i]) {
                    laDoThiCoHuong = true;
                    return;
                }
            }
        }
    }
    
    void phanLoaiDoThi() {
        cout << endl << "=== PHAN LOAI DO THI ===" << endl;
        if (!kiemTraHopLe()) {
            cout << "Ma tran khong hop le! Chua gia tri am." << endl;
            return;
        }
        
        cout << "Ma tran hop le!" << endl;
        cout << "Loai do thi: " << (laDoThiCoHuong ? "Do thi co huong" : "Do thi vo huong") << endl;
    }
    
    int demSoCanh() {
        int soCanh = 0;
        for (int i = 0; i < soDinh; i++) {
            for (int j = 0; j < soDinh; j++) {
                soCanh += maTranKe[i][j];
            }
        }
        
        if (!laDoThiCoHuong) {
            soCanh /= 2;
        }
        return soCanh;
    }
    
    int layBac(int dinh) {
        int bac = 0;
        for (int j = 0; j < soDinh; j++) {
            bac += maTranKe[dinh][j];
        }
        return bac;
    }
    
    int layBacVao(int dinh) {
        int bacVao = 0;
        for (int i = 0; i < soDinh; i++) {
            bacVao += maTranKe[i][dinh];
        }
        return bacVao;
    }
    
    int layBacRa(int dinh) {
        int bacRa = 0;
        for (int j = 0; j < soDinh; j++) {
            bacRa += maTranKe[dinh][j];
        }
        return bacRa;
    }
    
    void hienThiThongTinDoThi() {
        if (soDinh == 0) {
            cout << "Do thi chua duoc khoi tao!" << endl;
            return;
        }
        
        cout << endl << "=== THONG TIN DO THI ===" << endl;
        cout << "So dinh: " << soDinh << endl;
        cout << "So canh: " << demSoCanh() << endl << endl;
        
        if (laDoThiCoHuong) {
            cout << "BAC CUA CAC DINH (Do thi co huong):" << endl;
            cout << setw(8) << "Dinh" << setw(12) << "Bac vao" 
                 << setw(12) << "Bac ra" << setw(12) << "Tong bac" << endl;
            cout << string(44, '-') << endl;
            
            for (int i = 0; i < soDinh; i++) {
                int bacVao = layBacVao(i);
                int bacRa = layBacRa(i);
                cout << setw(8) << i << setw(12) << bacVao 
                     << setw(12) << bacRa << setw(12) << (bacVao + bacRa) << endl;
            }
        } else {
            cout << "BAC CUA CAC DINH (Do thi vo huong):" << endl;
            cout << setw(8) << "Dinh" << setw(12) << "Bac" << endl;
            cout << string(20, '-') << endl;
            
            for (int i = 0; i < soDinh; i++) {
                cout << setw(8) << i << setw(12) << layBac(i) << endl;
            }
        }
    }
    
    void timDinhDacBiet() {
        if (soDinh == 0) {
            cout << "Do thi chua duoc khoi tao!" << endl;
            return;
        }
        
        cout << endl << "=== CAC DINH DAC BIET ===" << endl;
        
        vector<int> dinhCoLap;
        vector<int> dinhTreo;
        
        for (int i = 0; i < soDinh; i++) {
            int bac;
            if (laDoThiCoHuong) {
                bac = layBacVao(i) + layBacRa(i);
            } else {
                bac = layBac(i);
            }
            
            if (bac == 0) {
                dinhCoLap.push_back(i);
            } else if (bac == 1) {
                dinhTreo.push_back(i);
            }
        }
        
        cout << "Dinh co lap (bac = 0): ";
        if (dinhCoLap.empty()) {
            cout << "Khong co" << endl;
        } else {
            for (int dinh : dinhCoLap) {
                cout << dinh << " ";
            }
            cout << endl;
        }
        
        cout << "Dinh treo (bac = 1): ";
        if (dinhTreo.empty()) {
            cout << "Khong co" << endl;
        } else {
            for (int dinh : dinhTreo) {
                cout << dinh << " ";
            }
            cout << endl;
        }
    }
    
    void xuLyTatCa() {
        xuatDuLieu();
        phanLoaiDoThi();
        hienThiThongTinDoThi();
        timDinhDacBiet();
    }
};

void hienThiMenu() {
    cout << endl;
    cout << "========================================" << endl;
    cout << "  CHUONG TRINH QUAN LY DO THI" << endl;
    cout << "========================================" << endl;
    cout << "1. Nhap du lieu do thi" << endl;
    cout << "2. Xuat ma tran ke" << endl;
    cout << "3. Phan loai do thi" << endl;
    cout << "4. Hien thi thong tin do thi" << endl;
    cout << "5. Tim dinh dac biet" << endl;
    cout << "6. Xu ly tat ca thong tin" << endl;
    cout << "0. Thoat chuong trinh" << endl;
    cout << "========================================" << endl;
    cout << "Nhap lua chon: ";
}

int main() {
    DoThi doThi;
    int luaChon;
    
    do {
        hienThiMenu();
        cin >> luaChon;
        
        switch (luaChon) {
            case 1:
                doThi.nhapDuLieu();
                break;
            case 2:
                doThi.xuatDuLieu();
                break;
            case 3:
                doThi.phanLoaiDoThi();
                break;
            case 4:
                doThi.hienThiThongTinDoThi();
                break;
            case 5:
                doThi.timDinhDacBiet();
                break;
            case 6:
                doThi.xuLyTatCa();
                break;
            case 0:
                cout << endl << "Cam on ban da su dung chuong trinh!" << endl;
                break;
            default:
                cout << endl << "Lua chon khong hop le! Vui long chon lai." << endl;
        }
    } while (luaChon != 0);
    
    return 0;
}