/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarsha <fmarsha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 23:26:44 by fmarsha           #+#    #+#             */
/*   Updated: 2022/01/10 23:38:19 by fmarsha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_isspace(char c)
{
	int	term1;
	int	term2;

	term1 = (c == '\t' || c == '\n' || c == '\v');
	term2 = (c == '\f' || c == '\r' || c == ' ');
	return (term1 || term2);
}

int	ft_atoi(const char *str)
{
	int	num;
	int	sign;

	num = 0;
	sign = -1;
	while (ft_isspace(*str))
		str++;
	if (*str == '-')
		str++;
	else if (*str == '+')
	{
		str++;
		sign = 1;
	}
	else
		sign = 1;
	while (*str && ft_isdigit(*str))
	{
		num = num * 10 + (*str - '0');
		str++;
	}
	return (num * sign);
}
