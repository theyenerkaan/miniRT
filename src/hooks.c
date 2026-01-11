/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yenyilma <yyenerkaan1@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 00:19:09 by yenyilma          #+#    #+#             */
/*   Updated: 2026/01/11 19:01:22 by yenyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	close_window(void *param)
{
	t_minirt	*rt;

	rt = (t_minirt *)param;
	if (rt->mlx.img)
		mlx_destroy_image(rt->mlx.mlx, rt->mlx.img);
	if (rt->mlx.win)
		mlx_destroy_window(rt->mlx.mlx, rt->mlx.win);
	if (rt->mlx.mlx)
	{
		mlx_destroy_display(rt->mlx.mlx);
		free(rt->mlx.mlx);
	}
	free_scene(&rt->scene);
	exit(0);
	return (0);
}

int	key_press(int keycode, void *param)
{
	if (keycode == 65307)
		close_window(param);
	return (0);
}
