#include "../include/vec3.h"

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
