/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarsha <fmarsha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 21:33:17 by fmarsha           #+#    #+#             */
/*   Updated: 2022/01/11 02:54:39 by fmarsha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "ft_printf.h"

int	print_char(t_f *st, char c)
{
	if (st->minus == 1)
		ft_putchar_fd(c, 1);
	print_sym_n(' ', st->width - 1);
	if (st->minus == 0)
		ft_putchar_fd(c, 1);
	if (st->width)
		return (st->width);
	else
		return (1);
}

int	print_point(t_f *st, unsigned long int p)
{
	st->sharp = 1;
	if (p)
		return (print_hex(st, p));
	else
		return (print_str(st, "0x0"));
}

int	ft_handler(const char **s, va_list *argptr)
{
	t_f	flags;

	*s = get_struct(&flags, *s);
	if (flags.type == 'c')
		return (print_char(&flags, va_arg(*argptr, int)));
	else if (flags.type == '%')
		return (print_char(&flags, '%'));
	else if (flags.type == 's')
		return (print_str(&flags, va_arg(*argptr, char *)));
	else if (flags.type == 'p')
		return (print_point(&flags, va_arg(*argptr, unsigned long int)));
	else if (flags.type == 'd' || flags.type == 'i')
		return (print_int(&flags, va_arg(*argptr, int)));
	else if (flags.type == 'u')
		return (print_int(&flags, va_arg(*argptr, unsigned int)));
	else if (flags.type == 'x' || flags.type == 'X')
		return (print_hex(&flags, va_arg(*argptr, unsigned int)));
	return (0);
}

int	ft_printf(const char *s, ...)
{
	va_list	argptr;
	int		len;

	va_start(argptr, s);
	len = 0;
	while (*s)
	{
		if (*s != '%')
			ft_putchar_fd(*s, 1);
		else
			len += ft_handler(&s, &argptr) - 1 ;
		++s;
		++len;
	}
	va_end(argptr);
	return (len);
}
