/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_common.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yenyilma <yyenerkaan1@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 00:19:09 by yenyilma          #+#    #+#             */
/*   Updated: 2025/12/22 21:33:42 by yenyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	check_valid_double(double val)
{
	if (val != val)
		return (0);
	if (val > 1e308 || val < -1e308)
		return (0);
	return (1);
}

t_vec3	parse_vec3(char *str)
{
	char	**parts;
	t_vec3	v;

	if (!str || !*str)
		error_exit("Invalid vector format");
	parts = ft_split(str, ',');
	if (!parts || !parts[0] || !parts[1] || !parts[2])
	{
		free_parts(parts);
		error_exit("Invalid vector format");
	}
	if (!*parts[0] || !*parts[1] || !*parts[2])
	{
		free_parts(parts);
		error_exit("Invalid vector format");
	}
	v.x = ft_atof(parts[0]);
	v.y = ft_atof(parts[1]);
	v.z = ft_atof(parts[2]);
	if (!check_valid_double(v.x) || !check_valid_double(v.y)
		|| !check_valid_double(v.z))
	{
		free_parts(parts);
		error_exit("Invalid vector values");
	}
	free_parts(parts);
	return (v);
}

t_color	parse_color(char *str)
{
	char	**parts;
	t_color	c;
	int		rgb[3];

	if (!str || !*str)
		error_exit("Invalid color format");
	parts = ft_split(str, ',');
	if (!parts || !parts[0] || !parts[1] || !parts[2])
	{
		free_parts(parts);
		error_exit("Invalid color format");
	}
	if (!*parts[0] || !*parts[1] || !*parts[2])
	{
		free_parts(parts);
		error_exit("Invalid color format");
	}
	rgb[0] = (int)ft_atof(parts[0]);
	rgb[1] = (int)ft_atof(parts[1]);
	rgb[2] = (int)ft_atof(parts[2]);
	if (rgb[0] < 0 || rgb[0] > 255 || rgb[1] < 0 || rgb[1] > 255
		|| rgb[2] < 0 || rgb[2] > 255)
	{
		free_parts(parts);
		error_exit("Color values must be in range [0-255]");
	}
	c.r = rgb[0] / 255.0;
	c.g = rgb[1] / 255.0;
	c.b = rgb[2] / 255.0;
	free_parts(parts);
	return (c);
}

void	validate_normal_vector(t_vec3 vec, char *error_msg)
{
	double	magnitude;

	if (vec.x < -1.0 || vec.x > 1.0 || vec.y < -1.0 || vec.y > 1.0
		|| vec.z < -1.0 || vec.z > 1.0)
		error_exit(error_msg);
	magnitude = vec.x * vec.x + vec.y * vec.y + vec.z * vec.z;
	if (magnitude < EPSILON)
		error_exit("Direction vector cannot be zero");
	if (magnitude < 0.9 || magnitude > 1.1)
		error_exit(error_msg);
}

void	add_object(t_scene *scene, t_object *new_obj)
{
	t_object	*tmp;

	if (!scene->objects)
	{
		scene->objects = new_obj;
		return ;
	}
	tmp = scene->objects;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_obj;
}
