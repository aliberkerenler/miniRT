/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_validate2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerenler <aerenler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 15:21:27 by aerenler          #+#    #+#             */
/*   Updated: 2026/02/27 15:31:34 by aerenler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"
#include "../../include/minirt.h"
#include "../../include/vec3.h"
#include <stdlib.h>

int	parse_float_safe(const char *str, double *out, t_scene *scene,
		const char *err_msg)
{
	if (!str || !is_valid_float(str))
	{
		scene->error = 1;
		scene->err_msg = err_msg;
		return (0);
	}
	*out = ft_atof(str);
	return (1);
}

int	set_err(t_scene *scene, const char *msg)
{
	scene->error = 1;
	scene->err_msg = msg;
	return (0);
}

int	parse_vector_safe(char **tokens, int *index,
		t_vector *out, t_scene *scene)
{
	char	**coords;

	if (!validate_comma_format(tokens[*index], 3))
		return (set_err(scene, "Invalid vector format (expected x,y,z)"));
	coords = ft_split(tokens[*index], ',');
	if (!coords || !coords[0] || !coords[1] || !coords[2]
		|| !validate_vector_values(coords))
	{
		if (coords)
			free_split_arr(coords);
		return (set_err(scene, "Vector contains non-numeric values"));
	}
	out->x = ft_atof(coords[0]);
	out->y = ft_atof(coords[1]);
	out->z = ft_atof(coords[2]);
	free_split_arr(coords);
	(*index)++;
	return (1);
}

static int	fill_color_values(char **rgb, t_color *out)
{
	double	vals[3];

	vals[0] = ft_atof(rgb[0]);
	vals[1] = ft_atof(rgb[1]);
	vals[2] = ft_atof(rgb[2]);
	out->x = vals[0] / 255.0;
	out->y = vals[1] / 255.0;
	out->z = vals[2] / 255.0;
	return (1);
}

int	parse_color_safe(char **tokens, int *index,
		t_color *out, t_scene *scene)
{
	char	**rgb;

	if (!validate_comma_format(tokens[*index], 3))
		return (set_err(scene, "Invalid color format (expected R,G,B)"));
	rgb = ft_split(tokens[*index], ',');
	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2]
		|| !validate_color_values(rgb))
	{
		if (rgb)
			free_split_arr(rgb);
		return (set_err(scene, "Color must be integers [0,255]"));
	}
	fill_color_values(rgb, out);
	free_split_arr(rgb);
	(*index)++;
	return (1);
}
