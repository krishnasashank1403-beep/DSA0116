#include <iostream>
#include <cmath>
#include <stdexcept>
using namespace std;
class Complex {
    double real,imag;
public:
    Complex():real(0),imag(0){}
    Complex(double r):real(r),imag(0){}
    Complex(double r,double i):real(r),imag(i){}
    Complex operator+(const Complex& z)const{return {real+z.real,imag+z.imag};}
    Complex operator-(const Complex& z)const{return {real-z.real,imag-z.imag};}
    Complex operator*(const Complex& z)const{return {real*z.real-imag*z.imag,real*z.imag+imag*z.real};}
    Complex operator/(const Complex& z)const{
        double d=z.real*z.real+z.imag*z.imag;
        if(d==0)throw runtime_error("Division by zero impedance");
        return {(real*z.real+imag*z.imag)/d,(imag*z.real-real*z.imag)/d};
    }
    bool operator==(const Complex& z)const{return real==z.real&&imag==z.imag;}
    double magnitude()const{return sqrt(real*real+imag*imag);}
    friend ostream& operator<<(ostream& out,const Complex& z){
        return out<<z.real<<(z.imag<0?" - j":" + j")<<abs(z.imag);
    }
};
int main(){
    Complex resistor(10,0),inductor(0,5),capacitor(0,-2);
    Complex series=resistor+inductor+capacitor;
    Complex parallel=(resistor*inductor)/(resistor+inductor);
    cout<<"Series: "<<series<<'\n'<<"Magnitude: "<<series.magnitude()<<'\n';
    cout<<"Parallel: "<<parallel<<'\n';
    try{Complex zero;cout<<(resistor/zero);}catch(const exception& e){cout<<e.what()<<'\n';}
}