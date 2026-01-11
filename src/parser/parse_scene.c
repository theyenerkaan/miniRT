/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yenyilma <yyenerkaan1@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 00:00:00 by yenyilma          #+#    #+#             */
/*   Updated: 2026/01/11 18:02:34 by yenyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	open_and_check_file(char *filename)
{
	int	fd;

	if (!check_extension(filename))
		error_exit("File must have .rt extension");
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		error_exit("Cannot open file");
	if (is_empty_file(fd))
	{
		close(fd);
		error_exit("Empty scene");
	}
	close(fd);
	return (fd);
}

static t_scene	*allocate_scene(void)
{
	t_scene	*scene;

	scene = malloc(sizeof(t_scene));
	if (!scene)
		error_exit("Memory allocation failed");
	init_scene(scene);
	return (scene);
}

static void	read_scene_file(t_scene *scene, int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		set_current_line(line);
		process_line(scene, line);
		free(line);
		clear_current_line();
		line = get_next_line(fd);
	}
}

static void	validate_scene(t_scene *scene)
{
	if (!scene->has_ambient || !scene->has_camera)
		error_exit("Missing required elements (A, C)");
	if (scene->object_count == 0)
		error_exit("Scene must contain at least one object (sp, pl, cy)");
}

t_scene	*parse_scene_file(char *filename)
{
	t_scene	*scene;
	int		fd;

	open_and_check_file(filename);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		error_exit("Cannot open file");
	scene = allocate_scene();
	set_parse_context(scene);
	read_scene_file(scene, fd);
	close(fd);
	get_next_line(-1);
	validate_scene(scene);
	set_parse_context(NULL);
	return (scene);
}
