#include <iostream>
using namespace std;

class node{
	public:
		int value ;
		node* next;
		node* previous;
};
void printforword(node*head){
	node* treversor = head;
	while(treversor!=nullptr){
		cout<<treversor->value<<endl;
		treversor=treversor->next;
	}
}
void printbackword(node*tail){
	node*treversor =tail;
	while (treversor != nullptr){
		cout<<treversor->value<<endl;
		treversor= treversor->previous;
	}
}
int main(){
	node* head;
	node* tail;
	
	node* Node = new node();
	Node->value= 10;
	Node->next=nullptr;
	Node ->previous=nullptr;
	head= Node;
	tail=Node;
	
	Node = new node();
	Node->value=20;
	Node->next= nullptr;
	Node->previous=tail;
	tail->next=Node;
	tail=Node;
	
	Node = new node();
	Node->value=30;
	Node->next= nullptr;
	Node->previous=tail;
	tail->next=Node;
	tail=Node;
	
	Node = new node();
	Node->value=40;
	Node->next= nullptr;
	Node->previous=tail;
	tail->next=Node;
	tail=Node;
	
	Node = new node();
	Node->value=50;
	Node->next= nullptr;
	Node->previous=tail;
	tail->next=Node;
	tail=Node;
	
	printforword(head);
    printbackword(tail);
	
}
