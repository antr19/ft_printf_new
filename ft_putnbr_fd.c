/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarsha <fmarsha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 23:23:55 by fmarsha           #+#    #+#             */
/*   Updated: 2022/01/10 23:24:37 by fmarsha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	loop(long long int n, int fd)
{
	if (n / 10 == 0)
		ft_putchar_fd('0' - n, fd);
	else
	{
		loop(n / 10, fd);
		ft_putchar_fd('0' - n % 10, fd);
	}
}

void	ft_putnbr_fd(long long int n, int fd)
{
	if (n >= 0)
		loop(-n, fd);
	else
	{
		ft_putchar_fd('-', fd);
		loop(n, fd);
	}
}
