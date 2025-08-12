#include<stdio.h>

void degisim (int *a,int *b) {
	
	int gecici = *a;
	*a= *b;
	*b = gecici;
	
}





int main () {

	int x=5,y=10;
	
	degisim(&x,&y);
	
	printf("x:%d  y:%d\n",x,y);	
	
	
	// 33.Ders sonu.
	
	
	return 0;
}
