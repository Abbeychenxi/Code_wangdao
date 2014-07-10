#include <iostream>
#include <string>
#include <vector>
using namespace std;
int main(int argc, const char *argv[])
{
    string s;
    cin >> s;
    
    for(string::iterator it = s.begin(); it != s.end(); ++it){
       // cout << *it << endl;
       if(*it >= 'a' && *it <= 'z'){
           *it -=32;
       }else if(*it >= 'A' && *it <= 'Z'){
            *it +=32;
       }
    }
    cout << s << endl;


    return 0;
}
