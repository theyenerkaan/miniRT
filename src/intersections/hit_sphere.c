/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_sphere.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yenyilma <yyenerkaan1@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 00:19:09 by yenyilma          #+#    #+#             */
/*   Updated: 2025/12/22 21:33:42 by yenyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	hit_sphere(t_ray ray, t_sphere *sp, double t_min, t_hit *hit)
{
	t_vec3	oc;
	double	abc[3];
	double	discriminant;
	double	radius;

	radius = sp->diameter / 2.0;
	oc = vec3_sub(ray.origin, sp->center);
	abc[0] = vec3_dot(ray.dir, ray.dir);
	abc[1] = 2.0 * vec3_dot(oc, ray.dir);
	abc[2] = vec3_dot(oc, oc) - radius * radius;
	discriminant = abc[1] * abc[1] - 4 * abc[0] * abc[2];
	if (discriminant < 0)
		return (0);
	hit->t = (-abc[1] - sqrt(discriminant)) / (2.0 * abc[0]);
	if (hit->t < t_min)
		hit->t = (-abc[1] + sqrt(discriminant)) / (2.0 * abc[0]);
	if (hit->t < t_min)
		return (0);
	hit->point = ray_at(ray, hit->t);
	hit->normal = vec3_normalize(vec3_sub(hit->point, sp->center));
	hit->color = sp->color;
	return (1);
}
