#include "../include/parser.h"
#include "../include/minirt.h"
#include "../include/vec3.h"
#include "../include/render.h"

void	add_object(t_scene *scene, t_object *obj)
{
	obj->next = scene->objects;
	scene->objects = obj;
}

static t_sphere	*new_sphere(char **tokens, int *i, t_scene *scene)
{
	t_sphere	*sphere;
	double		diameter;

	sphere = malloc(sizeof(t_sphere));
	if (!sphere)
		exit_error("Memory allocation failed", ERR_MALLOC);
	sphere->center = parse_vector(tokens, i);
	diameter = ft_atof(tokens[(*i)++]);
	if (diameter <= 0)
	{
		free(sphere);
		scene->error = 1;
		scene->err_msg = "Sphere diameter must be positive";
		return (NULL);
	}
	sphere->radius = diameter / 2.0;
	sphere->color = parse_color(tokens, i);
	return (sphere);
}

static t_cylinder	*new_cylinder(char **tokens, int *i, t_scene *scene)
{
	t_cylinder	*cy;
	double		diameter;

	cy = malloc(sizeof(t_cylinder));
	if (!cy)
		exit_error("Memory allocation failed", ERR_MALLOC);
	cy->center = parse_vector(tokens, i);
	cy->axis = vec3_normalize(parse_vector(tokens, i));
	diameter = ft_atof(tokens[(*i)++]);
	cy->height = ft_atof(tokens[(*i)++]);
	if (diameter <= 0 || cy->height <= 0)
	{
		free(cy);
		scene->error = 1;
		scene->err_msg = "Cylinder diameter and height must be positive";
		return (NULL);
	}
	cy->radius = diameter / 2.0;
	cy->color = parse_color(tokens, i);
	return (cy);
}

void	parse_sphere(t_scene *scene, char **tokens)
{
	t_sphere	*sphere;
	t_object	*obj;
	int			i;

	i = 1;
	if (!tokens[1] || !tokens[2] || !tokens[3])
	{
		scene->error = 1;
		scene->err_msg = "Invalid sphere format";
		return ;
	}
	sphere = new_sphere(tokens, &i, scene);
	if (!sphere)
		return ;
	obj = malloc(sizeof(t_object));
	if (!obj)
		exit_error("Memory allocation failed", ERR_MALLOC);
	obj->type = OBJ_SPHERE;
	obj->data = sphere;
	add_object(scene, obj);
}

void	parse_cylinder(t_scene *scene, char **tokens)
{
	t_cylinder	*cylinder;
	t_object	*obj;
	int			i;

	i = 1;
	if (!tokens[1] || !tokens[2] || !tokens[3] || !tokens[4] || !tokens[5])
	{
		scene->error = 1;
		scene->err_msg = "Invalid cylinder format";
		return ;
	}
	cylinder = new_cylinder(tokens, &i, scene);
	if (!cylinder)
		return ;
	obj = malloc(sizeof(t_object));
	if (!obj)
		exit_error("Memory allocation failed", ERR_MALLOC);
	obj->type = OBJ_CYLINDER;
	obj->data = cylinder;
	add_object(scene, obj);
}
