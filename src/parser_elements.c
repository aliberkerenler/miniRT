#include "../include/parser.h"
#include "../include/minirt.h"
#include "../include/vec3.h"

static void	parse_ambient(t_scene *scene, char **tokens)
{
	int	i;

	i = 1;
	if (!tokens[1] || !tokens[2])
		exit_error("Invalid ambient format", ERR_PARSE_FORMAT);
	scene->ambient.ratio = parse_double(tokens[i++]);
	scene->ambient.color = parse_color(tokens, &i);
}

static void	parse_light(t_scene *scene, char **tokens)
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

static void	parse_camera(t_scene *scene, char **tokens)
{
	int	i;

	i = 1;
	if (!tokens[1] || !tokens[2] || !tokens[3])
		exit_error("Invalid camera format", ERR_PARSE_CAMERA);
	scene->camera.position = parse_vector(tokens, &i);
	scene->camera.orientation = vec3_normalize(parse_vector(tokens, &i));
	scene->camera.fov = parse_double(tokens[i]);
}

static void	parse_sphere(t_scene *scene, char **tokens)
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
	sphere->material.albedo = parse_color(tokens, &i);
	sphere->material.ambient = 0.1;
	sphere->material.diffuse = 0.9;
	sphere->material.specular = 0.9;
	sphere->material.shininess = 200.0;
	obj = malloc(sizeof(t_object));
	if (!obj)
		exit_error("Memory allocation failed", ERR_MALLOC);
	obj->type = OBJ_SPHERE;
	obj->data = sphere;
	obj->next = scene->objects;
	scene->objects = obj;
}

static void	parse_plane(t_scene *scene, char **tokens)
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
	plane->material.albedo = parse_color(tokens, &i);
	plane->material.ambient = 0.1;
	plane->material.diffuse = 0.9;
	plane->material.specular = 0.9;
	plane->material.shininess = 200.0;
	obj = malloc(sizeof(t_object));
	if (!obj)
		exit_error("Memory allocation failed", ERR_MALLOC);
	obj->type = OBJ_PLANE;
	obj->data = plane;
	obj->next = scene->objects;
	scene->objects = obj;
}

static void	free_tokens(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		free(tokens[i]);
		i++;
	}
	free(tokens);
}

void	parse_content(t_scene *scene, char *content)
{
	char	**lines;
	char	**tokens;
	int		i;

	lines = ft_split(content, '\n');
	if (!lines)
		exit_error("Failed to parse file", ERR_PARSE_FILE);
	i = 0;
	while (lines[i])
	{
		if (lines[i][0] && lines[i][0] != '#')
		{
			tokens = ft_split(lines[i], ' ');
			if (tokens && tokens[0])
			{
				if (ft_strncmp(tokens[0], "A", 2) == 0)
					parse_ambient(scene, tokens);
				else if (ft_strncmp(tokens[0], "C", 2) == 0)
					parse_camera(scene, tokens);
				else if (ft_strncmp(tokens[0], "L", 2) == 0)
					parse_light(scene, tokens);
				else if (ft_strncmp(tokens[0], "sp", 3) == 0)
					parse_sphere(scene, tokens);
				else if (ft_strncmp(tokens[0], "pl", 3) == 0)
					parse_plane(scene, tokens);
				free_tokens(tokens);
			}
		}
		free(lines[i]);
		i++;
	}
	free(lines);
}

