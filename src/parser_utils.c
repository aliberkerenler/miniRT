#include "../include/parser.h"
#include "../include/minirt.h"
#include <stdlib.h>

t_vector	parse_vector(char **tokens, int *index)
{
	t_vector	v;
	char		**coords;

	coords = ft_split(tokens[*index], ',');
	if (!coords || !coords[0] || !coords[1] || !coords[2])
		exit_error("Invalid vector format", ERR_PARSE_FORMAT);
	v.x = ft_atof(coords[0]);
	v.y = ft_atof(coords[1]);
	v.z = ft_atof(coords[2]);
	free_split_arr(coords);
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
	vals[0] = ft_atof(rgb[0]);
	vals[1] = ft_atof(rgb[1]);
	vals[2] = ft_atof(rgb[2]);
	free_split_arr(rgb);
	validate_color_range(vals[0], vals[1], vals[2]);
	c.x = vals[0] / 255.0;
	c.y = vals[1] / 255.0;
	c.z = vals[2] / 255.0;
	(*index)++;
	return (c);
}
