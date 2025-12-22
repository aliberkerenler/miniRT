#include "../include/render.h"
#include "../include/vec3.h"

static t_color	apply_ambient(t_scene *scene, t_material *material)
{
	t_color	ambient;

	ambient = color_multiply(scene->ambient.color, material->albedo);
	ambient = color_mul(ambient, scene->ambient.ratio * material->ambient);
	return (ambient);
}

static t_color	apply_diffuse(t_scene *scene, t_hit_record *rec,
				t_material *material)
{
	t_light		*light;
	t_vector	light_dir;
	double		diff;
	t_color		diffuse;
	t_color		result;

	result = color(0, 0, 0);
	light = scene->lights;
	while (light)
	{
		light_dir = vec3_normalize(vec3_sub(light->position, rec->point));
		diff = vec3_dot(rec->normal, light_dir);
		if (diff < 0)
			diff = 0;
		diffuse = color_multiply(light->color, material->albedo);
		diffuse = color_mul(diffuse, diff * light->brightness * material->diffuse);
		result = color_add(result, diffuse);
		light = light->next;
	}
	return (result);
}

t_color	calculate_color(t_scene *scene, t_hit_record *rec, t_material *material)
{
	t_color	ambient;
	t_color	diffuse;
	t_color	final_color;

	ambient = apply_ambient(scene, material);
	diffuse = apply_diffuse(scene, rec, material);
	final_color = color_add(ambient, diffuse);
	if (final_color.x > 1.0)
		final_color.x = 1.0;
	if (final_color.y > 1.0)
		final_color.y = 1.0;
	if (final_color.z > 1.0)
		final_color.z = 1.0;
	return (final_color);
}

