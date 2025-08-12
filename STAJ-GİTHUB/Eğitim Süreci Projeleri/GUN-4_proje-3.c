#include<stdio.h>

int main(){
	/*
	int i ;
	i=0;
	
	while (i<10) {
		
		
		printf("%d Merhaba dunya.\n",i);
		
		i++;
		
	}
	printf("Dongu bitti %d",i);
	*/
	
	int n;
	int fact = 1;
	
	printf("Lutfen faktoriyelini almak istediginiz sayiyi giriniz.\n");
	scanf("%d",&n);
	
	while(n!=0){
		
		fact = fact*n;
		
		n--;
	}
	printf("Sonuc: %d",fact);
	
	// 14.Ders Sonu.
	
	return 0;
}
