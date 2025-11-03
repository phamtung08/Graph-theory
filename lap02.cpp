#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <queue>
using namespace std;

#define MAX 100

struct GRAPH {
    int sodinh;
    int A[MAX][MAX]; 
};

int visited[MAX];
int nSoMienLienThong = 0;

void visit(GRAPH &g, int i, int nLabel)
{
    int queue[MAX];     
    int queuecount = 1;  
    int queueindex = 0; 
    int x;              
    queue[0] = i;        
    visited[i] = nLabel;
    while (queueindex < queuecount)
    {
        x = queue[queueindex];
        queueindex++;
        for (int j = 0; j < g.sodinh; j++)
        {
            if ((visited[j] == 0) && (g.A[x][j] != 0))
            {
                queue[queuecount] = j;
                queuecount++;
                visited[j] = nLabel;
            }
        }
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
        cout << "Không mở được file để ghi!" << endl;
        return;
    }
    if (nSoMienLienThong == 1)
        fo << "LIÊN THÔNG" << endl;
    else
        fo << "KHÔNG LIÊN THÔNG" << endl;
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
        fo << "Cần thêm tối thiểu " << canThem << " cạnh để đồ thị liên thông." << endl;
        fo << "Các cạnh cần thêm: " << endl;
        for (int i = 1; i < nSoMienLienThong; i++) {
            int u = thanhphan[i][0];
            int v = thanhphan[i + 1][0];
            fo << "(" << u << ", " << v << ")" << endl;
        }
    }
    fo.close();
    cout << "Đã ghi kết quả vào file '" << filename << "'." << endl;
}

void NhapMaTranKe(GRAPH &g) {
    cout << "Nhập số đỉnh: ";
    cin >> g.sodinh;
    cout << "Nhập ma trận kề (" << g.sodinh << "x" << g.sodinh << "):\n";
    for (int i = 0; i < g.sodinh; i++)
        for (int j = 0; j < g.sodinh; j++)
            cin >> g.A[i][j];
}

int main() {
    GRAPH g;
    NhapMaTranKe(g);
    XetLienThong(g);
    InRaFile(g, "ketqua_lap02.txt");
    return 0;
}
