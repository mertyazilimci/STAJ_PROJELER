#include<stdio.h>
#include<string.h>

struct adress {
	char mahalle[20];
	char cadde [15];
	char sokak [15];
	
	
};

struct ogrenci {
	char isim [20];
	char soyisim[20];
	int numara;
	int yas;
	
	struct adress adres;
	
};


int main()  {
	
	struct ogrenci ogrenci1;
	
	// ogrenci1.isim = "Mustafa Murat"; //bu þekilde olmaz.
	
	strcpy(ogrenci1.isim,"Mustafa murat");
	strcpy(ogrenci1.soyisim,"baltaci");
	ogrenci1.numara = 132;
	ogrenci1.yas = 24;
	
	strcpy(ogrenci1.adres.mahalle,"Bahcelievler.");
	strcpy(ogrenci1.adres.cadde,"7.cadde.");
	strcpy(ogrenci1.adres.sokak,"1032.sok.");
	
	printf("%s  %s  %d  %d  %s  %s  %s\n",ogrenci1.isim,ogrenci1.soyisim,ogrenci1.numara,ogrenci1.yas,ogrenci1.adres.mahalle,ogrenci1.adres.cadde,ogrenci1.adres.sokak);
	
	// 43.ders sonu.
	
	return 0;
}
