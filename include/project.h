#ifndef PROJECT_H
# define PROJECT_H

# include <math.h>
# include <stdbool.h>

/* ========== Vektör ve Renk Yapıları ========== */

typedef struct s_vector
{
	double	x;
	double	y;
	double	z;
}	t_vector;

typedef t_vector	t_point;
typedef t_vector	t_color;

/* ========== Ray (Işın) Yapısı ========== */

typedef struct s_ray
{
	t_point		origin;
	t_vector	direction;
}	t_ray;

/* ========== Hit Record (Çarpışma Kaydı) ========== */

typedef struct s_hit_record
{
	t_point		point;
	t_vector	normal;
	double		t;
	bool		front_face;
}	t_hit_record;

/* ========== Malzeme Yapısı ========== */

typedef struct s_material
{
	t_color		color;
}	t_material;

/* ========== Obje Tipleri ========== */

typedef enum e_object_type
{
	OBJ_SPHERE,
	OBJ_PLANE,
	OBJ_CYLINDER
}	t_object_type;

/* ========== Küre Yapısı ========== */

typedef struct s_sphere
{
	t_point		center;
	double		radius;
	t_material	material;
}	t_sphere;

/* ========== Düzlem Yapısı ========== */

typedef struct s_plane
{
	t_point		point;
	t_vector	normal;
	t_material	material;
}	t_plane;

/* ========== Silindir Yapısı ========== */

typedef struct s_cylinder
{
	t_point		center;
	t_vector	axis;
	double		radius;
	double		height;
	t_material	material;
}	t_cylinder;

/* ========== Genel Obje Yapısı ========== */

typedef struct s_object
{
	t_object_type	type;
	void			*data;
	struct s_object	*next;
}	t_object;

/* ========== Kamera Yapısı ========== */

typedef struct s_camera
{
	t_point		position;
	t_vector	orientation;
	double		fov;
}	t_camera;

/* ========== Ambient Işık ========== */

typedef struct s_ambient
{
	double		ratio;
	t_color		color;
}	t_ambient;

/* ========== Işık Kaynağı ========== */

typedef struct s_light
{
	t_point			position;
	double			brightness;
	t_color			color;
	struct s_light	*next;
}	t_light;

/* ========== Sahne Yapısı ========== */

typedef struct s_scene
{
	t_camera	camera;
	t_ambient	ambient;
	t_light		*lights;
	t_object	*objects;
}	t_scene;

#endif