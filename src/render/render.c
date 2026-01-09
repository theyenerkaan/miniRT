/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yenyilma <yyenerkaan1@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 00:19:09 by yenyilma          #+#    #+#             */
/*   Updated: 2026/01/09 17:12:47 by yenyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_ray		get_ray(t_camera *cam, double u, double v);
int			trace_ray(t_ray ray, t_scene *scene, t_hit *closest);
t_color		compute_lighting(t_hit *hit, t_scene *scene, t_vec3 light_dir);
int			is_in_shadow(t_hit *hit, t_scene *scene);

static void	put_pixel(t_mlx *mlx, int x, int y, int color)
{
	char	*dst;

	dst = mlx->addr + (y * mlx->line_len + x * (mlx->bpp / 8));
	*(unsigned int *)dst = color;
}

static t_color	trace_pixel(t_scene *scene, int x, int y)
{
	t_ray	ray;
	t_hit	hit;
	t_vec3	light_dir;
	double	u;
	double	v;

	u = (double)x / (double)WIDTH;
	v = 1.0 - ((double)y / (double)HEIGHT);
	ray = get_ray(&scene->camera, u, v);
	if (trace_ray(ray, scene, &hit))
	{
		if (!scene->has_light)
			return (color_scale(hit.color, scene->ambient.ratio));
		light_dir = vec3_normalize(vec3_sub(scene->light.pos, hit.point));
		if (is_in_shadow(&hit, scene))
			return (color_scale(hit.color, scene->ambient.ratio));
		return (compute_lighting(&hit, scene, light_dir));
	}
	return (color_new(0, 0, 0));
}

void	render_scene(t_minirt *rt)
{
	int		x;
	int		y;
	t_color	color;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			color = trace_pixel(&rt->scene, x, y);
			put_pixel(&rt->mlx, x, y, color_to_int(color));
			x++;
		}
		y++;
	}
}
