/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_context2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yenyilma <yyenerkaan1@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 16:50:00 by yenyilma          #+#    #+#             */
/*   Updated: 2026/01/09 16:50:13 by yenyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	clear_current_parts(void)
{
	t_parse_ctx	*ctx;

	ctx = get_parse_context();
	ctx->parts = NULL;
}

static void	cleanup_temp_allocs(t_parse_ctx *ctx)
{
	int	i;

	i = 0;
	while (i < ctx->temp_count)
	{
		free(ctx->temp_allocs[i]);
		i++;
	}
	ctx->temp_count = 0;
}

void	cleanup_parse_context(void)
{
	t_parse_ctx	*ctx;

	ctx = get_parse_context();
	cleanup_temp_allocs(ctx);
	if (ctx->parts)
	{
		free_parts(ctx->parts);
		ctx->parts = NULL;
	}
	if (ctx->line)
	{
		free(ctx->line);
		ctx->line = NULL;
	}
	if (ctx->scene)
	{
		free_scene(ctx->scene);
		free(ctx->scene);
		ctx->scene = NULL;
	}
}
