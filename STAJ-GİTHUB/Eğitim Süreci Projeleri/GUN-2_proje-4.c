#include<stdio.h>
#define PI 3.14


int main ()  {
	
	int yaricap;
	float hacim;
	
	printf("kurenin yaricapini giriniz");
	
	scanf("%d",&yaricap);
	
	
	hacim = (4/3.0)*PI*(yaricap*yaricap*yaricap);
	
	printf("kurenin hacmi %fb",hacim);
	
	// 7. DERS SONU
	
	return 0;
}
