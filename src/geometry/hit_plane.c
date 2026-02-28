/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_plane.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerenler <aerenler@student.42istanbul.com.t+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 15:07:07 by aerenler          #+#    #+#             */
/*   Updated: 2026/02/22 15:07:08 by aerenler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/render.h"
#include "../../include/vec3.h"

bool	hit_plane(t_plane *plane, t_ray *ray, t_hit_record *rec)
{
	double		denom;
	double		t;
	t_vector	p_to_origin;

	denom = vec3_dot(plane->normal, ray->direction);
	if (denom > -EPSILON && denom < EPSILON)
		return (false);
	p_to_origin = vec3_sub(plane->point, ray->origin);
	t = vec3_dot(p_to_origin, plane->normal) / denom;
	if (t < EPSILON)
		return (false);
	rec->t = t;
	rec->point = ray_at(*ray, t);
	rec->normal = plane->normal;
	if (denom > 0)
		rec->normal = vec3_negate(rec->normal);
	return (true);
}
