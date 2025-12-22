#include "../include/vec3.h"

t_color	color(double r, double g, double b)
{
	return (vec3(r, g, b));
}

t_color	color_mul(t_color c, double t)
{
	return (vec3_mul(c, t));
}

t_color	color_add(t_color a, t_color b)
{
	return (vec3_add(a, b));
}

t_color	color_multiply(t_color a, t_color b)
{
	return (vec3(a.x * b.x, a.y * b.y, a.z * b.z));
}

static int	clamp(double value, int min, int max)
{
	if (value < min)
		return (min);
	if (value > max)
		return (max);
	return ((int)value);
}

int	color_to_int(t_color c)
{
	int	r;
	int	g;
	int	b;

	r = clamp(c.x * 255.999, 0, 255);
	g = clamp(c.y * 255.999, 0, 255);
	b = clamp(c.z * 255.999, 0, 255);
	return (r << 16 | g << 8 | b);
}

