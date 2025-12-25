/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yenyilma <yyenerkaan1@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 00:19:09 by yenyilma          #+#    #+#             */
/*   Updated: 2025/12/25 16:23:14 by yenyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	error_exit(char *msg)
{
	write(2, "Error\n", 6);
	if (msg)
	{
		while (*msg)
			write(2, msg++, 1);
		write(2, "\n", 1);
	}
	get_next_line(-1);
	cleanup_parse_context();
	exit(1);
}

static void	free_objects(t_object *obj)
{
	t_object	*tmp;

	while (obj)
	{
		tmp = obj->next;
		if (obj->data)
			free(obj->data);
		free(obj);
		obj = tmp;
	}
}

void	free_scene(t_scene *scene)
{
	if (!scene)
		return ;
	free_objects(scene->objects);
}
