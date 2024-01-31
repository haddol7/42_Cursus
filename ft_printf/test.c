#include <stdio.h>
#include <limits.h>
#include "ft_printf.h"

/*
struct a
{
	int num;
} typedef n;

int test3(va_list ap)
{
	int a;

	a = va_arg(ap, int);
	printf("%p3\n", ap);
}

int test2(va_list ap)
{
	int a;

	a = va_arg(ap, int);
	printf("%p2\n", ap);
	test3(ap);
}

int test1(int n, ...)
{
	int a;

	va_list	ap;
	va_start(ap, n);
	printf("%p1\n",ap);
	test2(ap);
	a = va_arg(ap, int);
	printf("%p4\n",ap);
	va_end(ap);
}

void test(n *b)
{
	b->num = 10;
}
*/

int main(int argc, char **argv)
{
	unsigned int a;

	a = 2147483647;

	char *str = "%p\n";
	ft_printf("%p", &a);

//	printf("\nprintf : %d\n", printf("%01.u" , 0));
//	printf("\nft_printf : %d\n", ft_printf("%01.u" , 0));
	// printf("%s\n", argv[1]);
	// printf("\n%d", printf(argv[1], 10));
}

