/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_validate.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerenler <aerenler@student.42istanbul.com.t+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 12:00:00 by aerenler          #+#    #+#             */
/*   Updated: 2026/03/03 23:58:27 by aerenler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"
#include "../../include/minirt.h"
#include <float.h>
#include <stdlib.h>

int	is_valid_int(const char *str)
{
	int	i;
	int	has_digit;

	if (!str || !str[0])
		return (0);
	i = 0;
	has_digit = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		has_digit = 1;
		i++;
	}
	return (has_digit);
}

int	is_valid_float(const char *str)
{
	int	i;
	int	has_digit;
	int	has_dot;

	if (!str || !str[0])
		return (0);
	i = 0;
	has_digit = 0;
	has_dot = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (str[i] < '0' || str[i] > '9')
		return (0);
	while (str[i])
	{
		if (str[i] == '.' && !has_dot)
			has_dot = 1;
		else if (str[i] >= '0' && str[i] <= '9')
			has_digit = 1;
		else
			return (0);
		i++;
	}
	return (has_digit);
}

static int	count_fields(const char *str, char delim)
{
	int	count;
	int	i;

	if (!str || !str[0])
		return (0);
	count = 1;
	i = 0;
	while (str[i])
	{
		if (str[i] == delim)
			count++;
		i++;
	}
	return (count);
}

static int	has_empty_field(const char *str, char delim)
{
	int	i;

	if (!str || !str[0])
		return (1);
	if (str[0] == delim)
		return (1);
	i = 0;
	while (str[i])
	{
		if (str[i] == delim && (!str[i + 1] || str[i + 1] == delim))
			return (1);
		i++;
	}
	return (0);
}

int	validate_comma_format(const char *str, int expected_count)
{
	if (!str)
		return (0);
	if (has_empty_field(str, ','))
		return (0);
	if (count_fields(str, ',') != expected_count)
		return (0);
	return (1);
}
