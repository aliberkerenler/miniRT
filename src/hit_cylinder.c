#include "../include/render.h"
#include "../include/vec3.h"
#include <math.h>

static bool	check_cap_intersection(t_cylinder *cy, t_ray *ray,
				t_hit_record *rec, t_cap_data *data);

static double	get_valid_root(double *coeffs, double discriminant)
{
	double	sqrtd;
	double	root;

	if (fabs(coeffs[0]) < 0.000001)
		return (-1.0);
	sqrtd = sqrt(discriminant);
	root = (-coeffs[1] - sqrtd) / (2.0 * coeffs[0]);
	if (root < 0.001)
		root = (-coeffs[1] + sqrtd) / (2.0 * coeffs[0]);
	return (root);
}

static bool	check_cap_intersection(t_cylinder *cy, t_ray *ray,
			t_hit_record *rec, t_cap_data *data)
{
	t_vector	hit_point;
	t_vector	to_hit;
	double		dist_sq;

	if (data->t < 0.001)
		return (false);
	hit_point = ray_at(*ray, data->t);
	to_hit = vec3_sub(hit_point, data->cap_center);
	dist_sq = vec3_length_squared(to_hit);
	if (dist_sq > cy->radius * cy->radius)
		return (false);
	if (data->t < rec->t)
	{
		rec->t = data->t;
		rec->point = hit_point;
		rec->normal = data->cap_normal;
		if (data->denom > 0)
			rec->normal = vec3_negate(rec->normal);
		return (true);
	}
	return (false);
}

static bool	hit_cylinder_cap(t_cylinder *cy, t_ray *ray,
			t_hit_record *rec, bool is_top)
{
	t_cap_data	data;
	t_vector	oc;

	if (is_top)
		data.cap_center = vec3_add(cy->center,
				vec3_mul(cy->axis, cy->height / 2.0));
	else
		data.cap_center = vec3_sub(cy->center,
				vec3_mul(cy->axis, cy->height / 2.0));
	if (is_top)
		data.cap_normal = cy->axis;
	else
		data.cap_normal = vec3_mul(cy->axis, -1.0);
	data.denom = vec3_dot(ray->direction, data.cap_normal);
	if (fabs(data.denom) < 0.0001)
		return (false);
	oc = vec3_sub(data.cap_center, ray->origin);
	data.t = vec3_dot(oc, data.cap_normal) / data.denom;
	if (!check_cap_intersection(cy, ray, rec, &data))
		return (false);
	return (true);
}

static bool	check_body_hit(t_cylinder *cy, t_ray *ray,
			t_hit_record *rec, t_vector oc)
{
	double	coeffs[3];
	double	discriminant;
	double	root;
	double	projection;

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

bool	hit_cylinder(t_cylinder *cy, t_ray *ray, t_hit_record *rec)
{
	t_vector	oc;
	bool		hit_any;

	if (cy->radius <= 0.0)
		return (false);
	rec->t = INFINITY;
	hit_any = false;
	oc = vec3_sub(ray->origin, cy->center);
	if (check_body_hit(cy, ray, rec, oc))
		hit_any = true;
	if (hit_cylinder_cap(cy, ray, rec, true))
		hit_any = true;
	if (hit_cylinder_cap(cy, ray, rec, false))
		hit_any = true;
	return (hit_any);
}
