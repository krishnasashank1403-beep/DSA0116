#include <iostream>
#include <cstring>
using namespace std;
class Text {
    char* data;
public:
    Text(const char* s=""){data=new char[strlen(s)+1];strcpy(data,s);}
    Text(const Text& other):Text(other.data){}
    Text& operator=(const Text& other){
        if(this!=&other){char* p=new char[strlen(other.data)+1];strcpy(p,other.data);delete[] data;data=p;}
        return *this;
    }
    ~Text(){delete[] data;}
    Text operator+(const Text& other)const{
        size_t n=strlen(data)+strlen(other.data);
        char* joined=new char[n+1];strcpy(joined,data);strcat(joined,other.data);
        Text result(joined);delete[] joined;return result;
    }
    bool operator==(const Text& other)const{return strcmp(data,other.data)==0;}
    bool operator!=(const Text& other)const{return !(*this==other);}
    friend ostream& operator<<(ostream& out,const Text& t){return out<<t.data;}
};
int main(){
    Text a("Hello "),b("Metro");Text c=a+b;cout<<c<<'\n';
    Text d;d=c;d=d;cout<<boolalpha<<(d==c)<<'\n';
}