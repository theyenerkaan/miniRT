/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_context2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yenyilma <yyenerkaan1@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 16:50:00 by yenyilma          #+#    #+#             */
/*   Updated: 2025/12/25 16:50:00 by yenyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

typedef struct s_parse_ctx
{
	t_scene	*scene;
	char	*line;
	char	**parts;
}t_parse_ctx;

extern t_parse_ctx	g_ctx;

void	clear_current_parts(void)
{
	g_ctx.parts = NULL;
}

void	cleanup_parse_context(void)
{
	if (g_ctx.parts)
	{
		free_parts(g_ctx.parts);
		g_ctx.parts = NULL;
	}
	if (g_ctx.line)
	{
		free(g_ctx.line);
		g_ctx.line = NULL;
	}
	if (g_ctx.scene)
	{
		free_scene(g_ctx.scene);
		free(g_ctx.scene);
		g_ctx.scene = NULL;
	}
}
