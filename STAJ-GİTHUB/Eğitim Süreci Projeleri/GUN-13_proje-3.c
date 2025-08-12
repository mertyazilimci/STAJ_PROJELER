#include<stdio.h> 
#include<string.h>

struct ogrenci {
	
	char isim[20];
	char sayisim[20];
	
	int numara;
	
};

/*   struct ogrenci *degerAl(struct ogrenci *a) {
	
	strcpy(a->isim,"tarik");
	strcpy(a->sayisim,"calik");
	a->numara = 132;
	
	return a;
} */

void degerAl(struct ogrenci *a) {
	
	strcpy(a->isim,"tarik");
	strcpy(a->sayisim,"calik");
	a->numara = 132;
	
}

void goster (struct ogrenci *p) {
	printf("%s  %s  %d\n\n",p->isim,p->sayisim,p->numara);
	
}

int main () {
	
//	struct ogrenci *tut;
	struct ogrenci ogrenci1 = {"murat","bektas",189};	
	
	goster(&ogrenci1);
	
//	tut = degerAl(&ogrenci1);

degerAl(&ogrenci1);
	
	  printf("%s  %s  %d\n",ogrenci1.isim,ogrenci1.sayisim,ogrenci1.numara);
	
//  printf("%s  %s  %d\n",tut->isim,tut->sayisim,tut->numara);
	
	
	// Eğer void ile yapılsaydı gene olurdu,bunu göstermek için 2 kez yaptık.
	
	// 47.ders sonu.
	return 0;
}
