#include "../include/render.h"
#include "../include/vec3.h"

bool	hit_sphere(t_sphere *sphere, t_ray *ray, t_hit_record *rec)
{
	t_vector	oc;
	double		a;
	double		half_b;
	double		c;
	double		discriminant;
	double		sqrtd;
	double		root;

	oc = vec3_sub(ray->origin, sphere->center);
	a = vec3_length_squared(ray->direction);
	half_b = vec3_dot(oc, ray->direction);
	c = vec3_length_squared(oc) - sphere->radius * sphere->radius;
	discriminant = half_b * half_b - a * c;
	if (discriminant < 0)
		return (false);
	sqrtd = sqrt(discriminant);
	root = (-half_b - sqrtd) / a;
	if (root < 0.001)
		root = (-half_b + sqrtd) / a;
	if (root < 0.001)
		return (false);
	rec->t = root;
	rec->point = ray_at(*ray, rec->t);
	rec->normal = vec3_normalize(vec3_sub(rec->point, sphere->center));
	return (true);
}

