#include "map.h"

double  ft_atof(char *num)
{
    double  result;
    double  sign;
    double     mult;
    int     dot_flag;
    int     i;

    i = 0;
    mult = 1.0;
    dot_flag = 0;
    result = 0.0;
    sign = 1.0;
    if (num[0] == '-')
    {
        sign = -1.0;
        i++;
    }
	while (num[i] != '\0')
	{
        if (!(ft_isdigit(num[i]) || num[i] == '.'))
            error_exit();
        if (num[i] == '.')
            dot_flag = 1;
        else if (dot_flag == 0)
        {
            result *= 10;
            result += num[i];
        }
        else
            result += num[i] * pow(0.1, mult++);
		if (result < 0 && sign == 1)
			return (-1);
		else if (result < 0 && sign == -1)
			return (0);
		i++;
	}
	return ((int)(sign * result));
}
