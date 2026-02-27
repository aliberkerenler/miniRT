/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_validate4.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerenler <aerenler@student.42istanbul.com.t+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 16:00:00 by aerenler          #+#    #+#             */
/*   Updated: 2026/02/27 15:48:26 by aerenler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"
#include "../../include/minirt.h"

int	check_duplicate(t_scene *scene, int has_flag, const char *msg)
{
	if (has_flag)
		return (set_err(scene, msg));
	return (1);
}

int	check_token_count(t_scene *scene, char **tokens,
		int expected, const char *msg)
{
	if (count_tokens(tokens) != expected)
		return (set_err(scene, msg));
	return (1);
}
