#include <iostream>
#include <memory>
#include <string>
#include <vector>
using namespace std;

class Vehicle {
protected:
    string reg;
    double dailyRate;
    bool rented=false;
public:
    Vehicle(string r,double rate):reg(r),dailyRate(rate){}
    virtual double charge(int days) const=0;
    virtual string type() const=0;
    virtual void details() const {
        cout<<type()<<" "<<reg<<" Rs "<<charge(2)<<" for 2 days\n";
    }
    bool rent(){if(rented)return false;rented=true;return true;}
    double giveBack(int daysLate){
        rented=false;
        return charge(daysLate);
    }
    virtual ~Vehicle()=default;
};
class Bicycle:public Vehicle {
public:
    Bicycle(string r,double rate):Vehicle(r,rate){}
    double charge(int d)const override{return dailyRate*d;}
    string type()const override{return "Bicycle";}
};
class MotorVehicle:public Vehicle {
protected:
    double fuelLevel;
    string serviceDue;
public:
    MotorVehicle(string r,double rate,double f,string due):Vehicle(r,rate),fuelLevel(f),serviceDue(due){}
};
class TwoWheeler:public MotorVehicle {
public:
    TwoWheeler(string r,double rate,double f,string due):MotorVehicle(r,rate,f,due){}
    double charge(int d)const override{return dailyRate*d+50;}
    string type()const override{return "TwoWheeler";}
};
class Car:public MotorVehicle {
protected:
    int seats;
public:
    Car(string r,double rate,double f,string due,int s):MotorVehicle(r,rate,f,due),seats(s){}
    double charge(int d)const override{return dailyRate*d+100;}
    string type()const override{return "Car";}
};
class ElectricCar:public Car {
    double batteryKWh;
public:
    ElectricCar(string r,double rate,double f,string due,int s,double k)
        :Car(r,rate,f,due,s),batteryKWh(k){}
    double charge(int d)const override{return dailyRate*d+batteryKWh*2;}
    string type()const override{return "ElectricCar";}
};
class ElectricBus:public Vehicle {
    int seats;
    double batteryKWh;
public:
    ElectricBus(string r,double rate,int s,double k):Vehicle(r,rate),seats(s),batteryKWh(k){}
    double charge(int d)const override{return dailyRate*d+batteryKWh*2+200;}
    string type()const override{return "ElectricBus";}
};
int main(){
    vector<unique_ptr<Vehicle>> fleet;
    fleet.push_back(make_unique<Bicycle>("BI-101",100));
    fleet.push_back(make_unique<TwoWheeler>("TW-202",250,8,"2027-01-10"));
    fleet.push_back(make_unique<Car>("CA-303",1000,20,"2027-02-15",5));
    fleet.push_back(make_unique<ElectricCar>("EV-404",1200,80,"2027-03-01",5,40));
    fleet.push_back(make_unique<ElectricBus>("EB-505",3000,30,120));

    for(auto& v:fleet){
        cout<<v->type()<<" rent: "<<(v->rent()?"Success":"Unavailable")<<", 2-day charge Rs "<<v->charge(2)<<'\n';
    }
    cout<<"Late return charge: Rs "<<fleet[0]->giveBack(1)<<'\n';
    cout<<"Returned bicycle rent: "<<(fleet[0]->rent()?"Success":"Unavailable")<<'\n';
}