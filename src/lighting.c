#include "../include/render.h"
#include "../include/vec3.h"

static t_color	apply_ambient(t_scene *scene, t_material *material)
{
	t_color	ambient;

	ambient = color_multiply(scene->ambient.color, material->albedo);
	ambient = color_mul(ambient, scene->ambient.ratio * material->ambient);
	return (ambient);
}
static int is_in_shadow(t_scene *scene, t_vector point, t_vector light_dir, double light_distance)
{
    t_ray shadow_ray;
    t_hit_record temp_rec;
    t_object *temp_obj;
    
    // Shadow ray oluştur (vuruş noktasından ışığa doğru)
    shadow_ray.origin = vec3_add(point, vec3_mul(light_dir, 0.001));  // Epsilon offset (shadow acne önler)
    shadow_ray.direction = light_dir;
    
    // Işığa giderken engel var mı?
    if (find_closest_hit(scene, &shadow_ray, &temp_rec, &temp_obj))
    {
        // Engel ışıktan daha yakınsa → gölge!
        if (temp_rec.t < light_distance)
            return (1);  // Gölgede!
    }
    return (0);  // Gölge yok
}
static t_color apply_diffuse(t_scene *scene, t_hit_record *rec, t_material *material)
{
    t_light     *light;
    t_vector    light_dir;
    double      light_distance;
    double      diff;
    t_color     diffuse;
    t_color     result;

    result = color(0, 0, 0);
    light = scene->lights;
    while (light)
    {
        // Işığa olan vektör
        t_vector to_light = vec3_sub(light->position, rec->point);
        light_distance = vec3_length(to_light);
        light_dir = vec3_normalize(to_light);
        
        // ✨ YENİ: Shadow kontrolü!
        if (is_in_shadow(scene, rec->point, light_dir, light_distance))
        {
            light = light->next;
            continue;  // Bu ışık engelleniyor, bir sonrakine geç!
        }
        
        // Lambert's law (eskisi gibi)
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

