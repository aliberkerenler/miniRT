#include "../include/parser.h"
#include "../include/minirt.h"
#include <stdlib.h>

double	parse_double(const char *str)
{
	return (atof(str));
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
	free(coords[0]);
	free(coords[1]);
	free(coords[2]);
	free(coords);
	(*index)++;
	return (v);
}

t_color	parse_color(char **tokens, int *index)
{
	t_color		c;
	char		**rgb;

	rgb = ft_split(tokens[*index], ',');
	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2])
		exit_error("Invalid color format", ERR_PARSE_FORMAT);
	c.x = parse_double(rgb[0]) / 255.0;
	c.y = parse_double(rgb[1]) / 255.0;
	c.z = parse_double(rgb[2]) / 255.0;
	free(rgb[0]);
	free(rgb[1]);
	free(rgb[2]);
	free(rgb);
	(*index)++;
	return (c);
}
