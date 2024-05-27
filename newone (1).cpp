#include <iostream>
#include <iomanip>
#include <ctime>
#include <algorithm>
using namespace std;

struct Student {
    string name, surname, id, lop;
    double gpa;
};

struct SV {
    Student s;
    SV* prev;
    SV* next;
};

typedef SV* sv;

sv makeNode() {
    Student s;
    cout << "Nhap thong tin sinh vien :\n";
    cout << "Nhap ID :"; cin >> s.id;
    cout << "Nhap ho :"; cin >> s.surname;
    cout << "Nhap ten :"; cin.ignore();
    getline(cin, s.name);
    cout << "Nhap lop :"; cin >> s.lop;
    cout << "Nhap gpa :"; cin >> s.gpa;
    sv tmp = new SV();
    tmp->s = s;
    tmp->next = NULL;
    tmp->prev = NULL;
    return tmp;
}








bool isEmpty(sv a) {
    return a == NULL;
}

int Size(sv a) {
    int cnt = 0;
    while (a != NULL) {
        ++cnt;
        a = a->next;
    }
    return cnt;
}

void insertFirst(sv &a) {
    sv tmp = makeNode();
    if (isEmpty(a)) {
        a = tmp;
    } else {
        tmp->next = a;
        a->prev = tmp;
        a = tmp;
    }
}

void insertLast(sv &a) {
    sv tmp = makeNode();
    if (isEmpty(a)) {
        a = tmp;
    } else {
        sv p = a;
        while (p->next != NULL) {
            p = p->next;
        }
        p->next = tmp;
        tmp->prev = p;
    }
}

void insertMiddle(sv &a, int pos) {
    int n = Size(a);
    if (pos <= 0 || pos > n + 1) {
        cout << "Vi tri chen khong hop le!\n";
        return;
    }
    if (pos == 1) {
        insertFirst(a);
        return;
    } else if (pos == n + 1) {
        insertLast(a);
        return;
    }
    sv p = a;
    for (int i = 1; i < pos; i++) {
        p = p->next;
    }
    sv tmp = makeNode();
    tmp->next = p->next;
    p->next->prev = tmp;
    tmp->prev = p;
    p->next = tmp;
}

void deleteFirst(sv &a) {
    if (isEmpty(a)) return;
    sv tmp = a;
    a = a->next;
    if (a != NULL) {
        a->prev = NULL;
    }
    delete tmp;
}

void deleteLast(sv &a) {
    if (isEmpty(a)) return;
    if (a->next == NULL) {
        delete a;
        a = NULL;
        return;
    }
    sv p = a;
    while (p->next->next != NULL) {
        p = p->next;
    }
    sv tmp = p->next;
    p->next = NULL;
    delete tmp;
}

void deleteMiddle(sv &a, int pos) {
    if (isEmpty(a) || pos <= 0 || pos > Size(a)) return;
    if (pos == 1) {
        deleteFirst(a);
        return;
    }
    sv p = a;
    for (int i = 1; i < pos; i++) {
        p = p->next;
    }
    sv tmp = p->next;
    p->next = tmp->next;
    if (tmp->next != NULL) {
        tmp->next->prev = p;
    }
    delete tmp;
}

void printStudent(Student s, bool highlight = false) {
    cout << "--------------------------------\n";
    cout << "ID : " << s.id << endl;
    cout << "Ho ten :";
    if (highlight) cout << "\033[1;31m"; // bold red
    cout << s.surname << " " << s.name;
    if (highlight) cout << "\033[0m"; // reset color
    cout << endl;
    cout << "Lop : " << s.lop << endl;
    cout << "GPA : " << fixed << setprecision(2) << s.gpa << endl;
    cout << "--------------------------------\n";
}

void printList(sv a) {
    cout << "Danh sach sinh vien :\n";
    while (a != NULL) {
        printStudent(a->s);
        a = a->next;
    }
    cout << endl;
}

void swapStudents(Student& s1, Student& s2) {
    Student temp = s1;
    s1 = s2;
    s2 = temp;
}

void bubbleSort(sv a, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (a[j].s.gpa > a[j + 1].s.gpa) {
                swap(a[j], a[j + 1]);
            }
        }
    }
}

void heapify(sv arr, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left].s.gpa > arr[largest].s.gpa)
        largest = left;

    if (right < n && arr[right].s.gpa > arr[largest].s.gpa)
        largest = right;

    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(sv arr, int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

void merge(sv arr, int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    Student *L = new Student[n1];
    Student *R = new Student[n2];

    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i].s;
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j].s;

    int i = 0, j = 0,k = l;
    while (i < n1 && j < n2) {
        if (L[i].gpa <= R[j].gpa) {
            arr[k].s = L[i];
            i++;
        } else {
            arr[k].s = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k].s = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k].s = R[j];
        j++;
        k++;
    }

    delete[] L;
    delete[] R;
}

void mergeSort(sv arr, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;

        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        merge(arr, l, m, r);
    }
}

int partition(sv arr, int low, int high) {
    double pivot = arr[high].s.gpa;
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (arr[j].s.gpa < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}

void quickSort(sv arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void selectionSort(sv arr, int n) {
    int i, j, minIndex;
    for (i = 0; i < n - 1; i++) {
        minIndex = i;
        for (j = i + 1; j < n; j++) {
            if (arr[j].s.gpa < arr[minIndex].s.gpa)
                minIndex = j;
        }
        swap(arr[minIndex], arr[i]);
    }
}

sv timKiem(sv a, string keyword, int& count, bool& found) {
    sv result = NULL;
    clock_t startTime = clock();
    while (a != NULL) {
        // Chuyển đổi họ tên thành chữ thường 
        string fullName = a->s.surname + " " + a->s.name;
        transform(fullName.begin(), fullName.end(), fullName.begin(), ::tolower);
        transform(keyword.begin(), keyword.end(), keyword.begin(), ::tolower);

        if (fullName.find(keyword) != string::npos) {
            // Tìm thấy sinh viên
            if (!found) {
                cout << "Ket qua tim kiem:\n";
                found = true;
            }
            count++;
            printStudent(a->s, true); // In đậm thông tin sinh viên tìm thấy
            result = a;
        }
        a = a->next;
    }
    clock_t endTime = clock();
    double searchTime = double(endTime - startTime) / CLOCKS_PER_SEC;
    cout << "Thoi gian tim kiem: " << searchTime << " giay\n";
    return result;
}

int main() {
    sv head = NULL;
    
    while (true) {
        cout << "-----------------MENU---------------\n";
        cout << "1. Chen sinh vien vao dau danh sach\n";
        cout << "2. Chen sinh vien vao cuoi danh sach\n";
        cout << "3. Chen sinh vien vao giua danh sach\n";
        cout << "4. Xoa sinh vien o dau\n";
        cout << "5. Xoa sinh vien o cuoi\n";
        cout << "6. Xoa sinh vien o giua\n";
        cout << "7. Duyet danh sach lien ket\n";
        cout << "8. Chon thuat toan sap xep:\n";
        cout << "   a. Bubble Sort\n";
        cout << "   b. Heap Sort\n";
        cout << "   c. Merge Sort\n";
        cout << "   d. Quick Sort\n";
        cout << "   e. Selection Sort\n";
        cout << "9. Tim kiem sinh vien\n";
        cout << "0. Thoat !\n";
        cout << "-------------------------------------\n";
        cout << "Nhap lua chon :";
        int lc; cin >> lc;
        cout << endl;
        if (lc == 1) {
            insertFirst(head);
        } else if (lc == 2) {
            insertLast(head);
        } else if (lc == 3) {
            int pos; cout << "Nhap vi tri can chen :"; cin >> pos;
            insertMiddle(head, pos);
        } else if (lc == 4) {
            deleteFirst(head);
        } else if (lc == 5) {
            deleteLast(head);
        } else if (lc == 6) {
            int pos; cout << "Nhap vi tri can xoa:"; cin >> pos;
            deleteMiddle(head, pos);
        } else if (lc == 7) {
            printList(head);
        } else if (lc == 8) {
            int n = Size(head);
            sv arr = new SV[n];
            for (int i = 0; i < n; i++) {
                arr[i] = *head;
                head = head->next;
            }
            int sortChoice; 
            cout << "Chon thuat toan sap xep (a-e): ";
            char sortAlgorithm; 
            cin >> sortAlgorithm;
            switch (sortAlgorithm) {
                case 'a':
                    bubbleSort(arr, n);
                    break;
                case 'b':
                    heapSort(arr, n);
                    break;
                case 'c':
                    mergeSort(arr, 0, n - 1);
                    break;
                case 'd':
                    quickSort(arr, 0, n - 1);
                    break;
                case 'e':
                    selectionSort(arr, n);
                    break;
                default:
                    cout << "Lua chon khong hop le!\n";
                    cout << "Danh sach sau khi sap xep:\n";
            }
            for (int i = 0; i < n; i++) {
                printStudent(arr[i].s);
            }
            delete[] arr;
        } else if (lc == 9) {
            string keyword;
            cout << "Nhap tu khoa can tim kiem: ";
            cin.ignore(); 
            getline(cin, keyword);
            int count = 0;
            bool found = false;
            sv result = timKiem(head, keyword, count, found);
            if (!found) {
                cout << "Khong tim thay sinh vien nao phu hop!\n";
            } else {
                char choice;
                cout << "Ban muon xuat dao nguoc ho va ten khong?";
                cout << "y/n: ";
                cin >> choice;
                if (choice == 'y' || choice == 'Y') {
                    string reverseName = result->s.name;
                    reverse(reverseName.begin(), reverseName.end());
                    string reverseSurname = result->s.surname;
                    reverse(reverseSurname.begin(), reverseSurname.end());
                    cout << "Chuoi dao nguoc ho va ten: " << reverseName << " " << reverseSurname << endl;
                }
            }
        } else if (lc == 0) {
            break;
        }
    }
    return 0;
}

