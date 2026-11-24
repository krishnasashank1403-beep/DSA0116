#include <iostream>
#include <algorithm>
#include <iomanip>
#include <memory>
#include <string>
#include <vector>
using namespace std;

class Bill {
protected:
    string patient;
public:
    explicit Bill(string p):patient(move(p)){}
    virtual ~Bill()=default;
    virtual double total() const=0;
    virtual string type() const=0;
    void print() const { cout<<type()<<" "<<patient<<": "<<total()<<'\n'; }
};
class OutPatient:public Bill {
    double consultation,tests;
public:
    OutPatient(string p,double c,double t):Bill(move(p)),consultation(c),tests(t){}
    double total()const override{return consultation+tests;}
    string type()const override{return "OP";}
};
class InPatient:public Bill {
    int days; double perDay,procedure,medicines;
public:
    InPatient(string p,int d,double r,double s,double m):Bill(move(p)),days(d),perDay(r),procedure(s),medicines(m){}
    double total()const override{return days*perDay+procedure+medicines;}
    string type()const override{return "IP";}
};
class DayCareBill:public Bill {
    double package;
public:
    DayCareBill(string p,double v):Bill(move(p)),package(v){}
    double total()const override{return package;}
    string type()const override{return "DayCare";}
};
class EmergencyBill:public Bill {
    double base; int hours; double hourly;
public:
    EmergencyBill(string p,double b,int h,double r):Bill(move(p)),base(b),hours(h),hourly(r){}
    double total()const override{return base+hours*hourly;}
    string type()const override{return "Emergency";}
};
class Payer {
public:
    virtual ~Payer()=default;
    virtual string name()const=0;
    virtual double amountCovered(const Bill& b)const=0;
};
class SelfPay:public Payer {
public:
    string name()const override{return "SelfPay";}
    double amountCovered(const Bill&)const override{return 0;}
};
class Insurance:public Payer {
    double limit,coPay;
public:
    Insurance(double l,double c):limit(l),coPay(c){}
    string name()const override{return "Insurance";}
    double amountCovered(const Bill& b)const override{return min(b.total(),limit)*(1.0-coPay/100.0);}
};
class GovernmentScheme:public Payer {
    double packageRate;
public:
    explicit GovernmentScheme(double r):packageRate(r){}
    string name()const override{return "GovernmentScheme";}
    double amountCovered(const Bill& b)const override{return min(b.total(),packageRate);}
};
int main(){
    cout<<fixed<<setprecision(2);
    vector<unique_ptr<Bill>> bills;
    bills.push_back(make_unique<OutPatient>("Ravi",500,1200));
    bills.push_back(make_unique<InPatient>("Meena",3,2500,40000,5000));
    bills.push_back(make_unique<DayCareBill>("Asha",18000));
    bills.push_back(make_unique<EmergencyBill>("Kiran",1000,3,750));
    vector<unique_ptr<Payer>> payers;
    payers.push_back(make_unique<SelfPay>());
    payers.push_back(make_unique<Insurance>(50000,20));
    payers.push_back(make_unique<GovernmentScheme>(15000));
    double grand=0;
    for(const auto& b:bills){
        b->print(); grand+=b->total();
        for(const auto& p:payers)
            cout<<"  "<<p->name()<<" covers "<<p->amountCovered(*b)<<'\n';
    }
    cout<<"Day total: "<<grand<<'\n';
}