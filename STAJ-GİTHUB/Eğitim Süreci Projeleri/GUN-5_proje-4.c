#include<stdio.h>




int main () {
	
	/*  FOR �LE 10'A KADAR OLAN ��FT SAYILARIN TOPLAMI.
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
	
	
	// WH�LE �LE 10'A KADAR OLAN ��FT SAYILARIN TOPLAMI.
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
