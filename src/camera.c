#include "../include/render.h"
#include "../include/vec3.h"
#include <math.h>

static void	init_viewport(t_cam_calc *calc, t_camera *cam)
{
	calc->focal_length = 1.0;
	calc->theta = cam->fov * M_PI / 180.0;
	calc->h = tan(calc->theta / 2.0);
	calc->viewport_height = 2.0 * calc->h;
	calc->viewport_width = calc->viewport_height
		* (WIN_WIDTH / (double)WIN_HEIGHT);
	calc->forward = cam->orientation;
	if (fabs(calc->forward.y) > 0.999)
		calc->world_up = vec3(0, 0, 1);
	else
		calc->world_up = vec3(0, 1, 0);
	calc->right = vec3_normalize(vec3_cross(calc->forward, calc->world_up));
	calc->up = vec3_normalize(vec3_cross(calc->right, calc->forward));
	calc->horizontal = vec3_mul(calc->right, calc->viewport_width);
	calc->vertical = vec3_mul(calc->up, -calc->viewport_height);
}

t_ray	get_camera_ray(t_camera *cam, double u, double v)
{
	t_cam_calc	calc;

	init_viewport(&calc, cam);
	calc.upper_left = vec3_add(cam->position,
			vec3_mul(calc.forward, calc.focal_length));
	calc.upper_left = vec3_sub(calc.upper_left,
			vec3_div(calc.horizontal, 2.0));
	calc.upper_left = vec3_sub(calc.upper_left, vec3_div(calc.vertical, 2.0));
	calc.direction = vec3_add(calc.upper_left,
			vec3_mul(calc.horizontal, u));
	calc.direction = vec3_add(calc.direction, vec3_mul(calc.vertical, v));
	calc.direction = vec3_sub(calc.direction, cam->position);
	return (ray(cam->position, vec3_normalize(calc.direction)));
}
