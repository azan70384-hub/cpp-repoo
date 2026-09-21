 #include <iostream>
#include <queue>
using namespace std;

int main(){
	queue<int>myqueue;
	myqueue.push(10);
	myqueue.push(20);
	myqueue.push(30);

	
    cout<<myqueue.size()<<endl;     
   
    cout<<myqueue.back()<<endl;
    
    while(!myqueue.empty()){
    cout<<myqueue.front()<<endl;
    		myqueue.pop();
	}
}
