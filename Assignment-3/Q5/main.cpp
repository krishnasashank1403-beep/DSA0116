#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <string>
#include <vector>
using namespace std;
class Time {
    int seconds;
public:
    explicit Time(int s=0):seconds(s){}
    Time& operator++(){++seconds;return *this;}
    Time operator++(int){Time old(*this);++seconds;return old;}
    bool operator==(const Time& t)const{return seconds==t.seconds;}
    bool operator<(const Time& t)const{return seconds<t.seconds;}
    void print()const{
        cout<<seconds/3600<<':'<<setw(2)<<setfill('0')<<(seconds/60)%60
            <<':'<<setw(2)<<seconds%60<<setfill(' ')<<'\n';
    }
};
class Playlist {
    vector<string> tracks;
public:
    explicit Playlist(vector<string> t):tracks(std::move(t)){}
    string& operator[](int i){
        if(i<0||i>=static_cast<int>(tracks.size()))throw out_of_range("Track index out of range");
        return tracks[i];
    }
    const string& operator[](int i)const{
        if(i<0||i>=static_cast<int>(tracks.size()))throw out_of_range("Track index out of range");
        return tracks[i];
    }
};
int main(){
    Time t(3599); Time a=t++; Time b=++t;
    a.print();b.print();t.print();
    Playlist p({"Song One","Song Two"});cout<<p[0]<<'\n';
}