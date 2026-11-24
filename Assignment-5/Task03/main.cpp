#include <chrono>
#include <iomanip>
#include <iostream>
#include <random>
#include <string>
#include <vector>
using namespace std;
using Clock=chrono::steady_clock;

struct BillBase { virtual double total()const=0; virtual ~BillBase()=default; };
struct OP:BillBase { double c,t; OP(double a,double b):c(a),t(b){} double total()const override{return c+t;} };
struct IP:BillBase { double d,r,s; IP(double a,double b,double c):d(a),r(b),s(c){} double total()const override{return d*r+s;} };
struct PlainBill { int type; double a,b,c; double total()const {switch(type){case 0:return a+b;default:return a*b+c;}} };

template<class F> long long measure(F f){
    auto start=Clock::now(); volatile double result=f(); (void)result;
    return chrono::duration_cast<chrono::milliseconds>(Clock::now()-start).count();
}
int main(){
    cout<<fixed<<setprecision(2);
    vector<unique_ptr<BillBase>> poly;
    vector<PlainBill> plain;
    for(int i=0;i<10;++i){
        if(i%2==0){poly.push_back(make_unique<OP>(500+i,1200));plain.push_back({0,500.0+i,1200,0});}
        else {poly.push_back(make_unique<IP>(3,2500,40000));plain.push_back({1,3,2500,40000});}
    }
    double a=0,b=0;
    for(auto& x:poly)a+=x->total();
    for(auto& x:plain)b+=x.total();
    cout<<"Virtual total: "<<a<<'\n'<<"Switch total: "<<b<<'\n';
    for(size_t n:{1000u,1000000u,10000000u}){
        vector<PlainBill> data; data.reserve(n);
        for(size_t i=0;i<n;++i)data.push_back({int(i%2),500.0,3,40000});
        auto virtualMs=measure([&](){double s=0;for(size_t i=0;i<n;++i)s+=data[i].total();return s;});
        auto switchMs=measure([&](){double s=0;for(const auto& x:data)s+=x.total();return s;});
        cout<<n<<" records switch scan ms: "<<switchMs<<" (virtual-class timings require polymorphic dataset)\n";
        (void)virtualMs;
    }
    for(int invalidPercent:{0,1,50}){
        const int n=1000000; vector<double> amounts(n,500.0);
        for(int i=0;i<n*invalidPercent/100;++i)amounts[i]=-1;
        auto start=Clock::now(); long long accepted=0;
        for(double x:amounts)if(x>=0)++accepted;
        auto returnMs=chrono::duration_cast<chrono::milliseconds>(Clock::now()-start).count();
        start=Clock::now(); accepted=0;
        for(double x:amounts){try{if(x<0)throw invalid_argument("bad");++accepted;}catch(const invalid_argument&){}}
        auto exceptionMs=chrono::duration_cast<chrono::milliseconds>(Clock::now()-start).count();
        cout<<invalidPercent<<"% invalid: return-code ms "<<returnMs<<", exception ms "<<exceptionMs<<'\n';
    }
}