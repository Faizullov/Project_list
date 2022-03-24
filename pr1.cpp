#include <iostream>

using namespace std;


class Bank {
    int number;
    char *owner = NULL;
    char *date = NULL;
    int balance;
    public:
    Bank();
    Bank(const int , const char*, const char*, const int);
    ~Bank();
    Bank & operator = (const Bank & y);
    void get_all () const;
};

Bank::Bank (){
    number = 0;
    balance = 0;
    owner = NULL;
    date = NULL;
}

Bank & Bank :: operator = (const Bank & y){
    if (this == &y){
        return *this;
    }
    number = y.number;
    balance = y.balance;
    delete [] owner;
    int i = 0, cnt = 1;
    while (y.owner[i] != '\0'){
        cnt ++;
        i++;
    }
    i = 0;
    owner = new char[cnt];
    while (cnt != 0){
        cnt --;
        owner[i] = y.owner[i];
        i++;
    }
    delete [] date;
    i = 0;
    cnt = 1;
    while (y.date[i] != '\0'){
        cnt ++;
        i++;
    }
    i = 0;
    date = new char[cnt];
    while (cnt != 0){
        cnt --;
        date[i] = y.date[i];
        i++;
    }
    return *this;
}

void Bank::get_all() const{
    cout << "-----------------\n";
    cout << "Info:" << endl;
    cout << "number " << number << endl;
    cout << "owner " << owner << endl;
    cout << "date " << date << endl;
    cout << "balance " << balance << endl;
    cout << "-----------------\n";
}

Bank::Bank(const int num, const char *own, const char *dat, const int balanc){
    number = num;
    delete [] owner;
    int i = 0, cnt = 1;
    while (own[i] != '\0'){
        cnt ++;
        i++;
    }
    i = 0;
    owner = new char[cnt];
    while (cnt != 0){
        cnt --;
        owner[i] = own[i];
        i++;
    }
    delete [] date;
    i = 0, cnt= 1;
    while (dat[i] != '\0'){
        cnt ++;
        i++;
    }
    i = 0;
    date = new char[cnt];
    while (cnt != 0){
        cnt --;
        date[i] = dat[i];
        i++;
    }
    balance = balanc;
    cout << owner << " " << date << " ";
    cout << "Created!" << endl;
}

Bank::~Bank(){
    delete []owner;
    delete []date;
}

struct Element{
    Bank profile;
    Element *next;
    Element *prev;
};

class List{
    Element *node;
    public:
    List();
    ~List();
    void copy(List *x, const List *y);
    void push_front (const Bank &);
    Element * front();
    void push_back (const Bank &);
    Element * back();
    void pop_front();
    void pop_back();
    void insert(int n, const Bank &);
    void erase (int n);
    void print();
    void empty();
};

void List :: empty (){
    if (node == NULL){
        cout << "EMPTY!\n";
    } else {
        cout << "NOT EMPTY!\n";
    }
}

void List :: erase (int n){
    while (node->prev != NULL){
        node = node->prev;
    }
    int cnt = 1;
    while (cnt < n){
        cnt++;
        node = node->next;
    }
    if (n != 1){
        Element *save1;
        save1 = node->next;
        Element *save2;
        save2 = node;
        node = node -> prev;
        node -> next = save1;
        save1 -> prev = node;
        delete save2; 
    } else {
        Element *save1;
        save1 = node->next;
        Element *save2;
        save2 = node;
        node = node->next;
        save1 -> prev = NULL;
        delete save2;
    }
}

void List :: print(){
    while (node->prev != NULL){
        node = node->prev;
    }
    while (node->next != NULL){
        this->node->profile.get_all();
        node = node->next;
    }
    this->node->profile.get_all();
}

void List :: insert(int n, const Bank & y){
    while (node->prev != NULL){
        node = node->prev;
    }
    //cout << "CHECK!!!\n";
    int cnt = 1;
    while (cnt < n){
        cnt++;
        node = node->next;
    }
    // cout << "CHECK!!!\n";
    Element *help;
    help = node;
    if (n == 1){
        node = node -> prev;
        node = new Element;
        node -> next = help;
        help -> prev = node;
        node -> prev = NULL;
        node ->profile = y;
    } else {
        Element *save;
        save = node->prev;
        help = new Element;
        help->profile = y;
        node -> prev = help;
        help -> next = node;
        save -> next = help;
        help -> prev = save;
    }
    //cout << "CHECK!!!\n";
} 

void List :: pop_back (){
    Element *save;
    save = node;
    while (save->prev != NULL){
        node = save;
        save = save->prev;
    }
    node->prev = NULL;
    delete save;
}

void List :: pop_front(){
    Element *save;
    save = node;
    while (save->next != NULL){
        node = save;
        save = save->next;
    }
    node->next = NULL;
    delete save;
}

Element * List :: front(){
    while (node->next != NULL){
        node = node->next;
    }
    return node;
}

Element * List :: back(){
    while (node->prev != NULL){
        node = node->prev;
    }
    return node;
}

List :: ~List(){
    while (node->prev != NULL){
        node = node->prev;
    }
    while (node->next != NULL){
        Element *save;
        save = node;
        node = node->next;
        delete save;
    }
    delete node;
}

List :: List(){
    node = NULL;
}

void List:: push_front (const Bank & note1){  // из-за & не вызывается деструктор
    Element *save;
    if (node == NULL){
        node = new Element;
        node->next = NULL;
        node->prev = NULL;
        node->profile = note1;
    } else {
    while (node->next != NULL){
        node = node->next;
    }
        save = node;
        node = node->next;
        node = new Element;
        node->profile = note1;
        node->next = NULL;
        node->prev = save;
        save->next = node;
    }
} 

void List:: push_back (const Bank & note1){  // из-за & не вызывается деструктор
    Element *save;
    if (node == NULL){
        node = new Element;
        node->next = NULL;
        node->prev = NULL;
        node->profile = note1;
    } else {
    while (node->prev != NULL){
        node = node->prev;
    }
        save = node;
        node = node->prev;
        node = new Element;
        node->profile = note1;
        node->prev = NULL;
        node->next = save;
        save->prev = node;
    }
} 

class Object: List {
    void empty1(){
        
    }
};

int main(){
    Bank Vasya(1, "Vasya", "22.02.2022", 100);
    Bank Petya(2, "Petya", "23.03.2023", 250);
    Bank Kolya(3, "Kolya", "26.07.2025", 550);
    Bank Masha(4, "Masha", "25.08.2026", 750);
    Bank Sasha(5, "Sasha", "01.01.2027", 1000);
    List lst;
    Element *test;
    lst.empty();
    lst.push_front(Petya);
    lst.push_front(Masha);
    lst.push_back(Vasya);
    lst.push_front(Sasha);
    lst.push_back(Kolya);
    test = lst.front();
    test->profile.get_all();
    test = lst.back();
    test->profile.get_all();
    lst.pop_front();
    lst.pop_back();
    lst.print();
    lst.insert(1, Sasha);
    lst.erase(1);
    cout << " QQQQQ\n";
    lst.print();
    lst.empty();
    
    cout << "AIRAT\n";
    Object obj1;
    return 0;
}