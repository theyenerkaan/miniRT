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
	scene->object_count = 0;
}

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

static int	is_whitespace_line(char *line)
{
	if (!line)
		return (1);
	while (*line)
	{
		if (*line != ' ' && *line != '\t' && *line != '\n' && *line != '\r')
			return (0);
		line++;
	}
	return (1);
}

int	is_empty_file(int fd)
{
	char	*line;
	int		has_content;

	has_content = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (!is_whitespace_line(line))
			has_content = 1;
		free(line);
		if (has_content)
			break ;
		line = get_next_line(fd);
	}
	while (line)
	{
		line = get_next_line(fd);
		if (line)
			free(line);
	}
	return (!has_content);
}
