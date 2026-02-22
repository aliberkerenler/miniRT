#include "../include/vec3.h"

double	vec3_length_squared(t_vector v)
{
	return (v.x * v.x + v.y * v.y + v.z * v.z); // dot ile çözülebilir
}

double	vec3_length(t_vector v)
{
	return (sqrt(vec3_length_squared(v)));
}

double	vec3_dot(t_vector a, t_vector b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_vector	vec3_cross(t_vector a, t_vector b)
{
	t_vector	result;

	result.x = a.y * b.z - a.z * b.y;
	result.y = a.z * b.x - a.x * b.z;
	result.z = a.x * b.y - a.y * b.x;
	return (result);
}

t_vector	vec3_normalize(t_vector v)
{
	double	len;

	len = vec3_length(v);
	if (len == 0.0)
		return (vec3_zero());
	return (vec3_div(v, len));
}
