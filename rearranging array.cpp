#include <iostream>
using namespace std;
void reverseArray(int arry[], int n ){
	int left = 0;
	int right = n-1;
	
while (left<right){
    int temp = arry[right];
    arry[right]=arry[left];
    arry[left]= temp;
    
    left++;
    right--;
    
}
}

int main(){
	int arry[] = {50, 40 , 30, 20, 10};
	int n=sizeof(arry)/sizeof(arry[0]);
	 
	 cout<< "Orignal arry : " ;
	 for (int i=0 ; i<n; i++ ){
	 	cout<< arry[i] << "  ";
	 }
	 
cout<<endl;
reverseArray(arry, n );
	 cout<< "rearranged array : " ;
	 for (int i=0 ; i<n; i++ ){
	 	cout<< arry[i] << "  ";
	 }
return 0;
}



