#include<stdio.h>


int main () {
	
	int sayi;
	int i;
	int toplam = 0;
	
	
	for(i = 0;1;i++) {
		
		printf("Sayiyi giriniz: (Cikmak icin -1'e basin.')");
		scanf("%d",&sayi);
		
		
		if(sayi==-1){			
			break;			
		}
		toplam+=sayi;
		}	
	printf("%d",toplam);	
	
	//18.ders sonu.
	
	return 0;
}
