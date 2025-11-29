/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_plane.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yenyilma <yyenerkaan1@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 00:19:09 by yenyilma          #+#    #+#             */
/*   Updated: 2025/11/30 01:11:51 by yenyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	hit_plane(t_ray ray, t_plane *pl, double t_min, t_hit *hit)
{
	double	denom;
	double	t;
	t_vec3	p0;

	denom = vec3_dot(ray.dir, pl->normal);
	if (fabs(denom) < EPSILON)
		return (0);
	p0 = vec3_sub(pl->point, ray.origin);
	t = vec3_dot(p0, pl->normal) / denom;
	if (t < t_min)
		return (0);
	hit->t = t;
	hit->point = ray_at(ray, t);
	hit->normal = pl->normal;
	if (vec3_dot(ray.dir, hit->normal) > 0)
		hit->normal = vec3_scale(hit->normal, -1);
	hit->color = pl->color;
	return (1);
}
