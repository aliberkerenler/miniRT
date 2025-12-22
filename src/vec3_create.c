#include "../include/vec3.h"

t_vector	vec3(double x, double y, double z)
{
	t_vector	v;

	v.x = x;
	v.y = y;
	v.z = z;
	return (v);
}

t_vector	vec3_zero(void)
{
	return (vec3(0.0, 0.0, 0.0));
}

t_vector	vec3_one(void)
{
	return (vec3(1.0, 1.0, 1.0));
}

