#include<stdio.h>


int main()  {
	
	int toplam=0,n,hane=0;
	printf("Rakamlari toplamini ve hane sayisini merak ettiginiz sayiyi giriniz.");
	scanf("%d",&n);
	
	do {
		
		toplam = toplam + n%10;
		
		hane++;
		n=n/10;
		
	}
	while (n>0);
	
	printf("Rakamlari toplami %d , %d haneli",toplam,hane);
	
	//15.ders sonu
	
	return 0;
}
