/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerenler <aerenler@student.42istanbul.com.t+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 15:08:47 by aerenler          #+#    #+#             */
/*   Updated: 2026/02/22 15:08:48 by aerenler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/vec3.h"

t_ray	ray(t_point origin, t_vector direction)
{
	t_ray	r;

	r.origin = origin;
	r.direction = direction;
	return (r);
}

t_point	ray_at(t_ray r, double t)
{
	return (vec3_add(r.origin, vec3_mul(r.direction, t)));
}
