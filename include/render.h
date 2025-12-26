#ifndef RENDER_H
# define RENDER_H

# include "project.h"
# include "minirt.h"

/* Image yapısı */
typedef struct s_image
{
	void	*img_ptr;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}	t_image;

/* Render fonksiyonları */
void		render_scene(t_mlx *mlx, t_image *img, t_scene *scene);
void		put_pixel_to_image(t_image *img, int x, int y, int color);

/* Ray fonksiyonları */
t_ray		get_camera_ray(t_camera *cam, double u, double v);

/* Hit fonksiyonları */
bool		hit_sphere(t_sphere *sphere, t_ray *ray, t_hit_record *rec);
bool		hit_plane(t_plane *plane, t_ray *ray, t_hit_record *rec);
bool		hit_cylinder(t_cylinder *cylinder, t_ray *ray, t_hit_record *rec);
bool		find_closest_hit(t_scene *scene, t_ray *ray, t_hit_record *rec,
				t_object **hit_obj);

/* Lighting fonksiyonları */
t_color		calculate_color(t_scene *scene, t_hit_record *rec,
				t_material *material);

#endif

