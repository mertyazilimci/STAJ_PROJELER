#include<stdio.h>
#define MAX 50

void bubblesort(int array[],int boyut){
	int i,j;
	
	for(i=0;i<boyut;i++) {
		
		for(j=1;j<boyut-i;j++) {   // j ve bir önceki karþýlaþtýrýlacak o yüzden 1 den baþladý.her turdan sonra dizi boyutu 1'er 1'er küçülmeli o yüzden j<boyut-i;
			
			if (array[j-1]>array[j]){  
				
				int temp = array[j];
				array[j] = array[j-1];
				array[j-1] = temp;
				
			}
		}
		
	}	
}

int main()  {
	int boyut[MAX],size;
	int i;
	
	printf("Kac elemanlý?\n");
	scanf("%d",&size);
	 
	 for (i=0;i<size;i++){
	 	
	 	scanf("%d",&boyut[i]);
	 	
	 }
	
	bubblesort(boyut,size);
	
	for (i=0;i<size;i++){
	 	
	 	printf("%d  ",boyut[i]);
	 	
	 }
	
	
	// 38.ders sonu.
	
	return 0;
}
