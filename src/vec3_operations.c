#include "../include/vec3.h"

t_vector	vec3_add(t_vector a, t_vector b)
{
	return (vec3(a.x + b.x, a.y + b.y, a.z + b.z));
}

t_vector	vec3_sub(t_vector a, t_vector b)
{
	return (vec3(a.x - b.x, a.y - b.y, a.z - b.z));
}

t_vector	vec3_mul(t_vector v, double t)
{
	return (vec3(v.x * t, v.y * t, v.z * t));
}

t_vector	vec3_div(t_vector v, double t)
{
	if (t == 0.0)
		return (vec3_zero());
	return (vec3(v.x / t, v.y / t, v.z / t));
}

t_vector	vec3_negate(t_vector v)
{
	return (vec3(-v.x, -v.y, -v.z));
}
