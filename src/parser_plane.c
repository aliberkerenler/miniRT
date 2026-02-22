#include "../include/parser.h"
#include "../include/minirt.h"
#include "../include/vec3.h"
#include "../include/render.h"

void	parse_plane(t_scene *scene, char **tokens)
{
	t_plane		*plane;
	t_object	*obj;
	int			i;

	i = 1;
	if (!tokens[1] || !tokens[2] || !tokens[3])
	{
		scene->error = 1;
		scene->err_msg = "Invalid plane format";
		return ;
	}
	plane = malloc(sizeof(t_plane));
	if (!plane)
		exit_error("Memory allocation failed", ERR_MALLOC);
	plane->point = parse_vector(tokens, &i);
	plane->normal = vec3_normalize(parse_vector(tokens, &i));
	plane->color = parse_color(tokens, &i);
	obj = malloc(sizeof(t_object));
	if (!obj)
		exit_error("Memory allocation failed", ERR_MALLOC);
	obj->type = OBJ_PLANE;
	obj->data = plane;
	add_object(scene, obj);
}
