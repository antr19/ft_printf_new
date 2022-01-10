/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarsha <fmarsha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 00:04:48 by fmarsha           #+#    #+#             */
/*   Updated: 2022/01/11 00:11:40 by fmarsha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_hexlen(unsigned long long int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	while (n)
	{
		n /= 16;
		i++;
	}
	return (i);
}

static int	return_hex_space(t_f *st, int len, long long int n)
{
	return (st->width - ft_max(len + 2 * st->sharp * (n >= 0), st->precision));
}

static void	print_hexnbr(t_f *st, long long int n, int zero, int len)
{
	if ((st->sharp && (st->type == 'x') && (n > 0)) || (st->type == 'p'))
		ft_putstr_fd("0x", 1);
	else if (st->sharp && (n > 0))
		ft_putstr_fd("0X", 1);
	if (zero)
	{
		if (n < 0)
		{
			ft_putchar_fd('-', 1);
			n = -n;
		}
		if (st->precision == -1)
			print_sym_n('0', return_hex_space(st, len, n));
		else
			print_sym_n(' ', return_hex_space(st, len, n));
	}
	print_sym_n('0', st->precision - len);
	if (st->type == 'X')
		ft_puthex_fd(n, 1, 65);
	else
		ft_puthex_fd(n, 1, 97);
}

static int	return_hex(t_f *st, int len, long long int n)
{
	if (st->width > ft_max(len, st->precision))
		return (st->width - 2 * st->sharp * (n > 0) * (st->space));
	else
		return (ft_max(len, st->precision));
}

int	print_hex(t_f *st, unsigned long int n)
{
	int	len;

	len = ft_hexlen(n);
	if (n == 0 && st->precision == 0)
		return (print_str(st, ""));
	if (st->sharp && n > 0)
		len = len + 2;
	if (st->space && st->width - len < 2)
		st->width = len + 1 + 2 * st->sharp * (n > 0);
	else if (st->minus == 1)
	{
		print_hexnbr(st, n, 0, len);
		st->zero = 0;
	}
	if (st->zero)
		print_hexnbr(st, n, 1, len);
	else
	{
		print_sym_n(' ', st->width - ft_max(len, st->precision));
		if ((st->minus == 0) || (st->space))
			print_hexnbr(st, n, 0, len);
	}
	return (return_hex(st, len, n));
}
