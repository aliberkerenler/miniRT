#ifndef PARSER_H
# define PARSER_H

# include "project.h"
# include "../libft/libft.h"
# include <fcntl.h>

/* Parser hata kodları */
# define ERR_PARSE_FILE 10
# define ERR_PARSE_FORMAT 11
# define ERR_PARSE_CAMERA 12
# define ERR_PARSE_SPHERE 13

/* Parser fonksiyonları */
t_scene		*parse_scene(const char *filename);
void		free_scene(t_scene *scene);
void		parse_content(t_scene *scene, char *content);

/* Yardımcı fonksiyonlar */
double		parse_double(const char *str);
t_vector	parse_vector(char **tokens, int *index);
t_color		parse_color(char **tokens, int *index);
char		*get_next_line(int fd);

#endif

