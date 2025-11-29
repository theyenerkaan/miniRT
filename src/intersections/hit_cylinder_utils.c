/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cylinder_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yenyilma <yyenerkaan1@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 00:19:09 by yenyilma          #+#    #+#             */
/*   Updated: 2025/11/30 01:11:51 by yenyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	check_height(t_cylinder *cy, double m)
{
	if (m < 0 || m > cy->height)
		return (0);
	return (1);
}

void	calc_cylinder_abc(t_ray ray, t_cylinder *cy, t_vec3 oc, double *abc)
{
	abc[0] = vec3_dot(ray.dir, ray.dir) - pow(vec3_dot(ray.dir, cy->axis), 2);
	abc[1] = 2 * (vec3_dot(ray.dir, oc) - vec3_dot(ray.dir, cy->axis)
			* vec3_dot(oc, cy->axis));
	abc[2] = vec3_dot(oc, oc) - pow(vec3_dot(oc, cy->axis), 2)
		- pow(cy->diameter / 2.0, 2);
}

double	solve_cylinder(double *abc, double discriminant, int first)
{
	if (first)
		return ((-abc[1] - sqrt(discriminant)) / (2.0 * abc[0]));
	return ((-abc[1] + sqrt(discriminant)) / (2.0 * abc[0]));
}
