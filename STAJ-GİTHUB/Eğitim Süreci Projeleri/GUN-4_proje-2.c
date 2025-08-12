#include<stdio.h>


int main() {
	
	int islem;
	int tutar;
	int bakiye = 1000;
	
	printf("ISLEMLER\n1:Para Cekme\n2:Para Yatirma\n3:Havale Yapma\n4:Bakiye Sorgulama\n5:Kart Iade\n\n\n");
	
	printf("Islem seciniz\n");
	scanf("%d",&islem);
	
	switch(islem) {
		
		case 1:
			 printf("Bakiyeniz: %d\n",bakiye);
			printf("Cekilecek tutar:\n");
			scanf("%d",&tutar);
			if(tutar>bakiye) {
				printf("Bakiyeniz yetersiz.\n");
			}
			bakiye -= tutar;
			printf("Bakiyeniz: %d",bakiye);
			break;
			
			case 2:
				printf("Bakiyeniz: %d\n",bakiye);
			printf("Yatirilacak tutar:\n");
			scanf("%d",&tutar);
			bakiye += tutar;
			printf("Bakiyeniz: %d",bakiye);
			break;
								
				case 3:
					printf("Bakiyeniz: %d\n",bakiye);
			printf("Havale Yapilacak tutar:\n");
			scanf("%d",&tutar);
			if(tutar>bakiye) {
				printf("Havale Basarisiz.Cunku bakiyeniz yetersiz.\n");
			}
			bakiye -= tutar;
			printf("Bakiyeniz: %d",bakiye);
			break;
					case 4:
						
						printf("Bakiyeniz: %d",bakiye);
			break;
						
						case 5:
							
							printf("Kart Iade Edildi.");
							break;
							
							default :
								
								
		
		printf("Bilinmeyen Islem.");
		
		break;
		
	}
	
	
	
	
	
	
	
	
	return 0;
}
