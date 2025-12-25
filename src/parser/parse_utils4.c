/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yenyilma <yyenerkaan1@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 18:10:00 by yenyilma          #+#    #+#             */
/*   Updated: 2025/12/25 18:10:00 by yenyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	check_extension(char *filename)
{
	int	len;

	if (!filename)
		return (0);
	len = ft_strlen(filename);
	if (len < 4)
		return (0);
	return (ft_strncmp(filename + len - 3, ".rt", 3) == 0);
}

void	init_scene(t_scene *scene)
{
	scene->has_ambient = 0;
	scene->has_camera = 0;
	scene->has_light = 0;
	scene->objects = NULL;
	scene->object_count = 0;
}
