/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 22:08:21 by myuen             #+#    #+#             */
/*   Updated: 2025/02/28 22:08:27 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static long	ft_parse_str(const char **str, int base, int sign)
{
	long	result;
	int		digit;

	result = 0;
	digit = ft_char_to_digit(**str, base);
	while (digit != -1)
	{
		(*str)++;
		if (result > (LONG_MAX - digit) / base)
		{
			if (sign == 1)
				return (LONG_MAX);
			else
				return (LONG_MIN);
		}
		result = result * base + digit;
		digit = ft_char_to_digit(**str, base);
	}
	if (result == LONG_MAX && sign == -1)
		return (0);
	return (result * sign);
}

long	ft_strtol(const char *str, char **endptr, int base)
{
	int		sign;
	long	result;

	while (ft_isspace(*str))
		str++;
	sign = ft_set_sign(&str);
	if (*str == '\0')
	{
		if (endptr)
			*endptr = (char *)--str;
		return (0);
	}
	str = ft_check_base(str, &base);
	if (base == 0)
	{
		if (endptr)
			*endptr = (char *) str;
		return (0);
	}
	result = ft_parse_str(&str, base, sign);
	if (endptr)
		*endptr = (char *)str;
	return (result);
}

int	ft_isvalid_integer(const char *str, int base)
{
	char	*endptr;
	long	result;

	if (!str || !str[0])
		return (0);
	result = ft_strtol(str, &endptr, base);
	if (*endptr != '\0')
		return (0);
	if (result > INT_MAX || result < INT_MIN)
		return (0);
	return (1);
}
