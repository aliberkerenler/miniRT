/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerenler <aerenler@student.42istanbul.com.t+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 15:08:39 by aerenler          #+#    #+#             */
/*   Updated: 2026/02/27 16:21:49 by aerenler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"
#include "../../include/minirt.h"
#include "../../include/vec3.h"
#include <unistd.h>

static int	validate_and_open(const char *filename)
{
	int	len;
	int	fd;

	len = ft_strlen(filename);
	if (len < 4 || ft_strncmp(filename + len - 3, ".rt", 4) != 0)
		exit_error("Invalid file extension, expected .rt", ERR_PARSE_FILE);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		exit_error("Can't open .rt file", ERR_PARSE_FILE);
	return (fd);
}

static char	*read_file(int fd)
{
	char	*line;
	char	*content;
	char	*temp;

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
		if (!content)
		{
			close(fd);
			exit_error("Memory allocation failed", ERR_MALLOC);
		}
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
	scene->objects = NULL;
	scene->has_ambient = 0;
	scene->has_camera = 0;
	scene->has_light = 0;
	scene->error = 0;
	scene->err_msg = NULL;
}

static void	check_scene_errors(t_scene *scene)
{
	const char	*msg;

	if (scene->error)
	{
		msg = scene->err_msg;
		free_scene(scene);
		exit_error(msg, ERR_PARSE_FORMAT);
	}
	if (!scene->has_ambient || !scene->has_camera || !scene->has_light)
	{
		free_scene(scene);
		exit_error("Missing required elements (A, C, L)", ERR_PARSE_FORMAT);
	}
}

t_scene	*parse_scene(const char *filename)
{
	t_scene		*scene;
	char		*content;
	int			fd;

	fd = validate_and_open(filename);
	scene = malloc(sizeof(t_scene));
	if (!scene)
	{
		close(fd);
		exit_error("Memory allocation failed", ERR_MALLOC);
	}
	init_scene(scene);
	content = read_file(fd);
	parse_content(scene, content);
	free(content);
	check_scene_errors(scene);
	return (scene);
}
