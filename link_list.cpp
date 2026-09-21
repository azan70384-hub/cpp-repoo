#include <iostream>

using namespace std;

struct node{
	int value=1;
	node* next;
};

void print(node*n){
	while(n!=NULL){
		cout<<n->value<<endl;
		n=n->next;
	}
}

void insertAtFront(node**head, int newValue){
	node* newnode =new node();
	newnode->value=newValue;
	newnode->next=*head;
	 *head = newnode;
}

void interAtEnd(node**head, int newValue){
	node* newnod = new node();
	newnod->value=newValue;
	newnod->next= NULL;
	
	if(*head==NULL){
		*head=newnod;
		return;
	}
	
	node* last =*head;
	while(last->next!= NULL){
		last=last->next;
	}
	last->next=newnod;
}

void insertInbetween(node*previous , int newValue){
	if(previous==NULL){
		cout<<"previous cannot be null";
		return;
	}
    node* newnode=new node();
    newnode->value=newValue;
    newnode->next=previous->next;
    previous->next=newnode;
	
}
int main(){
	node* head = new node();
	node* second= new node();
    node* third= new node();
    
	head->value=10;
	head->next=second;
	
	second->value=20;
    second->next=third;
    
    third->value= 30;
    third->next= NULL;
    

    insertAtFront(&head,44);
    insertInbetween(head, 33);
    interAtEnd(&head, 66);
    

        print(head);
}
