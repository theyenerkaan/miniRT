/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_context.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yenyilma <yyenerkaan1@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 16:30:00 by yenyilma          #+#    #+#             */
/*   Updated: 2026/01/11 20:43:30 by yenyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_parse_ctx	*get_parse_context(void)
{
	static t_parse_ctx	ctx = {0};

	return (&ctx);
}

void	set_parse_context(t_scene *scene)
{
	t_parse_ctx	*ctx;

	ctx = get_parse_context();
	ctx->scene = scene;
}

void	set_current_line(char *line)
{
	t_parse_ctx	*ctx;

	ctx = get_parse_context();
	ctx->line = line;
}

void	clear_current_line(void)
{
	t_parse_ctx	*ctx;

	ctx = get_parse_context();
	ctx->line = NULL;
}

void	set_current_parts(char **parts)
{
	t_parse_ctx	*ctx;

	ctx = get_parse_context();
	ctx->parts = parts;
}
