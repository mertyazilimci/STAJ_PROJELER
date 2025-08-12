#include<stdio.h> 
#include<string.h>


int main()  {
	char veri[25] = "Yazilim Bilimi.";
	int i;
	int uzunluk = strlen(veri);
	
	FILE *filep = fopen("yazilimbilimi.txt","w");
	
	if(filep == NULL) {
		
		printf("Dosya olusturulamadi.\n");
		
	}
	
	else {
				
	for (i=0;i<uzunluk;i++) {
		
		fputc(veri[i],filep);
		printf("Yazilan karakter: %c \n",veri[i]);
		
	}	
	printf("Dosya basariyla yazdirildi.\n");
		fclose(filep);
	}
	
	
	// 49. Ders sonu.
	
	return 0;
}
