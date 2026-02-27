/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerenler <aerenler@student.42istanbul.com.t+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 15:06:25 by aerenler          #+#    #+#             */
/*   Updated: 2026/02/22 15:06:26 by aerenler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "project.h"
# include "minirt.h"

typedef struct s_cam_calc
{
	double		focal_length;
	double		viewport_height;
	double		viewport_width;
	double		theta;
	double		h;
	t_vector	forward;
	t_vector	right;
	t_vector	up;
	t_vector	horizontal;
	t_vector	vertical;
	t_vector	world_up;
}	t_cam_calc;

typedef struct s_diffuse_calc
{
	t_hit_record	*rec;
	t_color			obj_color;
	t_light			*light;
	t_vector		light_dir;
}	t_diffuse_calc;

typedef struct s_cap_data
{
	double		t;
	double		denom;
	t_vector	cap_center;
	t_vector	cap_normal;
}	t_cap_data;

typedef struct s_quadratic
{
	double	a;
	double	b;
	double	c;
	double	discriminant;
	double	sqrtd;
	double	root;
}	t_quadratic;

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

typedef struct s_data
{
	t_mlx		mlx;
	t_image		img;
	t_scene		*scene;
}	t_data;

void		render_scene(t_image *img, t_scene *scene);
void		put_pixel_to_image(t_image *img, int x, int y, int color);

void		init_viewport(t_cam_calc *calc, t_camera *cam);
t_ray		get_camera_ray(t_camera *cam, t_cam_calc *calc, double u, double v);

bool		hit_sphere(t_sphere *sphere, t_ray *ray, t_hit_record *rec);
bool		hit_plane(t_plane *plane, t_ray *ray, t_hit_record *rec);
bool		hit_cylinder(t_cylinder *cylinder, t_ray *ray, t_hit_record *rec);
bool		find_closest_hit(t_scene *scene, t_ray *ray, t_hit_record *rec,
				t_object **hit_obj);

bool		check_cylinder_height(t_cylinder *cy, t_vector hit_point,
				double *proj);
t_vector	calculate_cylinder_normal(t_cylinder *cy, t_vector hit_point,
				double projection);
void		calculate_coefficients(t_cylinder *cy, t_ray *ray,
				t_vector oc, double *coeffs);

t_color		calculate_color(t_scene *scene, t_hit_record *rec,
				t_color obj_color);

#endif
