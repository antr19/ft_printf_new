/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_struct.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarsha <fmarsha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 23:44:11 by fmarsha           #+#    #+#             */
/*   Updated: 2022/01/11 02:53:01 by fmarsha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	init_struct(t_f *st)
{
	st->type = 0;
	st->width = 0;
	st->minus = 0;
	st->zero = 0;
	st->precision = -1;
	st->sharp = 0;
	st->space = 0;
	st->plus = 0;
}

static int	check_type(char c)
{
	int	term1;
	int	term2;
	int	term3;

	term1 = (c == 'c' || c == 's' || c == 'p');
	term2 = (c == 'd' || c == 'i' || c == 'u');
	term3 = (c == 'x' || c == 'X' || c == '%');
	return (term1 || term2 || term3);
}

static const	char	*set_flags(t_f *st, const char *s)
{
	while (1)
	{
		if (*s == '0')
			st->zero = 1;
		else if (*s == '-')
			st->minus = 1;
		else if (*s == '#')
			st->sharp = 1;
		else if (*s == '+')
			st->plus = 1;
		else if (*s == ' ')
			st->space = 1;
		else
			break ;
		s++;
	}
	return (s);
}

static const char	*set_width_and_precision(t_f *st, const char *s)
{
	st->width = ft_atoi(s);
	while (ft_isdigit(*s))
		++s;
	if (*s == '.')
	{
		++s;
		st->precision = ft_atoi(s);
	}
	while (ft_isdigit(*s))
		++s;
	return (s);
}

const char	*get_struct(t_f *st, const char *s)
{
	init_struct(st);
	s = set_flags(st, s);
	s = set_width_and_precision(st, s);
	if (check_type(*s))
		st->type = *s;
	return (s);
}
