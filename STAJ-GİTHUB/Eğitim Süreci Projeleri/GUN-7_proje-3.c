#include<stdio.h>

/*
int topla (int sayi1,int sayi2) {
	
	
	
	return (sayi1+sayi2);
}
*/

int factoriel (sayi) {
	int fact= 1;
	for(;sayi>0;sayi--){
		
	fact *=sayi;
}
	
	return fact;
}


int main() {
/*	
	int sayi1,sayi2;
	int toplam;
	
	scanf("%d %d",&sayi1,&sayi2);
//	printf("%d",topla(sayi1,sayi2));     VEYA
	
	toplam=sayi1+sayi2;
	printf("%d",toplam);
*/

int n;	
	
	printf("Faktoriyelini almak istediginiz sayiyi giriniz.\n");
	scanf("%d",&n);
	printf("Faktoriyel: %d",factoriel(n));
	
	// 26.Ders sonu.
	
	return 0;
}
