/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarsha <fmarsha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 00:02:44 by fmarsha           #+#    #+#             */
/*   Updated: 2022/01/11 00:02:49 by fmarsha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_str(t_f *st, char *s)
{
	int	len;

	if (!s)
		return (print_str(st, "(null)"));
	len = ft_strlen(s);
	if (st->precision >= 0 && st->precision < len)
		len = st->precision;
	if (st->minus == 1)
		ft_putnstr_fd(s, len, 1);
	print_sym_n(' ', st->width - len);
	if (st->minus == 0)
		ft_putnstr_fd(s, len, 1);
	if (st->width > len)
		return (st->width);
	else
		return (len);
}
