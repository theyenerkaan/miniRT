/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yenyilma <yyenerkaan1@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 00:19:09 by yenyilma          #+#    #+#             */
/*   Updated: 2025/11/30 01:11:51 by yenyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	check_object_hit(t_ray ray, t_object *obj, t_hit *hit,
	t_hit *closest)
{
	int	did_hit;

	did_hit = 0;
	if (obj->type == OBJ_SPHERE)
		did_hit = hit_sphere(ray, (t_sphere *)obj->data, EPSILON, hit);
	else if (obj->type == OBJ_PLANE)
		did_hit = hit_plane(ray, (t_plane *)obj->data, EPSILON, hit);
	else if (obj->type == OBJ_CYLINDER)
		did_hit = hit_cylinder(ray, (t_cylinder *)obj->data, EPSILON, hit);
	if (did_hit && hit->t < closest->t)
	{
		*closest = *hit;
		return (1);
	}
	return (0);
}

int	trace_ray(t_ray ray, t_scene *scene, t_hit *closest)
{
	t_object	*obj;
	t_hit		hit;
	int			hit_anything;

	hit_anything = 0;
	closest->t = 1e30;
	obj = scene->objects;
	while (obj)
	{
		if (check_object_hit(ray, obj, &hit, closest))
			hit_anything = 1;
		obj = obj->next;
	}
	return (hit_anything);
}
