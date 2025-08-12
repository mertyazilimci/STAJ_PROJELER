#include<stdio.h>


int main () {
	
	int vize1,vize2,final;
	float dersort;
	float okulortalama;
	printf("1.vize");
	scanf("%d",&vize1);
	printf("2.vize");
	scanf("%d",&vize2);
	printf("final");
	scanf("%d",&final);
	printf("Universite ortalamanizi giriniz.");
	scanf("%f",&okulortalama);
	
	dersort= (vize1*3/10.0 + vize2*3/10.0 + final*4/10.0);
	
	if( dersort >= 90 ) {
		
		printf("harf notunuz AA ve ders ortalamanýz %.2f",dersort);
		
	}
	else if ( dersort >= 85 && dersort <90 ) {
		
		printf("harf notunuz BA ve ders ortalamanýz %.2f",dersort);
		
	}
	else if ( dersort >= 80 && dersort <85 ) {
		
		printf("harf notunuz BB ve ders ortalamanýz %.2f",dersort);
		
	}
	else if ( dersort >= 75 && dersort <80 ) {
		
		printf("harf notunuz BC ve ders ortalamanýz %.2f",dersort);
		
	}
	else if ( dersort >= 70 && dersort <75 ) {
		
		printf("harf notunuz CC ve ders ortalamanýz %.2f\n",dersort);
		
		if(okulortalama < 2.5){
			
			printf("Dersi seneye yeniden almaniz iyi olur cunku ortalamaniz dusuk.");
			
		}		
	}
	else if ( dersort >= 65 && dersort <70 ) {
		
		printf("harf notunuz DC ve ders ortalamanýz %.2f\n",dersort);
		
		if(okulortalama < 2.5){
			
			printf("Dersi seneye yeniden almaniz iyi olur cunku ortalamaniz dusuk.");
			
		}		
	}
	else if ( dersort >= 60 && dersort <65 ) {
		
		printf("harf notunuz DD ve ders ortalamanýz %.2f\n",dersort);
		
		if(okulortalama < 2.5){
			
			printf("Dersi seneye yeniden almaniz iyi olur cunku ortalamaniz dusuk.");
			
		}		
	}
	else {
		
		printf("Harf notunuz FF ve ders ortalamaniz %.2f\n",dersort);
		printf("Dersten kaldiniz");
	}
	
	//12.DERS SONU.
	
	return 0;
}
