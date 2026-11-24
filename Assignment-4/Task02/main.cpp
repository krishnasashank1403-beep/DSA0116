#include <iostream>
#include <string>
using namespace std;
class Person {
protected:
    string name;
public:
    Person(string n=""):name(n){cout<<"Person ";}
};
class Student : virtual public Person {
public:
    Student(string n=""):Person(n){cout<<"Student ";}
};
class Staff : virtual public Person {
public:
    Staff(string n=""):Person(n){cout<<"Staff ";}
};
class TeachingAssistant : public Student, public Staff {
public:
    TeachingAssistant(string n):Person(n),Student(n),Staff(n){cout<<"TA ";}
    void show() const { cout<<"Name: "<<name<<'\n'; }
};
class ResearchScholar : public Student {
    double fellowship;
public:
    ResearchScholar(string n,double f):Person(n),Student(n),fellowship(f){}
    void showFellowship() const { cout<<"Fellowship: "<<fellowship<<'\n'; }
};
int main(){
    TeachingAssistant ta("Kavya");
    cout<<'\n';
    ta.show();
    ResearchScholar rs("Arun",12000);
    rs.showFellowship();
}