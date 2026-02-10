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

int	color_to_int(t_color c)
{
	int	r;
	int	g;
	int	b;

	r = (int)(c.x * 255.999);
	if (r < 0)
		r = 0;
	if (r > 255)
		r = 255;
	g = (int)(c.y * 255.999);
	if (g < 0)
		g = 0;
	if (g > 255)
		g = 255;
	b = (int)(c.z * 255.999);
	if (b < 0)
		b = 0;
	if (b > 255)
		b = 255;
	return (r << 16 | g << 8 | b);
}
