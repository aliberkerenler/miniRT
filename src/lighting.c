#include "../include/render.h"
#include "../include/vec3.h"

static void	apply_diffuse(t_diffuse_calc *dc, t_color *result);

static t_color	apply_ambient(t_scene *scene, t_color obj_color)
{
	t_color	ambient;
	double	ka;

	ka = 0.1;
	ambient = color_multiply(scene->ambient.color, obj_color);
	ambient = color_mul(ambient, scene->ambient.ratio * ka);
	return (ambient);
}

static int	check_shadow(t_scene *scene, t_vector point,
				t_vector light_dir, double light_dist)
{
	t_ray			shadow_ray;
	t_hit_record	temp_rec;
	t_object		*temp_obj;

	shadow_ray.origin = vec3_add(point, vec3_mul(light_dir, 0.001));
	shadow_ray.direction = light_dir;
	if (find_closest_hit(scene, &shadow_ray, &temp_rec, &temp_obj))
	{
		if (temp_rec.t < light_dist)
			return (1);
	}
	return (0);
}

static void	process_light(t_scene *scene, t_hit_record *rec,
				t_color obj_color, t_color *result)
{
	t_light			*light;
	t_vector		to_light;
	t_diffuse_calc	dc;
	double			light_distance;

	light = scene->lights;
	while (light)
	{
		to_light = vec3_sub(light->position, rec->point);
		light_distance = vec3_length(to_light);
		dc.light_dir = vec3_normalize(to_light);
		if (!check_shadow(scene, rec->point, dc.light_dir, light_distance))
		{
			dc.rec = rec;
			dc.obj_color = obj_color;
			dc.light = light;
			apply_diffuse(&dc, result);
		}
		light = light->next;
	}
}

static void	apply_diffuse(t_diffuse_calc *dc, t_color *result)
{
	double	diff;
	double	kd;
	t_color	diffuse;

	kd = 0.9;
	diff = vec3_dot(dc->rec->normal, dc->light_dir);
	if (diff < 0)
		diff = 0;
	diffuse = color_multiply(dc->light->color, dc->obj_color);
	diffuse = color_mul(diffuse, diff * dc->light->brightness * kd);
	*result = color_add(*result, diffuse);
}

t_color	calculate_color(t_scene *scene, t_hit_record *rec, t_color obj_color)
{
	t_color	ambient;
	t_color	result;
	t_color	final_color;

	ambient = apply_ambient(scene, obj_color);
	result = color(0, 0, 0);
	process_light(scene, rec, obj_color, &result);
	final_color = color_add(ambient, result);
	if (final_color.x > 1.0)
		final_color.x = 1.0;
	if (final_color.y > 1.0)
		final_color.y = 1.0;
	if (final_color.z > 1.0)
		final_color.z = 1.0;
	return (final_color);
}
