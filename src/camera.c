#include "../include/render.h"
#include "../include/vec3.h"

t_ray	get_camera_ray(t_camera *cam, double u, double v)
{
	double		viewport_height;
	double		viewport_width;
	double		focal_length;
	t_vector	horizontal;
	t_vector	vertical;
	t_vector	lower_left;
	t_vector	direction;

	viewport_height = 2.0;
	viewport_width = viewport_height * (WIN_WIDTH / (double)WIN_HEIGHT);
	focal_length = 1.0;
	horizontal = vec3(viewport_width, 0, 0);
	vertical = vec3(0, -viewport_height, 0);
	lower_left = cam->position;
	lower_left = vec3_sub(lower_left, vec3_div(horizontal, 2));
	lower_left = vec3_sub(lower_left, vec3_div(vertical, 2));
	lower_left = vec3_sub(lower_left, vec3(0, 0, focal_length));
	direction = vec3_add(lower_left, vec3_mul(horizontal, u));
	direction = vec3_add(direction, vec3_mul(vertical, v));
	direction = vec3_sub(direction, cam->position);
	return (ray(cam->position, vec3_normalize(direction)));
}

