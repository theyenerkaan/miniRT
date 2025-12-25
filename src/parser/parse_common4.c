/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_common4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yenyilma <yyenerkaan1@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 18:00:00 by yenyilma          #+#    #+#             */
/*   Updated: 2025/12/25 18:00:00 by yenyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

char	*trimmed_dup(const char *start, int len);

static int	is_space_char(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r');
}

int	next_part(char *str, int *i, char **out, int require_comma)
{
	int	start;
	int	end;

	while (str[*i] && is_space_char(str[*i]))
		(*i)++;
	start = *i;
	while (str[*i] && str[*i] != ',')
		(*i)++;
	end = *i;
	*out = trimmed_dup(str + start, end - start);
	if (!*out || !**out)
		return (0);
	if (require_comma)
	{
		if (str[*i] != ',')
			return (0);
		(*i)++;
	}
	else if (str[*i] == ',')
		return (0);
	return (1);
}

int	has_extra(char *str, int i)
{
	while (str[i])
	{
		if (!is_space_char(str[i]))
			return (1);
		i++;
	}
	return (0);
}
