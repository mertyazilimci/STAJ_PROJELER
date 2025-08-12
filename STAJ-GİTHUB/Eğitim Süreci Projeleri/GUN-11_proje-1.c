#include<stdio.h>

char *gunismi (char *gundisisi[],int uzunluk,int hangigun) {
	
	if(hangigun >= 1 && hangigun <= 7){
		return gundisisi[hangigun-1];
		
	}
	else {
		
		return NULL;
	}
	
	
}


int main ()  {
	
	char *gunler[7]= {"pazartesi","sali","carsamba","persembe","cuma","cumartesi","pazar"};
	
//	printf("%s",gunler[0]); 
	
	char *p = gunismi(gunler,7,5);
	
	if (p== NULL){
		printf("NULL");
	}
	else {
		
		printf ("%s",p);
	}
	
	// 37.ders sonu.
	
	return 0;
}
