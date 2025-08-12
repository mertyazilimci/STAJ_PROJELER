#include<stdio.h>


int main()  {
	
	// int matris[3][3] = {{1,2,3},{4,5,6},{7,8,9}};
	int i,j;
	int matris [3][3];
//	printf("%d",matris[2][2]);
	
 /*	for(i=0;i<3;i++){
		for (j=0;j<3;j++){
			printf("%d ",matris[i][j]);
		}
		printf("\n");
	}
*/	

printf("9 adet sayi giriniz.\n");
for (i=0;i<3;i++) {
	
	for(j=0;j<3;j++) {
		scanf("%d",&matris[i][j]);
	}
	
}

for (i=0;i<3;i++) {
	
	for(j=0;j<3;j++) {
		printf("%d ",matris[i][j]);
	}
	
}
	// 23.ders sonu.
	return 0;
}
