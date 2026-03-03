/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_validate4.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerenler <aerenler@student.42istanbul.com.t+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 16:00:00 by aerenler          #+#    #+#             */
/*   Updated: 2026/03/03 23:58:27 by aerenler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"
#include "../../include/minirt.h"

static int	has_nonzero_fraction(const char *str)
{
	int	i;
	int	found_dot;

	i = 0;
	found_dot = 0;
	while (str[i])
	{
		if (str[i] == '.')
			found_dot = 1;
		else if (found_dot && str[i] >= '1' && str[i] <= '9')
			return (1);
		i++;
	}
	return (0);
}

int	exceeds_int_value(const char *str, int boundary)
{
	int	int_part;
	int	i;
	int	sign;

	i = 0;
	sign = 1;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	int_part = 0;
	while (str[i] >= '0' && str[i] <= '9')
		int_part = int_part * 10 + (str[i++] - '0');
	int_part *= sign;
	if (int_part > boundary)
		return (1);
	if (int_part == boundary && has_nonzero_fraction(str))
		return (1);
	return (0);
}

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
