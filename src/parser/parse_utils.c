/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yenyilma <yyenerkaan1@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 00:19:09 by yenyilma          #+#    #+#             */
/*   Updated: 2025/11/30 01:29:34 by yenyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r');
}

double	ft_atof(const char *str)
{
	double	result;
	double	fraction;
	int		sign;

	while (is_space(*str))
		str++;
	sign = 1;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	result = 0;
	while (*str >= '0' && *str <= '9')
		result = result * 10 + (*str++ - '0');
	if (*str == '.')
		str++;
	fraction = 0.1;
	while (*str >= '0' && *str <= '9')
	{
		result += (*str++ - '0') * fraction;
		fraction *= 0.1;
	}
	return (result * sign);
}

void	free_parts(char **parts)
{
	int	i;

	if (!parts)
		return ;
	i = 0;
	while (parts[i])
		free(parts[i++]);
	free(parts);
}

void	init_scene(t_scene *scene)
{
	scene->has_ambient = 0;
	scene->has_camera = 0;
	scene->has_light = 0;
	scene->objects = NULL;
}

int	check_extension(char *filename)
{
	int	len;

	len = ft_strlen(filename);
	if (len < 3)
		return (0);
	return (ft_strncmp(filename + len - 3, ".rt", 3) == 0);
}
