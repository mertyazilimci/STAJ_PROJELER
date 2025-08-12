#include<stdio.h> 



int main ()  {
	
	FILE *filep;
	filep= fopen("yaz.txt","a");
	char text [256];
	
	if(filep == NULL) {
		
	printf("Dosya olusturulamadi.\n");
		
	}
	
	else {
		printf("Bir sey yazin:\n");	
		fgets(text,256,stdin);
		fputs(text,filep);
		
		printf("Dosya yazildi.\n");
		fclose(filep);			
	}
	
	// 50.Ders sonu.
	
	return 0;
}
