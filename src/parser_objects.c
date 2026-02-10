#include "../include/parser.h"
#include "../include/minirt.h"
#include "../include/vec3.h"
#include "../include/render.h"

void	parse_sphere(t_scene *scene, char **tokens)
{
	t_sphere	*sphere;
	t_object	*obj;
	int			i;

	i = 1;
	if (!tokens[1] || !tokens[2] || !tokens[3])
		exit_error("Invalid sphere format", ERR_PARSE_SPHERE);
	sphere = malloc(sizeof(t_sphere));
	if (!sphere)
		exit_error("Memory allocation failed", ERR_MALLOC);
	sphere->center = parse_vector(tokens, &i);
	sphere->radius = parse_double(tokens[i++]) / 2.0;
	sphere->color = parse_color(tokens, &i);
	obj = malloc(sizeof(t_object));
	if (!obj)
		exit_error("Memory allocation failed", ERR_MALLOC);
	obj->type = OBJ_SPHERE;
	obj->data = sphere;
	obj->next = scene->objects;
	scene->objects = obj;
}

void	parse_plane(t_scene *scene, char **tokens)
{
	t_plane		*plane;
	t_object	*obj;
	int			i;

	i = 1;
	if (!tokens[1] || !tokens[2] || !tokens[3])
		exit_error("Invalid plane format", ERR_PARSE_FORMAT);
	plane = malloc(sizeof(t_plane));
	if (!plane)
		exit_error("Memory allocation failed", ERR_MALLOC);
	plane->point = parse_vector(tokens, &i);
	plane->normal = vec3_normalize(parse_vector(tokens, &i));
	plane->color = parse_color(tokens, &i);
	obj = malloc(sizeof(t_object));
	if (!obj)
		exit_error("Memory allocation failed", ERR_MALLOC);
	obj->type = OBJ_PLANE;
	obj->data = plane;
	obj->next = scene->objects;
	scene->objects = obj;
}

void	parse_cylinder(t_scene *scene, char **tokens)
{
	t_cylinder	*cylinder;
	t_object	*obj;
	int			i;

	i = 1;
	if (!tokens[1] || !tokens[2] || !tokens[3] || !tokens[4] || !tokens[5])
		exit_error("Invalid cylinder format", ERR_PARSE_FORMAT);
	cylinder = malloc(sizeof(t_cylinder));
	if (!cylinder)
		exit_error("Memory allocation failed", ERR_MALLOC);
	cylinder->center = parse_vector(tokens, &i);
	cylinder->axis = vec3_normalize(parse_vector(tokens, &i));
	cylinder->radius = parse_double(tokens[i++]) / 2.0;
	cylinder->height = parse_double(tokens[i++]);
	cylinder->color = parse_color(tokens, &i);
	obj = malloc(sizeof(t_object));
	if (!obj)
		exit_error("Memory allocation failed", ERR_MALLOC);
	obj->type = OBJ_CYLINDER;
	obj->data = cylinder;
	obj->next = scene->objects;
	scene->objects = obj;
}
