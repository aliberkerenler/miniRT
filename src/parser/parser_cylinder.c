/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cylinder.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerenler <aerenler@student.42istanbul.com.t+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 16:00:00 by aerenler          #+#    #+#             */
/*   Updated: 2026/02/27 17:23:16 by aerenler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"
#include "../../include/minirt.h"
#include "../../include/vec3.h"
#include "../../include/render.h"

static int	check_cylinder_axis(t_cylinder *cy, t_scene *scene)
{
	if (vec3_length_squared(cy->axis) < 1e-9)
	{
		free(cy);
		scene->error = 1;
		scene->err_msg = "Cylinder axis vector can't be zero";
		return (0);
	}
	cy->axis = vec3_normalize(cy->axis);
	return (1);
}

static int	parse_cy_dims(t_cylinder *cy, char **tokens, int *i,
		t_scene *scene)
{
	double	diameter;

	if (!parse_float_safe(tokens[*i], &diameter, scene,
			"Cylinder diameter is not a valid number"))
		return (free(cy), 0);
	(*i)++;
	if (!parse_float_safe(tokens[*i], &cy->height, scene,
			"Cylinder height is not a valid number"))
		return (free(cy), 0);
	(*i)++;
	if (diameter <= 0 || cy->height <= 0)
	{
		free(cy);
		scene->error = 1;
		scene->err_msg = "Cylinder diameter must be positive";
		return (0);
	}
	cy->radius = diameter / 2.0;
	return (1);
}

static t_cylinder	*new_cylinder(char **tokens, int *i, t_scene *scene)
{
	t_cylinder	*cy;

	cy = malloc(sizeof(t_cylinder));
	if (!cy)
		exit_error("Memory allocation failed", ERR_MALLOC);
	if (!parse_vector_safe(tokens, i, &cy->center, scene))
		return (free(cy), NULL);
	if (!parse_orientation_safe(tokens, i, &cy->axis, scene))
		return (free(cy), NULL);
	if (!check_cylinder_axis(cy, scene))
		return (NULL);
	if (!parse_cy_dims(cy, tokens, i, scene))
		return (NULL);
	if (!parse_color_safe(tokens, i, &cy->color, scene))
		return (free(cy), NULL);
	return (cy);
}

void	parse_cylinder(t_scene *scene, char **tokens)
{
	t_cylinder	*cylinder;
	t_object	*obj;
	int			i;

	i = 1;
	if (count_tokens(tokens) != 6)
	{
		scene->error = 1;
		scene->err_msg = "Invalid cylinder format";
		return ;
	}
	cylinder = new_cylinder(tokens, &i, scene);
	if (!cylinder)
		return ;
	obj = malloc(sizeof(t_object));
	if (!obj)
		exit_error("Memory allocation failed", ERR_MALLOC);
	obj->type = OBJ_CYLINDER;
	obj->data = cylinder;
	add_object(scene, obj);
}
