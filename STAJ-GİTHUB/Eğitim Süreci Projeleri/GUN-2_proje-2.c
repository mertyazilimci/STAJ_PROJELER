#include<stdio.h>


int main () {
	
	int x = 5;
	int y = 7;
	int a = 2;
	
	x=y;
	
	y = x+a+1;
	
	printf("x:%d\ny:%d\na:%d\n",x,y,a);
	
	
	x= 4;
	y= 5;
	a= 6;
	
	printf("\nx:%d\ny:%d\na:%d\n",--x,++y,a++);
	printf("\nx:%d\ny:%d\na:%d\n",x,y,a);
    printf("\nx:%d\ny:%d\na:%d\n",x--,--y,a--); 	
	/*   x=2  a=6
	x= x + (a+1); 

	*/
   x += (a+1);
   
   printf("\nx:%d\n",x);
   
   x = y = a+4;
   
   printf("\nx:%d\ny:%d\na:%d\n",x,y,a);

// 5.ders sonu.
	
	
	return 0;
}
