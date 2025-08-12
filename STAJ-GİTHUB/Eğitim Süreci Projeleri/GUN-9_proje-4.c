#include<stdio.h>


void degisim (int sayi1,int sayi2) {
	
	int temp = sayi1;
	sayi1 = sayi2;
	sayi2 = temp;
	
	printf("sayi 1: %d  sayi 2: %d\n",sayi1,sayi2);
	
}



int main() {
	
	int x=5,y=10;
	degisim(x,y);
	
	printf("x: %d  y: %d\n",x,y);
	
	// 32.Ders sonu.
		
	return 0;
}
