#include "../include/parser.h"
#include "../include/minirt.h"
#include <stdlib.h>

static double	ft_atof_decimal(const char *str, int i)
{
	double	result;
	double	fraction;

	result = 0.0;
	fraction = 0.1;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result += (str[i] - '0') * fraction;
		fraction *= 0.1;
		i++;
	}
	return (result);
}

double	ft_atof(const char *str)
{
	int		i;
	int		sign;
	double	result;

	i = 0;
	sign = 1;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	result = 0.0;
	while (str[i] >= '0' && str[i] <= '9')
		result = result * 10.0 + (str[i++] - '0');
	if (str[i] == '.')
		result += ft_atof_decimal(str, i + 1);
	return (result * sign);
}

void	free_split_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}
