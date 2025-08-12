#include<stdio.h>




int main () {
	
	/*  FOR ÝLE 10'A KADAR OLAN ÇÝFT SAYILARIN TOPLAMI.
	 int i;
	      int toplam = 0;
	for(i=0;i<=10;i++){
		
		if(i%2==1){
			
			continue;
		}
		
		toplam +=i;
		
	}
	printf("%d",toplam);
	*/
	
	
	// WHÝLE ÝLE 10'A KADAR OLAN ÇÝFT SAYILARIN TOPLAMI.
	int toplam = 0;
	int i= 0;
	
	while(i<=10){
		if(i%2==1){
			i++;
			continue;
		}
		
		toplam +=i;
		i++;
	}
	printf("%d",toplam);
	
	//19.DERS SONU.
	
	return 0;
}
