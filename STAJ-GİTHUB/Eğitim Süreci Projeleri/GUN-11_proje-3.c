#include<stdio.h>
#define MAX 50

void selectionsort(int arr[],int boyut) {
	int minimumindex;
	int i,j;
	for (i=0;i<boyut;i++) {
		minimumindex = i; //her turda bir sonraki indexten baþlamamýz için.i=0 0.index sonraki tur i=1 oluyor ve biz 1. indexten baþlayýp devam ediyoruz.
		for(j=i+1;j<boyut;j++) { // minimumindex ile diðerlarini karþýlaþtýrmaya baþlamak için j=i+1.her tur zaten j artýyor ve inexin tmamýný gezmiþ oluyoz ve o turun en küçüðünü buluyoruz.
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
	
	printf("Kac elemanlý?\n");
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
