#include <iostream>
#include <stack>
using namespace std;



int main(){
	stack<int>numberstack;
	numberstack.push(10);
	numberstack.push(20);
	numberstack.push(30);
	numberstack.push(40);
	
	
	if(numberstack.empty()){
		cout<<"the stack is empty"<<endl;
	} else{
		cout<<"the stack is not empty"<<endl;
	}
	cout<<"the stack size is :"<<numberstack.size()<<endl;
	
	while(!numberstack.empty()){
		cout<<numberstack.top()<<endl;
		numberstack.pop();
	}
} 
