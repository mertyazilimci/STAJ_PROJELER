#include<stdio.h>


/*
int carp (int matris[],int size) {
	
  int carpim=1;	
	int i=0;
	for (;i<size;i++){
		
		carpim *= matris[i];
	}
	
	return carpim;
	
}
*/

void neh (int matrisimiz[][4],int size) {
	
	int i,j;
	for(i=0;i<size;i++){
		
		for(j=0;j<4;j++){
			printf("%d ",matrisimiz[i][j]);
		}
		printf("\n");
	}
}



int main() {
/*
 int sayilar[5]={1,2,3,4,5};

printf("%d",carp(sayilar,5));
*/
int matris[3][4];
int i,j;

printf("Matrisi Doldurunuz.");	

for (i=0;i<3;i++) {
	
	for(j=0;j<4;j++){
		scanf("%d",&matris[i][j]);
	}
}
	neh(matris,3);
	
	//28.DERS SONU.
	
	return 0;
}
