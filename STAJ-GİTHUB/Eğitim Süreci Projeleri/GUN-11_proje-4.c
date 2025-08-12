#include<stdio.h>
#define MAX 50

/* 5  2  3  1  7  olsun. i=1,element=2,j=0 oluyor. j=0 ve 5>2 olduðu için döngüye girdik.
Döngüde arr[1](1. index) = arr[0] (0. index) : 1. index'i 5 yaptýk ve j= -1 yaptýk.
Koþulu saðlamadýðý için döngüye devam edemedik ve döngüden çýktýkk. arr[-1+1] = 5 iþlemi: 0.index'in deðerini eleman yani 2 yaptýk.
i=2,element=3,j=1 oldu ve bu þwkilde devam etti iþlemler. */

void insertionsort(int arr[],int size) {
	int element;
	int i,j;
	for(i=1;i<size;i++) {
		element= arr[i];
		j= i-1;
		while (j>= 0 && arr[j] > element) {
			arr[j+1] = arr[j];
			j--;
		}
		arr[j+1] = element;
	}
	
	
}

int main () {
	
	int boyut[MAX],size;
	int i;
	
	printf("Kac elemanlý?\n");
	scanf("%d",&size);
	 
	 for (i=0;i<size;i++){
	 	
	 	scanf("%d",&boyut[i]);
	 	
	 }
	
	insertionsort(boyut,size);
	
	for (i=0;i<size;i++){
	 	
	 	printf("%d  ",boyut[i]);
	 	
	 }
	
	//40.ders sonu.
	
	return 0;
}
