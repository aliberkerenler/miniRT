/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerenler <aerenler@student.42istanbul.com.t+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 15:06:28 by aerenler          #+#    #+#             */
/*   Updated: 2026/02/22 15:06:29 by aerenler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC3_H
# define VEC3_H

# include "project.h"

t_vector	vec3(double x, double y, double z);
t_vector	vec3_zero(void);

t_vector	vec3_add(t_vector a, t_vector b);
t_vector	vec3_sub(t_vector a, t_vector b);
t_vector	vec3_mul(t_vector v, double t);
t_vector	vec3_div(t_vector v, double t);
t_vector	vec3_negate(t_vector v);

double		vec3_length(t_vector v);
double		vec3_length_squared(t_vector v);
double		vec3_dot(t_vector a, t_vector b);
t_vector	vec3_cross(t_vector a, t_vector b);
t_vector	vec3_normalize(t_vector v);

t_color		color(double r, double g, double b);
t_color		color_mul(t_color c, double t);
t_color		color_add(t_color a, t_color b);
t_color		color_multiply(t_color a, t_color b);
int			color_to_int(t_color c);

t_ray		ray(t_point origin, t_vector direction);
t_point		ray_at(t_ray r, double t);

#endif
