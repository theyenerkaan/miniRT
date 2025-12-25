/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yenyilma <yyenerkaan1@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 16:55:00 by yenyilma          #+#    #+#             */
/*   Updated: 2025/12/25 16:55:00 by yenyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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

double	parse_decimal_part(const char **str)
{
	double	result;
	double	fraction;

	result = 0;
	fraction = 0.1;
	if (**str == '.')
		(*str)++;
	while (**str && **str >= '0' && **str <= '9')
	{
		result += (*(*str)++ - '0') * fraction;
		fraction *= 0.1;
	}
	return (result);
}

int	is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r');
}

int	check_sign_and_space(const char *str, int i)
{
	if (str[i] == '+' || str[i] == '-')
	{
		if (!str[i + 1] || str[i + 1] == '+' || str[i + 1] == '-')
			return (-1);
		if (is_space(str[i + 1]))
			return (-1);
		return (i + 1);
	}
	return (i);
}
