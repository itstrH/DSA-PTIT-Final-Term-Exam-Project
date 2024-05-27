#include <iostream>
#include <string>
#include <vector>
using namespace std;

class SV 
{
    private:
        string id;
        string name;
        string inClass;

    public:
        SV(){}
        SV(string msv, string ten, string lop) : id(msv), name(ten), inClass(lop) {}
        void addStudent();
        void delStudent(string msv);
        void editStudent(string msv);
        void showStudent();
        void setName(string ten)
        {
            name = ten;
        }
        
        void setInclass(string lop)
        {
            inClass = lop;
        }

};

vector<SV> listSV;

int main()
{
    int input;
    string id;
    SV st;
    while (true)
    {
        cout << "CHUONG TRINH QUAN LY SINH VIEN\n";
        cout << "CHUC NANG : \n";
        cout << "1. Them thong tin sinh vien.\n";
        cout << "2. Sua thong tin sinh vien.\n";
        cout << "3. Xoa thong tinh sinh vien.\n";
        cout << "4. Dua ra thong tin sinh vien.\n";
        cout << "0. Thoat.\n";
        cout << "Ban chon : " ; 
        cin >> input;

        switch (input)
        {
        case 1:
            cout << "Ban da chon them thong tin sinh vien!\n";
            st.addStudent();
            break;
        case 2:
            cin.ignore(); // ignore roi xuong duoi khong ignore nua
            cout << "Ban da chon sua thong tin sinh vien!\n";
            cout << "Nhap id sinh vien : "; getline(cin, id);
            st.editStudent(id);
            break;
        case 3:
            cout << "Ban da chon xoa thong tin sinh vien!\n";
            cout << "Nhap id sinh vien : "; cin >> id;
            st.delStudent(id);
            break;
        case 4:
            cout << "Ban da chon dua ra thong tin sinh vien!\n";
            st.showStudent();
            break;
        case 0:
            return 0;
        }
    }
}

void SV::addStudent()
{
    string msv, hoTen, lop;
    cin.ignore(32767, '\n');
    cout << "Nhap ma sinh vien: " ; getline(cin, msv);
    cout << "Nhap ten sinh vien: "; getline(cin, hoTen);
    cout << "Nhap lop : "; getline(cin, lop);
    listSV.push_back(SV(msv, hoTen, lop));

}

void SV::showStudent()
{ 
    for (int i=0; i<listSV.size(); i++)
    {
        cout << "MSV : " << listSV[i].id << "     ";
        cout << "Ten SV: " << listSV[i].name << "     ";
        cout << "Lop : " << listSV[i].inClass << endl;
    }
}

void SV::delStudent(string msv)
{
    for (int i=0; i<listSV.size(); i++)
    {
        if (listSV[i].id == msv)
        {
            listSV.erase(listSV.begin() + i);
        }
    }
}

void SV::editStudent(string msv)
{
    for (int i=0; i<listSV.size(); i++)
    {
        if (listSV[i].id == msv)
        {           
            string ten, lop;
            //cin.ignore();
            cout << "Nhap lai ten SV: "; getline(cin, ten);
            cout << "Nhap lai lop SV: "; getline(cin, lop);
            listSV[i].setName(ten);
            listSV[i].setInclass(lop);
        }
        else
            cout << "MSSV khong ton tai!" << endl;
    }
}