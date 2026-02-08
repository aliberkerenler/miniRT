#include "../include/render.h"

t_material	create_material(t_color color)
{
	t_material	mat;

	mat.color = color;
	return (mat);
}
