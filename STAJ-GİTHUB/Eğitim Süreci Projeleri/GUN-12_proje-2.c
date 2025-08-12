#include<stdio.h>

struct Araba {
	int tekersayisi;
	int vitessayisi;
	int model;
	
	float motor;
	
	int beygir;
	
};

int main()   {
	
struct Araba araba1 = {4,6,2011,3.0,300};
 struct Araba araba2 = araba1;
	
	
	printf("%d  %d  %d  %f  %d\n",araba1.tekersayisi,araba1.vitessayisi,araba1.model,araba1.motor,araba1.beygir);
	printf("%d  %d  %d  %f  %d\n",araba2.tekersayisi,araba2.vitessayisi,araba2.model,araba2.motor,araba2.beygir);
	
	// 42.ders sonu.
	
	return 0;
}
