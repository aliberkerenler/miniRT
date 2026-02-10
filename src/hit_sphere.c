#include "../include/render.h"
#include "../include/vec3.h"

bool	hit_sphere(t_sphere *sphere, t_ray *ray, t_hit_record *rec)
{
	t_vector	oc;
	t_quadratic	q;

	oc = vec3_sub(ray->origin, sphere->center);
	q.a = vec3_length_squared(ray->direction);
	q.half_b = vec3_dot(oc, ray->direction);
	q.c = vec3_length_squared(oc) - sphere->radius * sphere->radius;
	q.discriminant = q.half_b * q.half_b - q.a * q.c;
	if (q.discriminant < 0)
		return (false);
	q.sqrtd = sqrt(q.discriminant);
	q.root = (-q.half_b - q.sqrtd) / q.a;
	if (q.root < 0.001)
		q.root = (-q.half_b + q.sqrtd) / q.a;
	if (q.root < 0.001)
		return (false);
	rec->t = q.root;
	rec->point = ray_at(*ray, rec->t);
	rec->normal = vec3_normalize(vec3_sub(rec->point, sphere->center));
	return (true);
}
