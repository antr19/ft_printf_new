/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarsha <fmarsha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 23:34:14 by fmarsha           #+#    #+#             */
/*   Updated: 2022/01/11 00:00:29 by fmarsha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

int	ft_max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

void	print_sym_n(char c, int n)
{
	int	i;

	i = 0;
	while (i++ < n)
		ft_putchar_fd(c, 1);
}
