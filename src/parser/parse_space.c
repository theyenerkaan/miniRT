/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yenyilma <yyenerkaan1@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 00:00:00 by yenyilma          #+#    #+#             */
/*   Updated: 2025/12/25 16:23:14 by yenyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	all_whitespace(const char *buf, ssize_t len)
{
	ssize_t	i;

	i = 0;
	while (i < len)
	{
		if (buf[i] != ' ' && buf[i] != '\t' && buf[i] != '\n' && buf[i] != '\r')
			return (0);
		i++;
	}
	return (1);
}

int	is_empty_file(int fd)
{
	char		buf[256];
	ssize_t		read_bytes;
	int			only_ws;

	only_ws = 1;
	read_bytes = read(fd, buf, sizeof(buf));
	if (read_bytes < 0)
		error_exit("Cannot read file");
	while (read_bytes > 0)
	{
		if (!all_whitespace(buf, read_bytes))
			only_ws = 0;
		read_bytes = read(fd, buf, sizeof(buf));
		if (read_bytes < 0)
			error_exit("Cannot read file");
	}
	return (only_ws);
}
