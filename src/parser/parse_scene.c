/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yenyilma <yyenerkaan1@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 00:19:09 by yenyilma          #+#    #+#             */
/*   Updated: 2025/12/25 15:25:26 by yenyilma         ###   ########.fr       */
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
int		check_extension(char *filename);
int		is_empty_file(int fd);
t_scene	*parse_scene_file(char *filename);

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

static void	clean_line(char *line, int *len)
{
	while (line[*len])
	{
		if (line[*len] == '\t')
			line[*len] = ' ';
		(*len)++;
	}
	*len = ft_strlen(line);
	while (*len > 0 && (line[*len - 1] == ' ' || line[*len - 1] == '\t'
			|| line[*len - 1] == '\n' || line[*len - 1] == '\r'))
		line[--(*len)] = '\0';
}

void	process_line(t_scene *scene, char *line)
{
	char	**parts;
	int		len;

	if (!line || !*line || *line == '\n' || *line == '#')
		return ;
	len = 0;
	clean_line(line, &len);
	if (len == 0)
		return ;
	parts = ft_split(line, ' ');
	set_current_parts(parts);
	if (!parts || !parts[0])
	{
		free_parts(parts);
		clear_current_parts();
		return ;
	}
	parse_line_element(scene, parts);
	free_parts(parts);
	clear_current_parts();
}

t_scene	*parse_scene(char *filename)
{
	return (parse_scene_file(filename));
}
