#include <iostream>
using namespace std;

struct node{
	int data;
	node* left;
	node* right;
};

node* creatnode(int data){
	node* newnode = new node();
	newnode->data = data;
	newnode->left=newnode->right=nullptr;
}
void printtree(node*root){
	if(root == nullptr)return;
	cout<<root->data << endl;
	printtree(root->left);
	printtree(root->right);
}
int main(){
	node* root = creatnode(2);
	
	root->left= creatnode(4);
	root->right=creatnode(5);
	
	root->left->left= creatnode(6);
	root->left->right=creatnode(7);
	
	root->left->left->left= creatnode(8);
	root->left->right->right=creatnode(9);
	
	printtree(root);
}
