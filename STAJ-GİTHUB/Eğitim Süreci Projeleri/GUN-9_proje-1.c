#include<stdio.h>
#include<string.h>


/*
int isimuzunluk (char name[]){
	
	int uzunluk=0;
	int i;
	
	for(i=0;name[i] != '\0';i++ ){
		uzunluk++;
	}
	return uzunluk;
}  */

void terscevir (char name[]){
	
	int i,uzunluk,gecici;
	// veya  char gecici;  de çalisiyor.
	uzunluk = strlen(name);
	
	for(i=0;i<uzunluk/2;i++){
		
		gecici=name[i];
		name[i]=name[uzunluk-1-i];
		name[uzunluk-1-i]=gecici;
	}
	
}


int main () {
	/*
	char isim[] ="Mustafa";
	
	printf("%d",isimuzunluk(isim));  */
	
	char text [200];
	
	scanf("%s",&text);
	
	terscevir(text);
	printf("%s",text);
	
	
	// 29.Ders sonu.
	
	
	return 0;
}
