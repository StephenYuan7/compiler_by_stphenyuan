#include <stdio.h>

void Swap ( int x, int y )
{ 
	int temp;
	
	temp=x; 
	x=y; 
	y=temp;
} 

int main()
{
	int x=10, y=20;

	Swap( x, y );
	printf("x=%d, y=%d", x, y);
	
	return 0;
}
