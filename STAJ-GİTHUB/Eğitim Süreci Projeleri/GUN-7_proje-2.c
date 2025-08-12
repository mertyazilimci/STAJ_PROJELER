#include<stdio.h>


void hatayibas (int hata) {
	
	printf("hata kodu %d",hata);
	
}





int main() {
	
	int sayi;
	
	printf("Lutfen negatif olmayan bir sayi giriniz.");
	scanf("%d",&sayi);
	
	if (sayi<0){
		
		hatayibas(404);
	}
	else {
		printf("Tebrikler.");
	}
	
	//25. ders sonu.
	
	return 0;
}
