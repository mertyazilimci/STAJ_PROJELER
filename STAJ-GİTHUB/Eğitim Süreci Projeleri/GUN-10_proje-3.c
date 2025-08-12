#include<stdio.h>
#include<string.h>


int benimstrlen (char *p) {
	int uzunluk = 0;
	int i=0;
	
		for(; p[i] != '\0';i++) {
			
			uzunluk ++;
			
			
		}
	return uzunluk;
}




int main (){
	 /*
	char yazi[] = "tura";
	 char *p = yazi;
	 
	 printf("%s\n",p);
	printf("%s",p+1);  */
	
	char yazi[] = "tura";
	 char *p = yazi;
	
	printf("%d",strlen(yazi));
	
	// 35. ders sonu.
	
	return 0;
}
