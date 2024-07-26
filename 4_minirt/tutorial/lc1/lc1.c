#include <stdio.h>

int main(void)
{
	int	i;
	int	j;
	double r;
	double g;
	double b;
	int	width;
	int	height;

	width = 256;
	height = 256;
	printf("P3\n%d %d\n255\n", width, height);
	j = 0;
	while (j <= 255)
	{
		i = 0;
		while (i < width)
		{
			r = (double)i / (width - 1);
			b = 0;
			//b = (double)j / (height - 1);
			g = 0;
			printf("%d %d %d\n", (int)(255.999 * r), (int)(255.999 * g), (int)(255.999 * b));
			i++;
		}
		j++;
	}
	return (0);
}
