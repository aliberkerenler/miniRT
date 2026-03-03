/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_light.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerenler <aerenler@student.42istanbul.com.t+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 16:00:00 by aerenler          #+#    #+#             */
/*   Updated: 2026/03/03 23:50:48 by aerenler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"
#include "../../include/minirt.h"
#include "../../include/vec3.h"

static int	create_light(t_scene *scene, char **tokens, int *i)
{
	if (!parse_vector_safe(tokens, i, &scene->light.position, scene))
		return (0);
	if (!parse_float_safe(tokens[*i], &scene->light.brightness, scene,
			"Light brightness is not a valid number"))
		return (0);
	if (scene->light.brightness < 0.0 || scene->light.brightness > 1.0
		|| exceeds_int_value(tokens[*i], 1))
	{
		scene->error = 1;
		scene->err_msg = "Light brightness must be in [0.0,1.0]";
		return (0);
	}
	(*i)++;
	if (!parse_color_safe(tokens, i, &scene->light.color, scene))
		return (0);
	return (1);
}

void	parse_light(t_scene *scene, char **tokens)
{
	int		i;

	i = 1;
	if (!check_duplicate(scene, scene->has_light,
			"Duplicate light element"))
		return ;
	if (!check_token_count(scene, tokens, 4, "Invalid light format"))
		return ;
	if (!create_light(scene, tokens, &i))
		return ;
	scene->has_light = 1;
}
