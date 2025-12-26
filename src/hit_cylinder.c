#include "../include/render.h"
#include "../include/vec3.h"
#include <math.h>

static bool	check_cylinder_height(t_cylinder *cy, t_vector hit_point,
			double *proj)
{
	t_vector	to_hit;
	double		projection;
	double		half_height;

	to_hit = vec3_sub(hit_point, cy->center);
	projection = vec3_dot(to_hit, cy->axis);
	half_height = cy->height / 2.0;
	*proj = projection;
	if (projection < -half_height || projection > half_height)
		return (false);
	return (true);
}

static t_vector	calculate_cylinder_normal(t_cylinder *cy, t_vector hit_point,
				double projection)
{
	t_vector	center_to_hit;
	t_vector	proj_on_axis;

	center_to_hit = vec3_sub(hit_point, cy->center);
	proj_on_axis = vec3_mul(cy->axis, projection);
	return (vec3_normalize(vec3_sub(center_to_hit, proj_on_axis)));
}

static void	calculate_coefficients(t_cylinder *cy, t_ray *ray,
			t_vector oc, double *coeffs)
{
	double	dir_dot_axis;
	double	oc_dot_axis;

	dir_dot_axis = vec3_dot(ray->direction, cy->axis);
	oc_dot_axis = vec3_dot(oc, cy->axis);
	coeffs[0] = vec3_length_squared(ray->direction)
		- dir_dot_axis * dir_dot_axis;
	coeffs[1] = 2.0 * (vec3_dot(ray->direction, oc)
			- dir_dot_axis * oc_dot_axis);
	coeffs[2] = vec3_length_squared(oc) - oc_dot_axis * oc_dot_axis
		- cy->radius * cy->radius;
}

static double	get_valid_root(double *coeffs, double discriminant)
{
	double	sqrtd;
	double	root;

	sqrtd = sqrt(discriminant);
	root = (-coeffs[1] - sqrtd) / (2.0 * coeffs[0]);
	if (root < 0.001)
		root = (-coeffs[1] + sqrtd) / (2.0 * coeffs[0]);
	return (root);
}

bool	hit_cylinder(t_cylinder *cy, t_ray *ray, t_hit_record *rec)
{
	t_vector	oc;
	double		coeffs[3];
	double		discriminant;
	double		root;
	double		projection;

	oc = vec3_sub(ray->origin, cy->center);
	calculate_coefficients(cy, ray, oc, coeffs);
	discriminant = coeffs[1] * coeffs[1] - 4.0 * coeffs[0] * coeffs[2];
	if (discriminant < 0)
		return (false);
	root = get_valid_root(coeffs, discriminant);
	if (root < 0.001)
		return (false);
	rec->point = ray_at(*ray, root);
	if (!check_cylinder_height(cy, rec->point, &projection))
		return (false);
	rec->t = root;
	rec->normal = calculate_cylinder_normal(cy, rec->point, projection);
	return (true);
}