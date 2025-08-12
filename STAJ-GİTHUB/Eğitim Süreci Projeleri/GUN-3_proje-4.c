#include<stdio.h>



int main() {
	
	int vize1,vize2,final;
	float dersort;
	float ortalama;
	printf("1.Vize notunuzu giriniz.");
	scanf("%d",&vize1);
	printf("2.Vize notunuzu giriniz.");
	scanf("%d",&vize2);
	printf("Final notunuzu giriniz.");
	scanf("%d",&final);
	
	printf("Lutfen universite ortalamanizi giriniz.");
	scanf("%f",&ortalama);
	
	dersort = (vize1+vize2+final) /3.0;

	/*
	if(dersort > 60) {
		
		printf("Dersten gectiniz.");
	}
	
	else {
		
		printf("Dersten kaldiniz.");
		
		
	}   */
	
	if(dersort > 60) {
			printf("Dersten gectiniz.");	
	}
	
	else if (dersort > 50) {
		
		printf("Dersten bute kaldiniz.");
		
		if(ortalama < 2.5) {
			printf("butu gecsen bile seneye dersi al.Cunku ortalaman dusuk.");
			
		}
		
	}
	else {
		
		printf("Kaldiniz.");
		
	}
	
	// 11.Ders sonu.
	
	
	
	
	
	
	
	
	return 0;
}
