#include <iostream>
#include <unordered_map>
#include <string>

using namespace std;

int main(){
	unordered_map<string, string> mydictionary;
	mydictionary.insert(pair<string, string>("thanks", "danke"));
	mydictionary.insert(pair<string, string>("please", "bitea"));
	mydictionary.insert(pair<string, string>("nice", "nett"));
	mydictionary.insert(pair<string, string>("funny" , "lustig"));
	mydictionary.insert(pair<string, string>("good", "got"));
	mydictionary["nice"]= "fruet mitch";
	
	cout<< "size :"<<mydictionary.size()<<endl;
	
			cout<<"key "<<  "     "<<"value"<<endl;
	for (auto pair : mydictionary){
		cout<<pair.first<<  "     "<<pair.second<<endl;
	}
}
