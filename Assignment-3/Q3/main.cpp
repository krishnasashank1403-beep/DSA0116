#include <iostream>
using namespace std;
struct Logger {
    string n;
    Logger(const string& s):n(s){cout<<'+'<<n<<' ';}
    Logger(const Logger& o):n(o.n+"c"){cout<<"copy"<<n<<' ';}
    ~Logger(){cout<<'-'<<n<<' ';}
};
void use(Logger){cout<<"use ";}
class Event {
    int rows,seats,booked;
    char** map;
public:
    Event(int r,int s):rows(r),seats(s),booked(0),map(nullptr) {
        if(r<=0||s<=0){rows=seats=0; return;}
        map=new char*[rows]{};
        int made=0;
        try {
            for(;made<rows;++made) {
                map[made]=new char[seats];
                for(int j=0;j<seats;++j) map[made][j]='O';
            }
        } catch(...) {
            while(made>0) delete[] map[--made];
            delete[] map; map=nullptr; throw;
        }
        cout<<"Event opened\n";
    }
    bool book(int r,int s) {
        if(!map||r<0||r>=rows||s<0||s>=seats||map[r][s]=='X') return false;
        map[r][s]='X'; ++booked; return true;
    }
    bool cancel(int r,int s) {
        if(!map||r<0||r>=rows||s<0||s>=seats||map[r][s]=='O') return false;
        map[r][s]='O'; --booked; return true;
    }
    ~Event() {
        if(map){for(int i=0;i<rows;++i) delete[] map[i]; delete[] map;}
        cout<<"Event closed. Seats booked: "<<booked<<'\n';
    }
};
int main() {
    Logger a("A");
    { Logger b("B"); }
    use(a);
    Logger* p=new Logger("P"); delete p;
    cout<<"end ";
    Event morning(2,3); morning.book(0,1);
    { Event afternoon(1,2); afternoon.book(0,0); }
}