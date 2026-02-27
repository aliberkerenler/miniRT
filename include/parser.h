/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerenler <aerenler@student.42istanbul.com.t+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 15:06:11 by aerenler          #+#    #+#             */
/*   Updated: 2026/02/27 15:47:42 by aerenler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
char		*get_next_line(int fd);

int			is_valid_int(const char *str);
int			is_valid_float(const char *str);
int			validate_comma_format(const char *str, int expected_count);
int			validate_color_values(char **rgb);
int			validate_vector_values(char **coords);
int			count_tokens(char **tokens);

int			parse_vector_safe(char **tokens, int *index,
				t_vector *out, t_scene *scene);
int			parse_color_safe(char **tokens, int *index,
				t_color *out, t_scene *scene);
int			parse_orientation_safe(char **tokens, int *index,
				t_vector *out, t_scene *scene);
int			parse_float_safe(const char *str, double *out, t_scene *scene,
				const char *err_msg);
int			set_err(t_scene *scene, const char *msg);
int			check_duplicate(t_scene *scene, int has_flag, const char *msg);
int			check_token_count(t_scene *scene, char **tokens,
				int expected, const char *msg);

#endif
