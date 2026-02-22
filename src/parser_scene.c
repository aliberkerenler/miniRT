#include "../include/parser.h"
#include "../include/minirt.h"
#include "../include/vec3.h"

static int	create_light(t_scene *scene, char **tokens, int *i)
{
	scene->light.position = parse_vector(tokens, i);
	scene->light.brightness = ft_atof(tokens[(*i)++]);
	if (scene->light.brightness < 0.0 || scene->light.brightness > 1.0)
	{
		scene->error = 1;
		scene->err_msg = "Light brightness must be in range [0.0,1.0]";
		return (0);
	}
	scene->light.color = parse_color(tokens, i);
	return (1);
}

void	parse_ambient(t_scene *scene, char **tokens)
{
	int	i;

	i = 1;
	if (scene->has_ambient)
	{
		scene->error = 1;
		scene->err_msg = "Duplicate ambient element";
		return ;
	}
	if (!tokens[1] || !tokens[2])
	{
		scene->error = 1;
		scene->err_msg = "Invalid ambient format";
		return ;
	}
	scene->ambient.ratio = ft_atof(tokens[i++]);
	if (scene->ambient.ratio < 0.0 || scene->ambient.ratio > 1.0)
	{
		scene->error = 1;
		scene->err_msg = "Ambient ratio must be in range [0.0,1.0]";
		return ;
	}
	scene->ambient.color = parse_color(tokens, &i);
	scene->has_ambient = 1;
}

void	parse_light(t_scene *scene, char **tokens)
{
	int		i;

	i = 1;
	if (scene->has_light)
	{
		scene->error = 1;
		scene->err_msg = "Duplicate light element";
		return ;
	}
	if (!tokens[1] || !tokens[2] || !tokens[3])
	{
		scene->error = 1;
		scene->err_msg = "Invalid light format";
		return ;
	}
	if (!create_light(scene, tokens, &i))
		return ;
	scene->has_light = 1;
}

void	parse_camera(t_scene *scene, char **tokens)
{
	int	i;

	i = 1;
	if (scene->has_camera)
	{
		scene->error = 1;
		scene->err_msg = "Duplicate camera element";
		return ;
	}
	if (!tokens[1] || !tokens[2] || !tokens[3])
	{
		scene->error = 1;
		scene->err_msg = "Invalid camera format";
		return ;
	}
	scene->camera.position = parse_vector(tokens, &i);
	scene->camera.orientation = vec3_normalize(parse_vector(tokens, &i));
	scene->camera.fov = ft_atof(tokens[i]);
	if (scene->camera.fov < 0 || scene->camera.fov >= 180)
	{
		scene->error = 1;
		scene->err_msg = "FOV must be in range [0,180)";
		return ;
	}
	scene->has_camera = 1;
}
