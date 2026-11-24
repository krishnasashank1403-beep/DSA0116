#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include <limits>
using namespace std;

class BillingError:public runtime_error{public:using runtime_error::runtime_error;};
class ClaimError:public BillingError{public:using BillingError::BillingError;};
class PackageError:public BillingError{public:using BillingError::BillingError;};

double approve(double billed,double cover){
    if(billed<0||cover<0) throw invalid_argument("negative amount");
    if(billed>cover) throw ClaimError("exceeds cover");
    return billed;
}
double settle(double billed,double cover){
    try{return approve(billed,cover);}
    catch(const ClaimError& e){cout<<"audit: "<<e.what()<<'\n';throw;}
}
void validate(double amount){
    if(amount<0) throw invalid_argument("negative");
    if(amount>1e6) throw out_of_range("too large");
    cout<<"ok ";
}
void process(double amount){
    try{validate(amount);}
    catch(const out_of_range& e){cout<<"[log "<<e.what()<<"] ";throw;}
}
struct Resource {
    ~Resource(){cout<<"Resource released\n";}
};
int main(){
    for(double a:{100.0,-5.0,2e6}){
        try{process(a);cout<<"done ";}
        catch(const exception& e){cout<<"caught "<<e.what()<<' ';}
    }
    cout<<'\n';
    double cases[][2]={{40000,50000},{60000,50000},{-1,50000}};
    for(auto& c:cases){
        try{double paid=settle(c[0],c[1]);cout<<"approved "<<paid<<'\n';}
        catch(const ClaimError& e){cout<<"claim rejected: "<<e.what()<<'\n';}
        catch(const exception& e){cout<<"error: "<<e.what()<<'\n';}
    }
    try{
        Resource r;
        vector<int> values;
        values.reserve(values.max_size());
    }catch(const bad_alloc&){cout<<"allocation failed: bad_alloc\n";}
     catch(const exception& e){cout<<"allocation request failed: "<<e.what()<<'\n';}
    try{size_t n=0; stod("not-a-number",&n);}
    catch(const invalid_argument& e){cout<<"input error: "<<e.what()<<'\n';}
    cout<<"Program continues\n";
}