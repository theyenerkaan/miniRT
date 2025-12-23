/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yenyilma <yyenerkaan1@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 00:19:09 by yenyilma          #+#    #+#             */
/*   Updated: 2025/12/22 21:33:42 by yenyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	parse_ambient(t_scene *scene, char **parts);
void	parse_camera(t_scene *scene, char **parts);
void	parse_light(t_scene *scene, char **parts);
void	parse_sphere(t_scene *scene, char **parts);
void	parse_plane(t_scene *scene, char **parts);
void	parse_cylinder(t_scene *scene, char **parts);
void	free_parts(char **parts);
void	init_scene(t_scene *scene);
int		check_extension(char *filename);

static void	parse_line_element(t_scene *scene, char **parts)
{
	if (ft_strncmp(parts[0], "A", 2) == 0)
		parse_ambient(scene, parts);
	else if (ft_strncmp(parts[0], "C", 2) == 0)
		parse_camera(scene, parts);
	else if (ft_strncmp(parts[0], "L", 2) == 0)
		parse_light(scene, parts);
	else if (ft_strncmp(parts[0], "sp", 3) == 0)
		parse_sphere(scene, parts);
	else if (ft_strncmp(parts[0], "pl", 3) == 0)
		parse_plane(scene, parts);
	else if (ft_strncmp(parts[0], "cy", 3) == 0)
		parse_cylinder(scene, parts);
	else
		error_exit("Invalid identifier (expected: A, C, L, sp, pl, cy)");
}

static void	process_line(t_scene *scene, char *line)
{
	char	**parts;
	int		len;

	if (!line || !*line || *line == '\n' || *line == '#')
		return ;
	len = ft_strlen(line);
	while (len > 0 && (line[len - 1] == ' ' || line[len - 1] == '\t'
			|| line[len - 1] == '\n' || line[len - 1] == '\r'))
		line[--len] = '\0';
	if (len == 0)
		return ;
	parts = ft_split(line, ' ');
	if (!parts || !parts[0])
	{
		free_parts(parts);
		return ;
	}
	parse_line_element(scene, parts);
	free_parts(parts);
}

t_scene	*parse_scene(char *filename)
{
	t_scene	*scene;
	char	*line;
	int		fd;

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
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		error_exit("Cannot open file");
	scene = malloc(sizeof(t_scene));
	if (!scene)
		error_exit("Memory allocation failed");
	init_scene(scene);
	line = get_next_line(fd);
	while (line)
	{
		process_line(scene, line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	if (!scene->has_ambient || !scene->has_camera || !scene->has_light)
		error_exit("Missing required elements (A, C, L)");
	if (scene->object_count == 0)
		error_exit("Scene must contain at least one object (sp, pl, cy)");
	return (scene);
}
