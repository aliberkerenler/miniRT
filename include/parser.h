#ifndef PARSER_H
# define PARSER_H

# include "project.h"
# include "../libft/libft.h"
# include <fcntl.h>

# define ERR_PARSE_FILE 10
# define ERR_PARSE_FORMAT 11

t_scene		*parse_scene(const char *filename);
void		free_scene(t_scene *scene);
void		parse_content(t_scene *scene, char *content);
void		parse_ambient(t_scene *scene, char **tokens);
void		parse_light(t_scene *scene, char **tokens);
void		parse_camera(t_scene *scene, char **tokens);
void		parse_sphere(t_scene *scene, char **tokens);
void		parse_plane(t_scene *scene, char **tokens);
void		parse_cylinder(t_scene *scene, char **tokens);

void		add_object(t_scene *scene, t_object *obj);
void		free_split_arr(char **arr);
double		ft_atof(const char *str);
t_vector	parse_vector(char **tokens, int *index);
t_color		parse_color(char **tokens, int *index);
char		*get_next_line(int fd);

#endif