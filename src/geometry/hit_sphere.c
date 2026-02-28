/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_sphere.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerenler <aerenler@student.42istanbul.com.t+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 15:07:11 by aerenler          #+#    #+#             */
/*   Updated: 2026/02/22 15:07:12 by aerenler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/render.h"
#include "../../include/vec3.h"

bool	hit_sphere(t_sphere *sphere, t_ray *ray, t_hit_record *rec)
{
	t_vector	oc;
	t_quadratic	q;

	oc = vec3_sub(ray->origin, sphere->center);
	q.a = vec3_length_squared(ray->direction);
	q.b = 2.0 * vec3_dot(oc, ray->direction);
	q.c = vec3_length_squared(oc) - sphere->radius * sphere->radius;
	q.discriminant = q.b * q.b - 4.0 * q.a * q.c;
	if (q.discriminant < 0)
		return (false);
	q.sqrtd = sqrt(q.discriminant);
	q.root = (-q.b - q.sqrtd) / (2.0 * q.a);
	if (q.root < EPSILON)
		q.root = (-q.b + q.sqrtd) / (2.0 * q.a);
	if (q.root < EPSILON)
		return (false);
	rec->t = q.root;
	rec->point = ray_at(*ray, rec->t);
	rec->normal = vec3_normalize(vec3_sub(rec->point, sphere->center));
	if (vec3_dot(ray->direction, rec->normal) > 0)
		rec->normal = vec3_negate(rec->normal);
	return (true);
}
