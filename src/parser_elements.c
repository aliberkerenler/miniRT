#include "../include/parser.h"
#include "../include/minirt.h"
#include "../include/vec3.h"
#include "../include/render.h"

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

static void	parse_line_tokens(t_scene *scene, char **tokens)
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
	else if (ft_strncmp(tokens[0], "cy", 3) == 0)
		parse_cylinder(scene, tokens);
	else
	{
		scene->error = 1;
		scene->err_msg = "Unknown element identifier";
	}
}

static void	replace_tabs(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\t')
			line[i] = ' ';
		i++;
	}
}

static void	process_line(t_scene *scene, char *line)
{
	char	**tokens;

	replace_tabs(line);
	tokens = ft_split(line, ' ');
	if (tokens && tokens[0])
		parse_line_tokens(scene, tokens);
	if (tokens)
		free_tokens(tokens);
}

void	parse_content(t_scene *scene, char *content)
{
	char	**lines;
	int		i;

	lines = ft_split(content, '\n');
	if (!lines)
		exit_error("Failed to parse file", ERR_PARSE_FILE);
	i = 0;
	while (lines[i])
	{
		if (lines[i][0])
			process_line(scene, lines[i]);
		free(lines[i++]);
		if (scene->error)
			break ;
	}
	while (lines[i])
		free(lines[i++]);
	free(lines);
}
