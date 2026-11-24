#include <iostream>
#include <string>
using namespace std;
class Address {
    string city; int pin;
public:
    Address(string c,int p):city(c),pin(p){cout<<"Address+ ";}
    ~Address(){cout<<"Address- ";}
    string str() const { return city+"-"+to_string(pin); }
};
class Person {
protected:
    string name; int age;
    Address home;
public:
    Person(string n,int a,string c,int p):name(n),age(a),home(c,p){cout<<"Person+ ";}
    virtual ~Person(){cout<<"Person- ";}
};
class Student : public Person {
    long long regNo;
public:
    Student(string n,int a,long long r,string c,int p)
        :Person(n,a,c,p),regNo(r){cout<<"Student+ ";}
    ~Student(){cout<<"Student- ";}
    void print() const { cout<<regNo<<' '<<name<<" ("<<age<<") "<<home.str()<<'\n'; }
};
class Staff : public Person {
    double salary;
public:
    Staff(string n,int a,string c,int p,double s):Person(n,a,c,p),salary(s){cout<<"Staff+ ";}
    ~Staff(){cout<<"Staff- ";}
};
class TeachingAssistant : public Student {
public:
    TeachingAssistant(string n,int a,long long r,string c,int p)
        :Student(n,a,r,c,p){cout<<"TA+ ";}
    ~TeachingAssistant(){cout<<"TA- ";}
};
int main(){
    { Student s("Kavya",19,192311001,"Salem",636001); s.print(); }
    cout<<"| ";
    { Staff s("Ravi",35,"Chennai",600001,45000); }
    cout<<"| ";
    { TeachingAssistant t("Arun",22,192311002,"Madurai",625001); }
    cout<<'\n';
}