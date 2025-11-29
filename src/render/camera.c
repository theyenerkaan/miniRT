/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yenyilma <yyenerkaan1@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 00:19:09 by yenyilma          #+#    #+#             */
/*   Updated: 2025/11/30 01:11:51 by yenyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	setup_camera(t_camera *cam)
{
	double	theta;
	double	h;
	double	aspect;
	t_vec3	world_up;

	theta = cam->fov * M_PI / 180.0;
	h = tan(theta / 2.0);
	aspect = (double)WIDTH / (double)HEIGHT;
	cam->vp_height = 2.0 * h;
	cam->vp_width = cam->vp_height * aspect;
	world_up = vec3_new(0, 1, 0);
	if (fabs(vec3_dot(cam->dir, world_up)) > 0.999)
		world_up = vec3_new(0, 0, 1);
	cam->right = vec3_normalize(vec3_cross(cam->dir, world_up));
	cam->up = vec3_cross(cam->right, cam->dir);
	cam->lower_left = vec3_sub(cam->pos, vec3_scale(cam->right,
				cam->vp_width / 2.0));
	cam->lower_left = vec3_sub(cam->lower_left, vec3_scale(cam->up,
				cam->vp_height / 2.0));
	cam->lower_left = vec3_add(cam->lower_left, cam->dir);
}

t_ray	get_ray(t_camera *cam, double u, double v)
{
	t_vec3	point;

	point = vec3_add(cam->lower_left, vec3_scale(cam->right,
				u * cam->vp_width));
	point = vec3_add(point, vec3_scale(cam->up, v * cam->vp_height));
	return (ray_new(cam->pos, vec3_normalize(vec3_sub(point, cam->pos))));
}
