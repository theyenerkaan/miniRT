/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_common3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yenyilma <yyenerkaan1@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 16:50:00 by yenyilma          #+#    #+#             */
/*   Updated: 2025/12/25 16:50:00 by yenyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	is_space_char(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r');
}

char	*trimmed_dup(const char *start, int len)
{
	while (len > 0 && is_space_char(*start))
	{
		start++;
		len--;
	}
	while (len > 0 && is_space_char(start[len - 1]))
		len--;
	if (len <= 0)
		return (NULL);
	return (ft_substr(start, 0, len));
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
