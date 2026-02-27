/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_plane.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerenler <aerenler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 15:07:43 by aerenler          #+#    #+#             */
/*   Updated: 2026/02/27 15:11:30 by aerenler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"
#include "../../include/minirt.h"
#include "../../include/vec3.h"
#include "../../include/render.h"

void	add_object(t_scene *scene, t_object *obj)
{
	obj->next = scene->objects;
	scene->objects = obj;
}

static t_plane	*new_plane(char **tokens, int *i, t_scene *scene)
{
	t_plane		*plane;

	plane = malloc(sizeof(t_plane));
	if (!plane)
		exit_error("Memory allocation failed", ERR_MALLOC);
	if (!parse_vector_safe(tokens, i, &plane->point, scene))
		return (free(plane), NULL);
	if (!parse_orientation_safe(tokens, i, &plane->normal, scene))
		return (free(plane), NULL);
	if (vec3_length_squared(plane->normal) < 1e-9)
	{
		free(plane);
		scene->error = 1;
		scene->err_msg = "Plane normal vector can't be zero";
		return (NULL);
	}
	plane->normal = vec3_normalize(plane->normal);
	if (!parse_color_safe(tokens, i, &plane->color, scene))
		return (free(plane), NULL);
	return (plane);
}

void	parse_plane(t_scene *scene, char **tokens)
{
	t_plane		*plane;
	t_object	*obj;
	int			i;

	i = 1;
	if (count_tokens(tokens) != 4)
	{
		scene->error = 1;
		scene->err_msg = "Invalid plane format (expected: pl pos normal R,G,B)";
		return ;
	}
	plane = new_plane(tokens, &i, scene);
	if (!plane)
		return ;
	obj = malloc(sizeof(t_object));
	if (!obj)
		exit_error("Memory allocation failed", ERR_MALLOC);
	obj->type = OBJ_PLANE;
	obj->data = plane;
	add_object(scene, obj);
}
