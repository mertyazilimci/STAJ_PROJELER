#include<stdio.h>
#define MAX 50

void selectionsort(int arr[],int boyut) {
	int minimumindex;
	int i,j;
	for (i=0;i<boyut;i++) {
		minimumindex = i; //her turda bir sonraki indexten ba�lamam�z i�in.i=0 0.index sonraki tur i=1 oluyor ve biz 1. indexten ba�lay�p devam ediyoruz.
		for(j=i+1;j<boyut;j++) { // minimumindex ile di�erlarini kar��la�t�rmaya ba�lamak i�in j=i+1.her tur zaten j art�yor ve inexin tmam�n� gezmi� oluyoz ve o turun en k�����n� buluyoruz.
			if(arr[j]<arr[minimumindex]) {
				
				minimumindex = j;
			}
		}
		int temp = arr[i];
		arr[i]= arr[minimumindex];
        arr[minimumindex]= temp;		
	}
	
	
}

int main ()  {
	
	int boyut[MAX],size;
	int i;
	
	printf("Kac elemanl�?\n");
	scanf("%d",&size);
	 
	 for (i=0;i<size;i++){
	 	
	 	scanf("%d",&boyut[i]);
	 	
	 }
	
	selectionsort(boyut,size);
	
	for (i=0;i<size;i++){
	 	
	 	printf("%d  ",boyut[i]);
	 	
	 }
	
	// 39.ders sonu.
	return 0;
}
