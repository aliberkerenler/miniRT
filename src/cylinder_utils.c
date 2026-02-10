#include "../include/render.h"
#include "../include/vec3.h"
#include <math.h>

bool	check_cylinder_height(t_cylinder *cy, t_vector hit_point, double *proj)
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

t_vector	calculate_cylinder_normal(t_cylinder *cy, t_vector hit_point,
				double projection)
{
	t_vector	center_to_hit;
	t_vector	proj_on_axis;

	center_to_hit = vec3_sub(hit_point, cy->center);
	proj_on_axis = vec3_mul(cy->axis, projection);
	return (vec3_normalize(vec3_sub(center_to_hit, proj_on_axis)));
}

void	calculate_coefficients(t_cylinder *cy, t_ray *ray,
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
