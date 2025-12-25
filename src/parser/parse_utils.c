/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yenyilma <yyenerkaan1@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 00:19:09 by yenyilma          #+#    #+#             */
/*   Updated: 2025/12/25 16:23:14 by yenyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	parse_decimal_part(const char **str);
int		is_space(char c);
int		check_sign_and_space(const char *str, int i);

static int	check_remaining(const char *str, int i, int dots, int digits)
{
	while (str[i])
	{
		if (is_space(str[i]))
		{
			while (str[i] && is_space(str[i]))
				i++;
			return (str[i] == '\0' && digits);
		}
		if (str[i] == '.')
		{
			dots++;
			if (dots > 1 || !ft_isdigit(str[i + 1]))
				return (0);
		}
		else if (ft_isdigit(str[i]))
			digits = 1;
		else
			return (0);
		i++;
	}
	return (digits);
}

static int	valid_number_format(const char *str)
{
	int	i;
	int	result;

	i = 0;
	while (str[i] && is_space(str[i]))
		i++;
	result = check_sign_and_space(str, i);
	if (result < 0)
		return (0);
	return (check_remaining(str, result, 0, 0));
}

static double	parse_integer_part(const char **str)
{
	double	result;

	result = 0;
	while (**str && **str >= '0' && **str <= '9')
		result = result * 10 + (*(*str)++ - '0');
	return (result);
}

double	ft_atof(const char *str)
{
	int		sign;
	double	result;

	if (!str || !valid_number_format(str))
		error_exit("Invalid number format");
	while (is_space(*str))
		str++;
	sign = 1;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	result = parse_integer_part(&str);
	result += parse_decimal_part(&str);
	return (result * sign);
}
