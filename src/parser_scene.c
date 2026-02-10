#include "../include/parser.h"
#include "../include/minirt.h"
#include "../include/vec3.h"

void	parse_ambient(t_scene *scene, char **tokens)
{
	int	i;

	i = 1;
	if (!tokens[1] || !tokens[2])
		exit_error("Invalid ambient format", ERR_PARSE_FORMAT);
	scene->ambient.ratio = parse_double(tokens[i++]);
	scene->ambient.color = parse_color(tokens, &i);
}

void	parse_light(t_scene *scene, char **tokens)
{
	t_light	*light;
	int		i;

	i = 1;
	if (!tokens[1] || !tokens[2] || !tokens[3])
		exit_error("Invalid light format", ERR_PARSE_FORMAT);
	light = malloc(sizeof(t_light));
	if (!light)
		exit_error("Memory allocation failed", ERR_MALLOC);
	light->position = parse_vector(tokens, &i);
	light->brightness = parse_double(tokens[i++]);
	light->color = parse_color(tokens, &i);
	light->next = scene->lights;
	scene->lights = light;
}

void	parse_camera(t_scene *scene, char **tokens)
{
	int	i;

	i = 1;
	if (!tokens[1] || !tokens[2] || !tokens[3])
		exit_error("Invalid camera format", ERR_PARSE_CAMERA);
	scene->camera.position = parse_vector(tokens, &i);
	scene->camera.orientation = vec3_normalize(parse_vector(tokens, &i));
	scene->camera.fov = parse_double(tokens[i]);
}
