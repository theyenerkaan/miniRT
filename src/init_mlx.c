/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yenyilma <yyenerkaan1@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 00:19:09 by yenyilma          #+#    #+#             */
/*   Updated: 2025/11/30 01:11:51 by yenyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	init_mlx(t_minirt *rt)
{
	rt->mlx.mlx = mlx_init();
	if (!rt->mlx.mlx)
		return (0);
	rt->mlx.win = mlx_new_window(rt->mlx.mlx, WIDTH, HEIGHT, "miniRT");
	if (!rt->mlx.win)
		return (0);
	rt->mlx.img = mlx_new_image(rt->mlx.mlx, WIDTH, HEIGHT);
	if (!rt->mlx.img)
		return (0);
	rt->mlx.addr = mlx_get_data_addr(rt->mlx.img, &rt->mlx.bpp,
			&rt->mlx.line_len, &rt->mlx.endian);
	if (!rt->mlx.addr)
		return (0);
	return (1);
}
