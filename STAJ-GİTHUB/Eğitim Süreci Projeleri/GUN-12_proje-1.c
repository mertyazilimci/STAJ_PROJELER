#include<stdio.h>

struct student {
	
	char isim [15];
	char soyisim [15];
	
	int numara;
	int yas;
	
};


int main()  {
	
	struct student ahmet = { "ahmet","Gedikli",135,23};
	
	printf("%s  %s  %d  %d",ahmet.isim,ahmet.soyisim,ahmet.numara,ahmet.yas);
	
// 41.ders sonu.	
	
	return 0;
}
