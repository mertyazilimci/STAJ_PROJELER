#include<stdio.h>
#include<string.h>

struct ogrenci {
	
	char isim[20];
	char sayisim[20];
	
	int numara;
	
};



int main ()  {
	
	struct ogrenci *tut;
	struct ogrenci ogrenci1;
	
	strcpy(ogrenci1.isim,"mustafa");
	strcpy(ogrenci1.sayisim,"tamdenk");
	ogrenci1.numara = 145;
	
	tut = &ogrenci1;
	
	printf("%s  %s  %d\n",ogrenci1.isim,ogrenci1.sayisim,ogrenci1.numara); // Bu normal bastırma.
	printf("%s  %s  %d",tut->isim,tut->sayisim,tut->numara);
	
	// 46.ders sonu.
	
	return 0;
}
