/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ualkan <ualkan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 12:33:04 by ualkan            #+#    #+#             */
/*   Updated: 2026/02/22 12:33:06 by ualkan           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../include/render.h"
#include "../include/vec3.h"

static bool	check_object_hit(t_object *obj, t_ray *ray, t_hit_record *rec)
{
	if (obj->type == OBJ_SPHERE)
		return (hit_sphere((t_sphere *)obj->data, ray, rec));
	else if (obj->type == OBJ_PLANE)
		return (hit_plane((t_plane *)obj->data, ray, rec));
	else if (obj->type == OBJ_CYLINDER)
		return (hit_cylinder((t_cylinder *)obj->data, ray, rec));
	return (false);
}

bool	find_closest_hit(t_scene *scene, t_ray *ray, t_hit_record *rec,
			t_object **hit_obj)
{
	t_object		*obj;
	t_hit_record	temp_rec;
	bool			hit_anything;
	double			closest;

	hit_anything = false;
	closest = INFINITY;
	obj = scene->objects;
	while (obj)
	{
		if (check_object_hit(obj, ray, &temp_rec))
		{
			if (temp_rec.t < closest)
			{
				closest = temp_rec.t;
				*rec = temp_rec;
				*hit_obj = obj;
				hit_anything = true;
			}
		}
		obj = obj->next;
	}
	return (hit_anything);
}
