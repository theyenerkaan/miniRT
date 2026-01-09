/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_context3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yenyilma <yyenerkaan1@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 17:00:00 by yenyilma          #+#    #+#             */
/*   Updated: 2026/01/09 17:00:00 by yenyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	register_temp_alloc(void *ptr)
{
	t_parse_ctx	*ctx;

	if (!ptr)
		return ;
	ctx = get_parse_context();
	if (ctx->temp_count < MAX_TEMP_ALLOCS)
		ctx->temp_allocs[ctx->temp_count++] = ptr;
}

void	unregister_temp_alloc(void *ptr)
{
	t_parse_ctx	*ctx;
	int			i;

	if (!ptr)
		return ;
	ctx = get_parse_context();
	i = 0;
	while (i < ctx->temp_count)
	{
		if (ctx->temp_allocs[i] == ptr)
		{
			while (i < ctx->temp_count - 1)
			{
				ctx->temp_allocs[i] = ctx->temp_allocs[i + 1];
				i++;
			}
			ctx->temp_count--;
			return ;
		}
		i++;
	}
}

void	clear_temp_allocs(void)
{
	t_parse_ctx	*ctx;
	int			i;

	ctx = get_parse_context();
	i = 0;
	while (i < ctx->temp_count)
	{
		free(ctx->temp_allocs[i]);
		i++;
	}
	ctx->temp_count = 0;
}
