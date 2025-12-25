/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_context.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yenyilma <yyenerkaan1@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 16:30:00 by yenyilma          #+#    #+#             */
/*   Updated: 2025/12/25 16:30:00 by yenyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

typedef struct s_parse_ctx
{
	t_scene	*scene;
	char	*line;
	char	**parts;
}t_parse_ctx;

t_parse_ctx	g_ctx = {0};

void	set_parse_context(t_scene *scene)
{
	g_ctx.scene = scene;
}

void	set_current_line(char *line)
{
	g_ctx.line = line;
}

void	clear_current_line(void)
{
	g_ctx.line = NULL;
}

void	set_current_parts(char **parts)
{
	g_ctx.parts = parts;
}
