/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerenler <aerenler@student.42istanbul.com.t+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 15:07:48 by aerenler          #+#    #+#             */
/*   Updated: 2026/02/27 15:47:42 by aerenler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"
#include "../../include/minirt.h"
#include "../../include/vec3.h"

void	parse_ambient(t_scene *scene, char **tokens)
{
	int	i;

	i = 1;
	if (!check_duplicate(scene, scene->has_ambient,
			"Duplicate ambient element"))
		return ;
	if (!check_token_count(scene, tokens, 3, "Invalid ambient format"))
		return ;
	if (!parse_float_safe(tokens[i], &scene->ambient.ratio, scene,
			"Ambient ratio is not a valid number"))
		return ;
	i++;
	if (scene->ambient.ratio < 0.0 || scene->ambient.ratio > 1.0)
	{
		scene->error = 1;
		scene->err_msg = "Ambient ratio must be in [0.0,1.0]";
		return ;
	}
	if (!parse_color_safe(tokens, &i, &scene->ambient.color, scene))
		return ;
	scene->has_ambient = 1;
}

static int	parse_cam_params(t_scene *scene, char **tokens, int *i)
{
	if (!parse_vector_safe(tokens, i, &scene->camera.position, scene))
		return (0);
	if (!parse_orientation_safe(tokens, i,
			&scene->camera.orientation, scene))
		return (0);
	if (vec3_length_squared(scene->camera.orientation) < 1e-9)
	{
		scene->error = 1;
		scene->err_msg = "Camera direction can't be zero vector";
		return (0);
	}
	scene->camera.orientation = vec3_normalize(scene->camera.orientation);
	return (1);
}

void	parse_camera(t_scene *scene, char **tokens)
{
	int	i;

	i = 1;
	if (!check_duplicate(scene, scene->has_camera,
			"Duplicate camera element"))
		return ;
	if (!check_token_count(scene, tokens, 4, "Invalid camera format"))
		return ;
	if (!parse_cam_params(scene, tokens, &i))
		return ;
	if (!parse_float_safe(tokens[i], &scene->camera.fov, scene,
			"FOV is not a valid number"))
		return ;
	if (scene->camera.fov < 0 || scene->camera.fov >= 180)
	{
		scene->error = 1;
		scene->err_msg = "FOV must be in range [0,180)";
		return ;
	}
	scene->has_camera = 1;
}
