#include<stdio.h>
#define MAX 50

/* 5  2  3  1  7  olsun. i=1,element=2,j=0 oluyor. j=0 ve 5>2 oldu�u i�in d�ng�ye girdik.
D�ng�de arr[1](1. index) = arr[0] (0. index) : 1. index'i 5 yapt�k ve j= -1 yapt�k.
Ko�ulu sa�lamad��� i�in d�ng�ye devam edemedik ve d�ng�den ��kt�kk. arr[-1+1] = 5 i�lemi: 0.index'in de�erini eleman yani 2 yapt�k.
i=2,element=3,j=1 oldu ve bu �wkilde devam etti i�lemler. */

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
	
	printf("Kac elemanl�?\n");
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
