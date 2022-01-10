/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_int.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarsha <fmarsha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 23:49:36 by fmarsha           #+#    #+#             */
/*   Updated: 2022/01/10 23:57:26 by fmarsha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_nbrlen(long long int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		i = 1;
	while (n)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static void	print_nbr(t_f *st, long long int n, int len)
{
	if (st->plus && n >= 0)
		ft_putchar_fd('+', 1);
	if (n < 0)
		ft_putchar_fd('-', 1);
	print_sym_n('0', st->precision - len + (n < 0));
	if (n > 0)
		ft_putnbr_fd(n, 1);
	else
		ft_putnbr_fd(-n, 1);
}

static int	return_int(t_f *st, int len, long long int n)
{
	if (st->width > ft_max(len + st->plus * (n >= 0), st->precision + (n < 0)))
		return (st->width);
	else
		return (ft_max(len + st->plus * (n >= 0), st->precision + (n < 0)));
}

static int	return_num_space(t_f *st, int len, long long int n)
{
	return (st->width - ft_max(len, st->precision + (n < 0)) - st->plus);
}

int	print_int(t_f *st, long long int n)
{
	int	len;

	len = ft_nbrlen(n);
	if (n == 0 && st->precision == 0)
		return (print_str(st, ""));
	if (st->space && st->width - len < 2 && (n >= 0))
		st->width = len + 1;
	else if (st->minus == 1)
	{
		print_nbr(st, n, len);
		st->zero = 0;
	}
	if (st->zero && (st->precision == -1))
	{
		if (n < 0)
			ft_putchar_fd('-', 1);
		print_sym_n('0', st->width - ft_max(len, st->precision));
		n = (-(n < 0) * 2 + 1) * n;
	}
	else
		print_sym_n(' ', return_num_space(st, len, n));
	if (st->minus == 0)
		print_nbr(st, n, len);
	return (return_int(st, len, n));
}
