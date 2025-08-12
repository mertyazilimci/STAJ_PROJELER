#include<stdio.h>

struct ogrenci {
	
	char isim[20];
	char soyisim[20];
	int numara;
	
	
};

void ogrencim (struct ogrenci a) {
	
	printf("%s  %s  %d",a.isim,a.soyisim,a.numara);
	
}

struct ogrenci degerAl () {
	
	struct ogrenci yeni;
	printf("degerleri giriniz.\n");
	scanf("%s  %s  %d",&yeni.isim,&yeni.soyisim,&yeni.numara);
	
	return yeni;
}


int main ()  {
/*	struct ogrenci ogrenci1 = {"murat ali","behcet",123};
		ogrencim(ogrenci1);  */

struct ogrenci ogrenci1 = degerAl();

ogrencim(ogrenci1);



// 45.ders sonu
	
	return 0;
} 
