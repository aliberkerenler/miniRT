/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_validate3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerenler <aerenler@student.42istanbul.com.t+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 16:00:00 by aerenler          #+#    #+#             */
/*   Updated: 2026/02/27 15:48:26 by aerenler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"
#include "../../include/minirt.h"
#include <stdlib.h>

int	validate_color_values(char **rgb)
{
	int	i;
	int	val;

	i = 0;
	while (i < 3)
	{
		if (!is_valid_int(rgb[i]))
			return (0);
		val = ft_atoi(rgb[i]);
		if (val < 0 || val > 255)
			return (0);
		i++;
	}
	return (1);
}

int	validate_vector_values(char **coords)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (!is_valid_float(coords[i]))
			return (0);
		i++;
	}
	return (1);
}

int	count_tokens(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
		i++;
	return (i);
}

int	parse_orientation_safe(char **tokens, int *index,
		t_vector *out, t_scene *scene)
{
	if (!parse_vector_safe(tokens, index, out, scene))
		return (0);
	if (out->x < -1.0 || out->x > 1.0
		|| out->y < -1.0 || out->y > 1.0
		|| out->z < -1.0 || out->z > 1.0)
		return (set_err(scene, "Orientation must be in [-1,1]"));
	return (1);
}
