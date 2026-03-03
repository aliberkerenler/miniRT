/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerenler <aerenler@student.42istanbul.com.t+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 15:06:34 by aerenler          #+#    #+#             */
/*   Updated: 2026/03/03 16:45:09 by aerenler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/render.h"
#include "../../include/vec3.h"
#include <math.h>

void	init_viewport(t_cam_calc *calc, t_camera *cam)
{
	calc->focal_length = 1.0;
	calc->theta = cam->fov * M_PI / 180.0;
	calc->h = tan(calc->theta / 2.0);
	calc->viewport_height = 2.0 * calc->h;
	calc->viewport_width = calc->viewport_height
		* (WIN_WIDTH / (double)WIN_HEIGHT);
	calc->forward = cam->orientation;
	if (fabs(calc->forward.z) > 0.999)
		calc->world_up = vec3(0, 1, 0);
	else
		calc->world_up = vec3(0, 0, 1);
	calc->right = vec3_normalize(vec3_cross(calc->forward, calc->world_up));
	calc->up = vec3_normalize(vec3_cross(calc->right, calc->forward));
	calc->horizontal = vec3_mul(calc->right, calc->viewport_width);
	calc->vertical = vec3_mul(calc->up, calc->viewport_height);
	calc->upper_left = vec3_add(cam->position,
			vec3_mul(calc->forward, calc->focal_length));
	calc->upper_left = vec3_sub(calc->upper_left,
			vec3_div(calc->horizontal, 2.0));
	calc->upper_left = vec3_add(calc->upper_left,
			vec3_div(calc->vertical, 2.0));
}

t_ray	get_camera_ray(t_camera *cam, t_cam_calc *calc, double u, double v)
{
	t_vector	direction;

	direction = vec3_add(calc->upper_left, vec3_mul(calc->horizontal, u));
	direction = vec3_sub(direction, vec3_mul(calc->vertical, v));
	direction = vec3_sub(direction, cam->position);
	return (ray(cam->position, vec3_normalize(direction)));
}
