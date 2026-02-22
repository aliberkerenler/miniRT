#ifndef PROJECT_H
# define PROJECT_H

# include <math.h>
# include <stdbool.h>

typedef struct s_vector
{
	double	x;
	double	y;
	double	z;
}	t_vector;

typedef t_vector	t_point;
typedef t_vector	t_color;

typedef struct s_ray
{
	t_point		origin;
	t_vector	direction;
}	t_ray;

typedef struct s_hit_record
{
	t_point		point;
	t_vector	normal;
	double		t;
}	t_hit_record;

typedef enum e_object_type
{
	OBJ_SPHERE,
	OBJ_PLANE,
	OBJ_CYLINDER
}	t_object_type;

typedef struct s_sphere
{
	t_point		center;
	double		radius;
	t_color		color;
}	t_sphere;

typedef struct s_plane
{
	t_point		point;
	t_vector	normal;
	t_color		color;
}	t_plane;

typedef struct s_cylinder
{
	t_point		center;
	t_vector	axis;
	double		radius;
	double		height;
	t_color		color;
}	t_cylinder;

typedef struct s_object
{
	t_object_type	type;
	void			*data;
	struct s_object	*next;
}	t_object;

typedef struct s_camera
{
	t_point		position;
	t_vector	orientation;
	double		fov;
}	t_camera;

typedef struct s_ambient
{
	double		ratio;
	t_color		color;
}	t_ambient;

typedef struct s_light
{
	t_point			position;
	double			brightness;
}	t_light;

typedef struct s_scene
{
	t_camera	camera;
	t_ambient	ambient;
	t_light		light;
	t_object	*objects;
	int			has_ambient;
	int			has_camera;
	int			has_light;
	int			error;
	const char	*err_msg;
}	t_scene;

#endif