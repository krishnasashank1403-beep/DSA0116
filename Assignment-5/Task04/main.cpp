#include <iostream>
#include <iomanip>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>
using namespace std;
class Bill {
protected:string patient;
public:explicit Bill(string p):patient(move(p)){} virtual ~Bill()=default;
virtual double total()const=0; virtual string type()const=0;
void print()const{cout<<type()<<' '<<patient<<": "<<total()<<'\n';}
};
class OutPatient:public Bill {
double consultation,tests;
public:OutPatient(string p,double c,double t):Bill(move(p)),consultation(c),tests(t){}
double total()const override{return consultation+tests;} string type()const override{return "OP";}
};
class InPatient:public Bill {
int days;double rate,procedure;
public:InPatient(string p,int d,double r,double s):Bill(move(p)),days(d),rate(r),procedure(s){}
double total()const override{return days*rate+procedure;} string type()const override{return "IP";}
};
class DayCare:public Bill {
double package;
public:DayCare(string p,double v):Bill(move(p)),package(v){}
double total()const override{return package;} string type()const override{return "DayCare";}
};
class Emergency:public Bill {
double base,hourly;int hours;
public:Emergency(string p,double b,int h,double r):Bill(move(p)),base(b),hourly(r),hours(h){}
double total()const override{return base+hours*hourly;} string type()const override{return "Emergency";}
};
class CorporateBill:public Bill {
double discountable;
public:CorporateBill(string p,double v):Bill(move(p)),discountable(v){}
double total()const override{return discountable*0.9;} string type()const override{return "Corporate";}
};
class Payer {public:virtual ~Payer()=default;virtual double covered(const Bill&)const=0;virtual string name()const=0;};
class Insurance:public Payer {
double limit,coPay;
public:Insurance(double l,double c):limit(l),coPay(c){}
double covered(const Bill& b)const override{return min(b.total(),limit)*(1-coPay/100);}
string name()const override{return "Insurance";}
};
class CorporatePayer:public Payer {
double rate;
public:explicit CorporatePayer(double r):rate(r){}
double covered(const Bill& b)const override{return b.total()*rate/100;}
string name()const override{return "CorporatePayer";}
};
int main(){
cout<<fixed<<setprecision(2);
vector<unique_ptr<Bill>> bills;
bills.push_back(make_unique<OutPatient>("Ravi",500,1200));
bills.push_back(make_unique<InPatient>("Meena",3,2500,40000));
bills.push_back(make_unique<DayCare>("Asha",18000));
bills.push_back(make_unique<Emergency>("Kiran",1000,3,750));
bills.push_back(make_unique<CorporateBill>("Nila",20000));
vector<unique_ptr<Payer>> payers;
payers.push_back(make_unique<Insurance>(50000,20));
payers.push_back(make_unique<CorporatePayer>(75));
for(const auto& b:bills){
b->print();
for(const auto& p:payers)cout<<"  "<<p->name()<<" covers "<<p->covered(*b)<<'\n';
}
}