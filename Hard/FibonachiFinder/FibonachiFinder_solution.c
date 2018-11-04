#include <stdio.h>

int fibo(int num)
{
    if (num == 0)
    {
        return 0;
    }

    else if (num == 1)
    {
        return 1;
    }

    else
    {
        return(fibo(num - 1) + fibo(num - 2));
    }
}

int main()
{
    int num;
    int result;

    printf("Enter the element you wish to find:\n");
    scanf("%d", &num);

    result = fibo(num);
    printf("The %dth number in the Fibonacci series is %d\n", num, result);

    return 0;
}
