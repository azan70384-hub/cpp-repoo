#include <iostream>
#include <string>

using namespace std;

template <typename F>

class calculator{
	public:
		F add(F a, F b){
			return a+b;
		}
		F sub(F a, F b){
			return a-b;
		}
		F mult(F a, F b){
			return a*b;
	    }
		F div(F a, F b){
			if(b==0){
			return 0;
			}
			return a/b;
		}		
};
 

int main(){
calculator<int> intcalculator;
cout<<intcalculator.add(7, 9)<<endl; 
cout<<intcalculator.sub(7, 9)<<endl; 
cout<<intcalculator.mult(7, 9)<<endl; 
cout<<intcalculator.div(7, 9)<<endl; 

calculator<float> FLOATcalculator;
cout<<FLOATcalculator.add(7.9, 9.4)<<endl; 
cout<<FLOATcalculator.sub(7.6, 9.2)<<endl; 
cout<<FLOATcalculator.mult(7.4, 9.4)<<endl; 
cout<<FLOATcalculator.div(7.6, 9.9)<<endl;

calculator<string> STRINGcalculator;
cout<<STRINGcalculator.add("hmmm "," fuck")<<endl;

return 0;  
}

