#include <iostream>

using namespace std;

const int MAXN = 10;

int KICHTHUOC;
int Banco[MAXN][MAXN];
int a[] = {2, 1, -1, -2, -2, -1, 1, 2};
int b[] = {1, 2, 2, 1, -1, -2, -2, -1};

void tryK(int n, int x, int y, bool &q) {
    int k = -1, u, v;
    do {
        k++;
        q = false;
        u = x + a[k];
        v = y + b[k];
        if (u >= 0 && u < KICHTHUOC && v >= 0 && v < KICHTHUOC && Banco[u][v] == 0) {
            Banco[u][v] = n;
            if (n < KICHTHUOC * KICHTHUOC) {
                tryK(n + 1, u, v, q);
                if (!q)
                    Banco[u][v] = 0;
            } else
                q = true;
        }
    } while (!q && k < 7);
}

int main() {
    cout << "Nhap kich thuoc ban co: ";
    cin >> KICHTHUOC;

    int x , y;
    cout << "Nhap vi tri xuat phat cua con ma (u, v): ";
    cin >> x >> y;

    bool q = false;
    Banco[x][y] = 1;
    tryK(2,x,y,q);
    if (q) {
        cout << "Cac buoc di cua con ma:" << endl;
        for (int i = 0; i < KICHTHUOC; i++) {
            for (int j = 0; j < KICHTHUOC; j++) {
                cout << Banco[i][j] << "\t";
            }
            cout << endl;
        }
    } else {
        cout << "Khong co loi giai." << endl;
    }
    return 0;
}
