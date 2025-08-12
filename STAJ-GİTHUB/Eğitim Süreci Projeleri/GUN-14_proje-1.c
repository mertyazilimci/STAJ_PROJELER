#include<stdio.h> 



int main()  {
	

/*  FILE *filep = fopen("yazilimbilimi.txt","w");
  
  if(filep == NULL) {
  	
  	printf("Dosya olusturulamadi.\n");
  	
  }
  else {
  	
  	printf("Dosya olusturuldu.\n");
  	
  }   */


  FILE *filep = fopen("yazilimbilimi.txt","r");
  
  if(filep == NULL) {
  	
  	printf("Oyle bir dosya yok.\n");
  	
  }
  else {
  	
  	printf("Dosya var.\n");
}
 
 // 48.ders sonu.
return 0;
}
