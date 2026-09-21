#include <iostream>
#include <list>
using namespace std;

int main(){
	list<int>  fuck;;
	fuck.push_back(10);
	fuck.push_back(20);
	fuck.push_back(30);
	fuck.push_back(40);
	fuck.push_front(00000);
	
	for(list<int>::iterator it = fuck.begin(); it!=fuck.end(); it++ ){
		cout <<*it<< endl;
	}

return 0;
}
