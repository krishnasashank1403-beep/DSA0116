#include <iostream>
#include <iomanip>
using namespace std;
class Money {
    long long paise;
    explicit Money(long long total, bool) : paise(total) {}
public:
    Money(long long rupees=0,int p=0):paise(rupees*100+p){}
    Money operator+(const Money& other) const { return Money(paise+other.paise,true); }
    Money& operator+=(const Money& other){paise+=other.paise;return *this;}
    bool operator==(const Money& other)const{return paise==other.paise;}
    bool operator<(const Money& other)const{return paise<other.paise;}
    Money operator-(const Money& other)const{return Money(paise-other.paise,true);}
    friend ostream& operator<<(ostream& out,const Money& m){
        long long v=m.paise<0?-m.paise:m.paise;
        if(m.paise<0)out<<'-';
        return out<<"Rs "<<v/100<<'.'<<setw(2)<<setfill('0')<<v%100<<setfill(' ');
    }
};
int main(){
    Money a(120,75),b(79,25),c=a+b;
    cout<<c<<'\n'<<boolalpha<<(c==Money(200))<<'\n';
    cout<<(Money(0,75)+Money(0,50))<<'\n';
}