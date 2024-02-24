/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uahmed <uahmed@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 17:48:53 by uahmed            #+#    #+#             */
/*   Updated: 2023/10/31 22:27:09 by uahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	ft_isspace(const char *str)
{
	if (*str == '\t' || *str == ' ' || *str == '\v' || *str == '\f'
		|| *str == '\n' || *str == '\r')
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int			sign;
	long long	res;

	sign = 1;
	res = 0;
	while (ft_isspace(str))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*(str++) == '-')
			sign *= -1;
	}
	if (*str == '-' || *str == '+')
		return (0);
	while (*str >= '0' && *str <= '9')
	{
		if (res * 10 + (*str - '0') < res)
		{
			if (sign == -1)
				return (0);
			return (-1);
		}
		res = res * 10 + (*(str++) - '0');
	}
	return (res * sign);
}
