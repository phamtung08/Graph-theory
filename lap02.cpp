#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
using namespace std;

#define MAX 100

struct GRAPH {
    int sodinh;
    int A[MAX][MAX]; 
};

int visited[MAX];
int nSoMienLienThong = 0;


void visit(GRAPH &g, int i, int nLabel) {
    visited[i] = nLabel; 
    for (int j = 0; j < g.sodinh; j++) {
        if (visited[j] == 0 && g.A[i][j] != 0)
            visit(g, j, nLabel);
    }
}

void XetLienThong(GRAPH &g) {
    for (int i = 0; i < g.sodinh; i++)
        visited[i] = 0;
    nSoMienLienThong = 0;

    for (int i = 0; i < g.sodinh; i++)
        if (visited[i] == 0)
            visit(g, i, ++nSoMienLienThong);
}

void InRaFile(GRAPH g, const string &filename) {
    ofstream fo(filename);
    if (!fo) {
        cout << "Khong mo duoc file de ghi!" << endl;
        return;
    }

    if (nSoMienLienThong == 1)
        fo << "LIEN THONG" << endl;
    else
        fo << "KHONG LIEN THONG" << endl;

    fo << nSoMienLienThong << endl;

    vector<vector<int>> thanhphan(nSoMienLienThong + 1);
    for (int i = 0; i < g.sodinh; i++)
        thanhphan[visited[i]].push_back(i);

    for (int i = 1; i <= nSoMienLienThong; i++) {
        for (int v : thanhphan[i])
            fo << v << " ";
        fo << endl;
    }

    if (nSoMienLienThong > 1) {
        int canThem = nSoMienLienThong - 1;
        fo << "Can them toi thieu " << canThem 
           << " canh de do thi lien thong." << endl;

        fo << "Cac canh can them: " << endl;
        for (int i = 1; i < nSoMienLienThong; i++) {
            int u = thanhphan[i][0];
            int v = thanhphan[i + 1][0];
            fo << "(" << u << ", " << v << ")" << endl;
        }
    }

    fo.close();
    cout << "Da ghi ket qua vao file '" << filename << "'." << endl;
}

void NhapMaTranKe(GRAPH &g) {
    cout << "Nhap so dinh: ";
    cin >> g.sodinh;

    cout << "Nhap ma tran ke (" << g.sodinh << "x" << g.sodinh << "):\n";
    for (int i = 0; i < g.sodinh; i++)
        for (int j = 0; j < g.sodinh; j++)
            cin >> g.A[i][j];
}

int main() {
    GRAPH g;
    NhapMaTranKe(g);

    XetLienThong(g);
    InRaFile(g, "ketqua.txt");

    return 0;
}
