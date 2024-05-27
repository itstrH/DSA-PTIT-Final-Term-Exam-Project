#include <iostream>
#include <iomanip>
using namespace std;

struct Student {
  string name, surname, id;
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

void printStudent(Student s) {
  cout << "--------------------------------\n";
  cout << "ID : " << s.id << endl;
  cout << "Ho ten :" << s.surname << " " << s.name << endl;
  cout << "GPA : " << fixed << setprecision(2) << s.gpa << endl; 
  cout << "--------------------------------\n";
}

void inds(sv a){
	cout << "Danh sach sinh vien :\n";
	while(a != NULL){
		printStudent(a->s);
		a = a->next;
	}
	cout << endl;
}
 
void sapxep(sv &a){
	for(sv p = a; p->next != NULL; p = p->next){
		sv min = p;
		for(sv q = p->next; q != NULL; q = q->next){
			if(q->s.gpa < min->s.gpa){
				min = q;
			}
		}
		Student tmp = min->s;
		min->s = p->s;
		p->s = tmp;
	}
}

int main(){
	sv head = NULL;
	while(1){
		cout << "-----------------MENU---------------\n";
		cout << "1. Chen sinh vien vao dau danh sach\n";
		cout << "2. Chen sinh vien vao cuoi danh sach\n";
		cout << "3. Chen sinh vien vao giua danh sach\n";
		cout << "4. Xoa phan tu o dau\n";
		cout << "5. Xoa phan tu o cuoi\n";
		cout << "6. Xoa phan tu o giua\n";
		cout << "7. Duyet danh sach lien ket\n";
		cout << "8. Sap xep cac sinh vien trong dslk\n";
		cout << "0. Thoat !\n";
		cout << "-------------------------------------\n";
		cout << "Nhap lua chon :";
		int lc; cin >> lc;
		cout<<endl;
		if(lc == 1){
			insertFirst(head);
		}
		else if(lc == 2){
			insertLast(head);
		}
		else if(lc == 3){
			int pos; cout << "Nhap vi tri can chen :"; cin >> pos;
			insertMiddle(head, pos);
		}
		else if(lc == 4){
			deleteFirst(head);
		}
		else if(lc == 5){
			deleteLast(head);
		}
		else if(lc == 6){
			int pos; cout << "Nhap vi tri can xoa:"; cin >> pos;
			deleteMiddle(head, pos);
		}
		else if(lc == 7){
			inds(head);
		}
		else if(lc == 8){
			sapxep(head);
		}
		else if(lc == 0){
			break;
		}
	}
	return 0;
}
