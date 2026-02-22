/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_create.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ualkan <ualkan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 12:34:02 by ualkan            #+#    #+#             */
/*   Updated: 2026/02/22 12:34:04 by ualkan           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../include/vec3.h"

t_vector	vec3(double x, double y, double z)
{
	t_vector	v;

	v.x = x;
	v.y = y;
	v.z = z;
	return (v);
}

t_vector	vec3_zero(void)
{
	return (vec3(0.0, 0.0, 0.0));
}
