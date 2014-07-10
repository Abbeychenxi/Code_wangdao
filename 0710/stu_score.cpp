#include <iostream>
#include <string>
#include <vector>
using namespace std;
typedef struct stu{
    string name;
    int score;
};
vector <stu> vec;

int main(int argc, const char *argv[])
{
    string name;
    int score;
    while(cin){
        cin >> name >> score;
        stu stu;
        stu.name=name;
        stu.score=score;
        vec.push_back(stu);
    }
    for(vector<stu>::iterator iter=vec.begin(); iter != vec.end()-1; ++iter){
        if((*iter).score >=60){
            cout << (*iter).name << " " << (*iter).score << endl;
        }
    }

    return 0;
}
