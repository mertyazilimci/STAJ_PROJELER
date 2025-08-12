#include<stdio.h>


int main () {
	
	float toplam =0.0;
	int sayilar [5];
	int i;
	
	for(i=0;i<5;i++){
printf("LUTFEN SAYI GIRINIZ.");		
		scanf("%d",&sayilar[i]);
		
	}
	/*
	for (i=0;i<5;i++) {
		
		printf("%d\n",sayilar[i]);
	}
	*/
	
	for (i=0;i<5;i++) {
		toplam += sayilar [i];
	
		
	}
	printf("Girdiginiz sayilarin aritmetik ortalamasi: %f",toplam/5);
	// 21.ders sonu.
	
	return 0;
}
