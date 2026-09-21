#include <iostream>
#include <vector>
using namespace std;

int main(){
vector<int> num;
num.push_back(1);
num.push_back(2);
num.push_back(3);

for(int val : num){
    cout<<val<<"";
};
cout<<num.size();;
cout<<num.capacity();

num.pop_back();

for(int val : num){
    cout<<val<<"";
};

cout<<num.size();;
cout<<num.capacity();

return 0;
}
