/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yenyilma <yyenerkaan1@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 00:19:09 by yenyilma          #+#    #+#             */
/*   Updated: 2026/01/11 17:59:30 by yenyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	check_cap(t_cylinder *cy, double t, double m, double t_min)
{
	if (t < t_min)
		return (0);
	if (!check_height(cy, m))
		return (0);
	return (1);
}

static int	hit_body(t_ray ray, t_cylinder *cy, t_hit *hit, double t_min)
{
	t_vec3	oc;
	double	abc[3];
	double	discriminant;
	double	m;

	oc = vec3_sub(ray.origin, cy->center);
	calc_cylinder_abc(ray, cy, oc, abc);
	discriminant = abc[1] * abc[1] - 4 * abc[0] * abc[2];
	if (discriminant < 0)
		return (0);
	hit->t = solve_cylinder(abc, discriminant, 1);
	m = vec3_dot(ray.dir, cy->axis) * hit->t + vec3_dot(oc, cy->axis);
	if (!check_cap(cy, hit->t, m, t_min))
	{
		hit->t = solve_cylinder(abc, discriminant, 0);
		m = vec3_dot(ray.dir, cy->axis) * hit->t + vec3_dot(oc, cy->axis);
		if (!check_cap(cy, hit->t, m, t_min))
			return (0);
	}
	hit->point = ray_at(ray, hit->t);
	hit->normal = vec3_normalize(vec3_sub(vec3_sub(hit->point, cy->center),
				vec3_scale(cy->axis, m)));
	return (1);
}

int	hit_cylinder(t_ray ray, t_cylinder *cy, double t_min, t_hit *hit)
{
	if (!hit_body(ray, cy, hit, t_min))
		return (0);
	hit->color = cy->color;
	return (1);
}
