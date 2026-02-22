#include "../include/render.h"
#include "../include/vec3.h"

void	put_pixel_to_image(t_image *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= img->width || y < 0 || y >= img->height)
		return ;
	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

static t_color	get_object_color(t_object *obj)
{
	if (obj->type == OBJ_SPHERE)
		return (((t_sphere *)obj->data)->color);
	else if (obj->type == OBJ_PLANE)
		return (((t_plane *)obj->data)->color);
	else if (obj->type == OBJ_CYLINDER)
		return (((t_cylinder *)obj->data)->color);
	return (color(1, 0, 1));
}

static t_color	ray_color(t_ray *ray, t_scene *scene)
{
	t_hit_record	rec;
	t_object		*hit_obj;
	t_color			obj_color;

	if (find_closest_hit(scene, ray, &rec, &hit_obj))
	{
		obj_color = get_object_color(hit_obj);
		return (calculate_color(scene, &rec, obj_color));
	}
	return (color(0.1, 0.1, 0.1));
}

static void	render_pixel(t_scene *scene, t_image *img, t_cam_calc *calc,
			int *coords)
{
	double	u;
	double	v;
	t_ray	ray;
	t_color	pixel_color;

	u = (double)coords[0] / (img->width - 1);
	v = (double)coords[1] / (img->height - 1);
	ray = get_camera_ray(&scene->camera, calc, u, v);
	pixel_color = ray_color(&ray, scene);
	put_pixel_to_image(img, coords[0], coords[1], color_to_int(pixel_color));
}

void	render_scene(t_image *img, t_scene *scene)
{
	int			coords[2];
	t_cam_calc	calc;

	init_viewport(&calc, &scene->camera);
	coords[1] = 0;
	while (coords[1] < img->height)
	{
		coords[0] = 0;
		while (coords[0] < img->width)
		{
			render_pixel(scene, img, &calc, coords);
			coords[0]++;
		}
		coords[1]++;
	}
}
