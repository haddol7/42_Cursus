#include "../../inc/map.h"

// int	ft_isdigit(int c)
// {
// 	if (c >= '0' && c <= '9')
// 		return (1);
// 	return (0);
// }

// void    error_exit(void)
// {
//     write(1, "Error\n", 6);
//     exit(1);
// }

static void	init_var(t_num *info, double *result, int *i)
{
	info->dot_flag = 0;
	info->mult = 1.0;
	info->sign = 1.0;
	*result = 0.0;
	*i = 0;
}

static void	is_neg(char *num, t_num *info, int *i)
{
	if (num[0] == '-')
	{
		info->sign = -1.0;
		(*i)++;
	}
}

static void	add_num(double *res, char *num, int i, t_num *info)
{
	double	result;
	
	result = *res;
	if (num[i] == '.')
		info->dot_flag = 1;
	else if (info->dot_flag == 0)
	{
		result *= 10.0;
		result += num[i] - '0';
	}
	else
	{
		result += (num[i] - '0') * pow(0.1, info->mult++);
		if (info->mult > 10)
			error_exit("add_num\n");
	}
	*res = result;
}
// #include <stdio.h>
double	ft_atof(char *num)
{
	double	result;
	t_num	info;
	int		i;

	init_var(&info, &result, &i);
	is_neg(num, &info, &i);
	dprintf(2, "%s\n", num);
	while (!(num[i] == '\0' || num[i] == '\n'))
	{
		// printf("%f\n", result);
		if (!(ft_isdigit(num[i]) || num[i] == '.'))
			error_exit("ft_atof : not a digit");//TODO .ㅇㅣ 없는 정수값에서 뭔가 이상이 생긴다.
		add_num(&result, num, i, &info);
		if (result > INT_MAX || result < INT_MIN)
			error_exit("ft_atof : too big");
		i++;
	}
	// printf("%f :::: last\n", result);
	return (result * info.sign);
}

// int main(void)
// {
//     double num;

//     num = ft_atof("0.0");
//     printf("%f\n", num);
//     num = ft_atof("2147483648");
//     printf("%f\n", num);
// }
