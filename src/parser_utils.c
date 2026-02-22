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

static double	ft_atof(const char *str)
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

double	parse_double(const char *str)
{
	return (ft_atof(str));
}

static void	free_split(char **arr)
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

t_vector	parse_vector(char **tokens, int *index)
{
	t_vector	v;
	char		**coords;

	coords = ft_split(tokens[*index], ',');
	if (!coords || !coords[0] || !coords[1] || !coords[2])
		exit_error("Invalid vector format", ERR_PARSE_FORMAT);
	v.x = parse_double(coords[0]);
	v.y = parse_double(coords[1]);
	v.z = parse_double(coords[2]);
	free_split(coords);
	(*index)++;
	return (v);
}

static void	validate_color_range(double r, double g, double b)
{
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		exit_error("Color values must be in range [0,255]", ERR_PARSE_FORMAT);
}

t_color	parse_color(char **tokens, int *index)
{
	t_color		c;
	char		**rgb;
	double		vals[3];

	rgb = ft_split(tokens[*index], ',');
	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2])
		exit_error("Invalid color format", ERR_PARSE_FORMAT);
	vals[0] = parse_double(rgb[0]);
	vals[1] = parse_double(rgb[1]);
	vals[2] = parse_double(rgb[2]);
	free_split(rgb);
	validate_color_range(vals[0], vals[1], vals[2]);
	c.x = vals[0] / 255.0;
	c.y = vals[1] / 255.0;
	c.z = vals[2] / 255.0;
	(*index)++;
	return (c);
}
