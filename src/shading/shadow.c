/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yenyilma <yyenerkaan1@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 00:19:09 by yenyilma          #+#    #+#             */
/*   Updated: 2025/12/22 21:58:48 by yenyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	check_object_shadow(t_ray shadow_ray, t_object *obj,
	double light_dist)
{
	t_hit	tmp_hit;

	tmp_hit.t = light_dist;
	if (obj->type == OBJ_SPHERE)
	{
		if (hit_sphere(shadow_ray, (t_sphere *)obj->data, EPSILON, &tmp_hit))
			if (tmp_hit.t < light_dist)
				return (1);
	}
	else if (obj->type == OBJ_PLANE)
	{
		if (hit_plane(shadow_ray, (t_plane *)obj->data, EPSILON, &tmp_hit))
			if (tmp_hit.t < light_dist)
				return (1);
	}
	else if (obj->type == OBJ_CYLINDER)
	{
		if (hit_cylinder(shadow_ray, (t_cylinder *)obj->data,
				EPSILON, &tmp_hit))
			if (tmp_hit.t < light_dist)
				return (1);
	}
	return (0);
}

int	is_in_shadow(t_hit *hit, t_scene *scene)
{
	t_vec3		light_vec;
	double		light_dist;
	t_ray		shadow_ray;
	t_object	*obj;
	t_vec3		offset_point;

	light_vec = vec3_sub(scene->light.pos, hit->point);
	light_dist = vec3_len(light_vec);
	offset_point = vec3_add(hit->point, vec3_scale(hit->normal, 0.001));
	shadow_ray = ray_new(offset_point, vec3_normalize(light_vec));
	obj = scene->objects;
	while (obj)
	{
		if (check_object_shadow(shadow_ray, obj, light_dist))
			return (1);
		obj = obj->next;
	}
	return (0);
}
