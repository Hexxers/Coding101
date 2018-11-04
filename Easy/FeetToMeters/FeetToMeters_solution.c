#include<stdio.h>

int main()
{
	int feet;
	double meters;
		
	printf("Enter a number of feet:\n");
	scanf("%d",&feet);
		
	//convert from feet to meters
	meters = (double)feet * 0.3;
		
	printf("It is equal to %d meters\n",meters);

	return 0;
}