#include<stdio.h>



int main() {
	
/*    PROJE 1

	int a,b,c,d,e;
	float aritmetik;
	
	printf("5 tane tam sayi giriniz.");
	
	scanf("%d %d %d %d %d",&a,&b,&c,&d,&e);
	
	aritmetik= (a+b+c+d+e)/5;
	
	printf("Girdiginiz sayilarin ortalamasi %.2f",aritmetik);   */
	
	
	int a,b,c;
	float x1,x2;
	float delta;
	

	printf("Denklemin a'sini giriniz.");
	scanf("%d",&a);
	printf("Denklemin b'sini giriniz.");
	scanf("%d",&b);
	printf("Denklemin c'sini giriniz.");
	scanf("%d",&c);
	
	delta= b*b -4*a*c;
	x1 = (-b + (sqrt(delta))) / 2*a ;
	x2 = (-b - (sqrt(delta))) / 2*a ;
	
	printf("Denklemin 1.koku %.2f,denklemin 2.koku %.2f",x1,x2);
	
	
	// 8.Ders sonu.
	
	
	return 0;
}
