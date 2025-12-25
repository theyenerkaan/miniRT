/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_common.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yenyilma <yyenerkaan1@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 00:19:09 by yenyilma          #+#    #+#             */
/*   Updated: 2025/12/25 15:38:14 by yenyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		next_part(char *str, int *i, char **out, int require_comma);
int		has_extra(char *str, int i);
void	free_three(char *a, char *b, char *c);
void	validate_rgb(int *rgb);

static void	parse_vec3_parts(char *str, char **xs, char **ys, char **zs)
{
	int	idx;

	*xs = NULL;
	*ys = NULL;
	*zs = NULL;
	if (!str || !*str)
		error_exit("Invalid vector format");
	idx = 0;
	if (!next_part(str, &idx, xs, 1) || !next_part(str, &idx, ys, 1)
		|| !next_part(str, &idx, zs, 0) || has_extra(str, idx))
	{
		free_three(*xs, *ys, *zs);
		error_exit("Invalid vector format");
	}
}

t_vec3	parse_vec3(char *str)
{
	char	*xs;
	char	*ys;
	char	*zs;
	t_vec3	v;

	parse_vec3_parts(str, &xs, &ys, &zs);
	v.x = ft_atof(xs);
	v.y = ft_atof(ys);
	v.z = ft_atof(zs);
	free_three(xs, ys, zs);
	return (v);
}

static int	has_dot(const char *s)
{
	int	index;

	index = 0;
	while (s[index])
	{
		if (s[index] == '.')
			return (1);
		index++;
	}
	return (0);
}

static void	parse_color_parts(char *str, char **rs, char **gs, char **bs)
{
	int	idx;

	*rs = NULL;
	*gs = NULL;
	*bs = NULL;
	if (!str || !*str)
		error_exit("Invalid color format");
	idx = 0;
	if (!next_part(str, &idx, rs, 1) || !next_part(str, &idx, gs, 1)
		|| !next_part(str, &idx, bs, 0) || has_extra(str, idx))
	{
		free_three(*rs, *gs, *bs);
		error_exit("Invalid color format");
	}
	if (has_dot(*rs) || has_dot(*gs) || has_dot(*bs))
	{
		free_three(*rs, *gs, *bs);
		error_exit("Invalid color format");
	}
}

t_color	parse_color(char *str)
{
	char	*rs;
	char	*gs;
	char	*bs;
	int		rgb[3];
	t_color	c;

	parse_color_parts(str, &rs, &gs, &bs);
	rgb[0] = (int)ft_atof(rs);
	rgb[1] = (int)ft_atof(gs);
	rgb[2] = (int)ft_atof(bs);
	free_three(rs, gs, bs);
	validate_rgb(rgb);
	c.r = rgb[0] / 255.0;
	c.g = rgb[1] / 255.0;
	c.b = rgb[2] / 255.0;
	return (c);
}
