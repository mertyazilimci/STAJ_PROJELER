#include<stdio.h>


int asal_mi(int sayi){
	
	int i;

for(i=2;i<sayi;i++){
	
	if(sayi%i==0) {
		
		return 0;
	}
	else {
		
		return 1;
	}
	
}	
	
	
}


int main(){
	
int n;	
	
	printf("Bir sayi giriniz.\n");
	scanf("%d",&n);
	
	if(asal_mi(n)==0){
		
		printf("Bu sayi asal degildir.");
	}
	else {
		
		printf("Bu sayi asaldir.");
					
	}
	
	
	
	
	
	
	return 0;
}
