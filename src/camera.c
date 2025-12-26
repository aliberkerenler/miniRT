#include "../include/render.h"
#include "../include/vec3.h"
#include <math.h>

t_ray	get_camera_ray(t_camera *cam, double u, double v)
{
	double		viewport_height;
	double		viewport_width;
	double		focal_length;
	double		theta;
	double		h;
	t_vector	horizontal;
	t_vector	vertical;
	t_vector	upper_left;
	t_vector	direction;

	focal_length = 1.0;
	theta = cam->fov * M_PI / 180.0;
	h = tan(theta / 2.0);
	viewport_height = 2.0 * h;
	viewport_width = viewport_height * (WIN_WIDTH / (double)WIN_HEIGHT);
	horizontal = vec3(viewport_width, 0, 0);
	vertical = vec3(0, -viewport_height, 0);
	upper_left = cam->position;
	upper_left = vec3_sub(upper_left, vec3_div(horizontal, 2));
	upper_left = vec3_sub(upper_left, vec3_div(vertical, 2));
	upper_left = vec3_sub(upper_left, vec3(0, 0, focal_length));
	direction = vec3_add(upper_left, vec3_mul(horizontal, u));
	direction = vec3_add(direction, vec3_mul(vertical, v));
	direction = vec3_sub(direction, cam->position);
	return (ray(cam->position, vec3_normalize(direction)));
}

