#include "../include/parser.h"
#include "../include/minirt.h"
#include "../include/vec3.h"
#include <unistd.h>

static char	*read_file(const char *filename)
{
	int		fd;
	char	*line;
	char	*content;
	char	*temp;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		exit_error("Cannot open .rt file", ERR_PARSE_FILE);
	content = ft_strdup("");
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		temp = content;
		content = ft_strjoin(content, line);
		free(temp);
		free(line);
	}
	close(fd);
	return (content);
}

static void	init_scene(t_scene *scene)
{
	scene->camera.position = vec3_zero();
	scene->camera.orientation = vec3(0, 0, -1);
	scene->camera.fov = 90.0;
	scene->ambient.ratio = 0.0;
	scene->ambient.color = color(1, 1, 1);
	scene->lights = NULL;
	scene->objects = NULL;
}

t_scene	*parse_scene(const char *filename)
{
	t_scene	*scene;
	char	*content;

	scene = malloc(sizeof(t_scene));
	if (!scene)
		exit_error("Memory allocation failed", ERR_MALLOC);
	init_scene(scene);
	content = read_file(filename);
	parse_content(scene, content);
	free(content);
	return (scene);
}

void	free_scene(t_scene *scene)
{
	t_object	*obj;
	t_object	*next;
	t_light		*light;
	t_light		*next_light;

	if (!scene)
		return ;
	obj = scene->objects;
	while (obj)
	{
		next = obj->next;
		free(obj->data);
		free(obj);
		obj = next;
	}
	light = scene->lights;
	while (light)
	{
		next_light = light->next;
		free(light);
		light = next_light;
	}
	free(scene);
}

