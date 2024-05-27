#include <iostream>
#include <iomanip>
#include <ctime>
#include <algorithm>
using namespace std;

struct Student{
	string name, surname, id, lop;
	double gpa;
};
 
struct SV{
	Student s;
	SV *next;
};
 
typedef struct SV* sv;
 
sv makeNode(){
	Student s;
	cout << "Nhap thong tin sinh vien :\n";
	cout << "Nhap ID :"; cin >> s.id;
	cout << "Nhap ho :"; cin >> s.surname;
	cout << "Nhap ten :"; cin.ignore();
	getline(cin, s.name);
	cout << "Nhap lop: "; cin >> s.lop;
	cout << "Nhap gpa :"; cin >> s.gpa;
	sv tmp = new SV();
	tmp->s = s;
	tmp->next = NULL;
	return tmp;
}

bool empty(sv a){
	return a == NULL;
}
 
int Size(sv a){
	int cnt = 0;
	while(a != NULL){
		++cnt;
		a = a->next; 
	}
	return cnt;
}
 
void insertFirst(sv &a){
	sv tmp = makeNode();
	if(a == NULL){
		a = tmp;
	}
	else{
		tmp->next = a;
		a = tmp;
	}
}
 
void insertLast(sv &a){
	sv tmp = makeNode();
	if(a == NULL){
		a = tmp;
	}
	else{
		sv p = a;
		while(p->next != NULL){
			p = p->next;
		}
		p->next = tmp;
	}
}
 
void insertMiddle(sv &a,int pos){
	int n = Size(a);
	if(pos <= 0 || pos > n + 1){
		cout << "Vi tri chen khong hop le !\n"; return;
	}
	if(pos == 1){
		insertFirst(a); return;
	}
	else if(pos == n + 1 ){
		insertLast(a); return;
	}
	sv p = a;
	for(int i = 1; i < pos - 1; i++){
		p = p->next;
	}
	sv tmp = makeNode();
	tmp->next = p->next;
	p->next = tmp;
}
 
void deleteFirst(sv &a){
	if(a == NULL) return;
	a = a->next;
}
 
void deleteLast(sv &a){
	if(a == NULL) return;
	sv truoc = NULL, sau = a;
	while(sau->next != NULL){
		truoc = sau;
		sau = sau->next;
	}
	if(truoc == NULL){
		a = NULL;
	}
	else{
		truoc->next = NULL;
	}
}

void deleteMiddle(sv &a, int pos){
	if(pos <=0 || pos > Size(a)) return;
	sv truoc = NULL, sau = a;
	for(int i = 1; i < pos; i++){
		truoc = sau;
		sau = sau->next;
	}
	if(truoc == NULL){
		a = a->next;
	}
	else{
		truoc->next = sau->next;
	}
}
 
void printStudent(Student s, const string& keyword = "") {
    string id = s.id;
    string surname = s.surname;
    string name = s.name;
    string lop = s.lop;
    string gpa = to_string(s.gpa);

    auto highlight = [&](const string& text) {
        if (keyword.empty()) return text;
        string lowerText = text;
        transform(lowerText.begin(), lowerText.end(), lowerText.begin(), ::tolower);
        string lowerKeyword = keyword;
        transform(lowerKeyword.begin(), lowerKeyword.end(), lowerKeyword.begin(), ::tolower);
        if (lowerText.find(lowerKeyword) != string::npos) {
            return "\033[1;31m" + text + "\033[0m"; // Highlight in red
        }
        return text;
    };

    cout << "--------------------------------\n";
    cout << "ID : " << highlight(id) << endl;
    cout << "Ho ten : " << highlight(surname) << " " << highlight(name) << endl;
    cout << "Lop : " << highlight(lop) << endl;
    cout << "GPA : " << fixed << setprecision(2) << highlight(gpa) << endl;
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

void bubbleSort(SV* arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j].s.gpa > arr[j + 1].s.gpa) {
                swapStudents(arr[j].s, arr[j + 1].s);
            }
        }
    }
}

void heapify(SV* arr, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left].s.gpa > arr[largest].s.gpa)
        largest = left;

    if (right < n && arr[right].s.gpa > arr[largest].s.gpa)
        largest = right;

    if (largest != i) {
        swapStudents(arr[i].s, arr[largest].s);
        heapify(arr, n, largest);
    }
}

void heapSort(SV* arr, int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    for (int i = n - 1; i > 0; i--) {
        swapStudents(arr[0].s, arr[i].s);
        heapify(arr, i, 0);
    }
}

void merge(SV* arr, int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    Student* L = new Student[n1];
    Student* R = new Student[n2];

    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i].s;
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j].s;

    int i = 0, j = 0, k = l;
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

void mergeSort(SV* arr, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;

        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        merge(arr, l, m, r);
    }
}

int partition(SV* arr, int low, int high) {
    double pivot = arr[high].s.gpa;
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (arr[j].s.gpa < pivot) {
            i++;
            swapStudents(arr[i].s, arr[j].s);
        }
    }
    swapStudents(arr[i + 1].s, arr[high].s);
    return (i + 1);
}

void quickSort(SV* arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void selectionSort(SV* arr, int n) {
    int i, j, minIndex;
    for (i = 0; i < n - 1; i++) {
        minIndex = i;
        for (j = i + 1; j < n; j++) {
            if (arr[j].s.gpa < arr[minIndex].s.gpa) {
                minIndex = j;
            }
        }
        swapStudents(arr[minIndex].s, arr[i].s);
    }
}

void insertionSort(SV* arr, int n) {
    for (int i = 1; i < n; i++) {
        Student key = arr[i].s;
        int j = i - 1;
        while (j >= 0 && arr[j].s.gpa > key.gpa) {
            arr[j + 1].s = arr[j].s;
            j--;
        }
        arr[j + 1].s = key;
    }
}

sv timKiem(sv a, const string& keyword, int criteria, int& count, bool& found) {
    sv result = NULL;
    clock_t startTime = clock();
    while (a != NULL) {
        // Convert to lowercase for case-insensitive comparison
        string lowerKeyword = keyword;
        transform(lowerKeyword.begin(), lowerKeyword.end(), lowerKeyword.begin(), ::tolower);
        
        string id = a->s.id;
        string surname = a->s.surname;
        string name = a->s.name;
        string lop = a->s.lop;
        string gpa = to_string(a->s.gpa);
        
        auto containsIgnoreCase = [](const string& text, const string& keyword) {
            string lowerText = text;
            transform(lowerText.begin(), lowerText.end(), lowerText.begin(), ::tolower);
            return lowerText.find(keyword) != string::npos;
        };
        
        bool match = false;
        switch (criteria) {
            case 1: match = containsIgnoreCase(id, lowerKeyword); break;
            case 2: match = containsIgnoreCase(surname, lowerKeyword); break;
            case 3: match = containsIgnoreCase(name, lowerKeyword); break;
            case 4: match = containsIgnoreCase(lop, lowerKeyword); break;
            case 5: match = containsIgnoreCase(gpa, lowerKeyword); break;
            default: break;
        }
        
        if (match) {
            if (!found) {
                cout << "Ket qua tim kiem:\n";
                found = true;
            }
            count++;
            printStudent(a->s, keyword); // Print student information with highlight
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
        cout << "4. Xoa phan tu o dau\n";
        cout << "5. Xoa phan tu o cuoi\n";
        cout << "6. Xoa phan tu o giua\n";
        cout << "7. Duyet danh sach lien ket\n";
        cout << "8. Chon thuat toan sap xep:\n";
        cout << "   a. Bubble Sort\n";
        cout << "   b. Heap Sort\n";
        cout << "   c. Merge Sort\n";
        cout << "   d. Quick Sort\n";
        cout << "   e. Selection Sort\n";
        cout << "   f. Insertion Sort\n";
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
            SV* arr = new SV[n];
            sv temp = head;
            for (int i = 0; i < n; i++) {
                arr[i] = *temp;
                temp = temp->next;
            }
            char sortAlgorithm; 
            cout << "Chon thuat toan sap xep (a-f): ";
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
                case 'f':
                    insertionSort(arr, n);
                    break;
                default:
                    cout << "Lua chon khong hop le!\n";
                    delete[] arr;
                    continue;
            }
            cout << "Danh sach sau khi sap xep:\n";
            for (int i = 0; i < n; i++) {
                printStudent(arr[i].s);
            }
            delete[] arr;
        } else if (lc == 9) {
            cout << "Chon tieu chi tim kiem:\n";
            cout << "1. Ma sinh vien\n";
            cout << "2. Ho\n";
            cout << "3. Ten\n";
            cout << "4. Lop\n";
            cout << "5. Diem\n";
            int criteria;
            cout << "Nhap lua chon: ";
            cin >> criteria;
            cout << "Nhap tu khoa can tim kiem: ";
            cin.ignore();
            string keyword;
            getline(cin, keyword);

            int count = 0;
            bool found = false;
            sv result = timKiem(head, keyword, criteria, count, found);
            if (!found) {
                cout << "Khong tim thay sinh vien nao phu hop!\n";
            } else {
                char choice;
                cout << "Ban muon xuat dao nguoc ho va ten khong? (y/n): ";
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