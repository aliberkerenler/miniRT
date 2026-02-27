/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_objects.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerenler <aerenler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 15:07:38 by aerenler          #+#    #+#             */
/*   Updated: 2026/02/27 15:27:07 by aerenler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"
#include "../../include/minirt.h"
#include "../../include/vec3.h"
#include "../../include/render.h"

static t_sphere	*new_sphere(char **tokens, int *i, t_scene *scene)
{
	t_sphere	*sphere;
	double		diameter;

	sphere = malloc(sizeof(t_sphere));
	if (!sphere)
		exit_error("Memory allocation failed", ERR_MALLOC);
	if (!parse_vector_safe(tokens, i, &sphere->center, scene))
		return (free(sphere), NULL);
	if (!parse_float_safe(tokens[*i], &diameter, scene,
			"Sphere diameter is not a valid number"))
		return (free(sphere), NULL);
	(*i)++;
	if (diameter <= 0)
	{
		free(sphere);
		scene->error = 1;
		scene->err_msg = "Sphere diameter must be positive";
		return (NULL);
	}
	sphere->radius = diameter / 2.0;
	if (!parse_color_safe(tokens, i, &sphere->color, scene))
		return (free(sphere), NULL);
	return (sphere);
}

void	parse_sphere(t_scene *scene, char **tokens)
{
	t_sphere	*sphere;
	t_object	*obj;
	int			i;

	i = 1;
	if (count_tokens(tokens) != 4)
	{
		scene->error = 1;
		scene->err_msg = "Invalid sphere format (expected: sp pos diam R,G,B)";
		return ;
	}
	sphere = new_sphere(tokens, &i, scene);
	if (!sphere)
		return ;
	obj = malloc(sizeof(t_object));
	if (!obj)
		exit_error("Memory allocation failed", ERR_MALLOC);
	obj->type = OBJ_SPHERE;
	obj->data = sphere;
	add_object(scene, obj);
}
