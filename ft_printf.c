/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarsha <fmarsha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 21:33:17 by fmarsha           #+#    #+#             */
/*   Updated: 2021/11/10 23:33:37 by fmarsha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <string.h>
#include <stdio.h> // TODO
// #include "libftprintf.h"

void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putnbr_fd(long long int n, int fd);
int		ft_atoi(const char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_isdigit(int c);
size_t	ft_strlen(const char *s);
void	ft_putnstr_fd(char *s, int n, int fd);
void 	ft_puthex_fd(long long int n, int fd, int shift);

int ft_max(int a, int b)
{
	if (a > b)
		return a;
	return b;
}

typedef struct s_flags
{
	char 	type;
	int		width;
	int		minus;
	int		zero;
	int		precision;
	int		sharp;
	int		space;
	int		plus;
}	t_f;

void init_struct(t_f *st)
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

int check_type(char c)
{
	int	term1;
	int	term2;
	int	term3;

	term1 = c == 'c' || c == 's' || c == 'p';
	term2 = c == 'd' || c == 'i' || c == 'u';
	term3 = c == 'x' || c == 'X';
	return (term1 || term2 || term3);
}

const char *set_flags(t_f *st, const char *s)
{
	while(1)
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
			break;
		s++;
	}
	return s;
}

const char *set_width_and_precision(t_f *st, const char *s)
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
	return s;
}

const char *get_struct(t_f *st, const char *s)
{
	init_struct(st);
	s = set_flags(st, s);
	s = set_width_and_precision(st, s);
	if (check_type(*s))
		st->type = *s;
	return s;
}

void print_sym_n(char c, int n)
{
	int	i;

	i = 0;
	while(i++ < n)
		ft_putchar_fd(c, 1);
}

int print_char(t_f *st, char c)
{
	if (st->minus == 1)
		ft_putchar_fd(c, 1);
	print_sym_n(' ', st->width - 1);
	if (st->minus == 0)
		ft_putchar_fd(c, 1);
	if (st->width)
		return st->width;
	else
		return 1;
}

int print_str(t_f *st, char *s)
{
	int	len;

	if (!s && st->precision < 6 && st->precision >= 0) // TODO
		return print_str(st, "");
	else if (!s)
		return print_str(st, "(null)");
	len = ft_strlen(s);
	if (st->precision >= 0 && st->precision < len)
		len = st->precision;
	if (st->minus == 1)
		ft_putnstr_fd(s, len, 1);
	print_sym_n(' ', st->width - len);
	if (st->minus == 0)
		ft_putnstr_fd(s, len, 1);
	if (st->width > len)
		return st->width;
	else
		return len;
}

int ft_nbrlen(long long int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return 1;
	if (n < 0)
		i = 1;
	while (n)
	{
		n /= 10;
		i++;
	}
	return i;
}

void print_nbr(t_f *st, long long int n, int zero, int len)
{
	if (st->plus && n >= 0)
		ft_putchar_fd('+', 1);
	if (zero)
	{
		if (n < 0)
		{
			ft_putchar_fd('-', 1);
			n = -n;
		}
		if (st->precision < len)
			print_sym_n('0', st->width - ft_max(len, st->precision));
		else
			print_sym_n(' ', st->width - ft_max(len, st->precision));
	}
	else if (n < 0)
		ft_putchar_fd('-', 1);
	print_sym_n('0', st->precision - len + (n < 0));
	if (n > 0)
		ft_putnbr_fd(n, 1);
	else
		ft_putnbr_fd(-n, 1);
}

int print_int(t_f *st, long long int n)
{
	int	len;

	len = ft_nbrlen(n);
	if (n == 0 && st->precision == 0)
		return print_str(st, "");
	if (st->space && st->width - len < 2 && (n >= 0))
		st->width = len + 1;
	else if (st->minus == 1)
	{
		print_nbr(st, n, 0, len);
		st->zero = 0;
	}
	if (st->zero)
		print_nbr(st, n, 1, len);
	else
	{
		print_sym_n(' ', st->width - ft_max(len, st->precision + (n < 0)) - st->plus);
		if (st->minus == 0)
			print_nbr(st, n, 0, len);
	}
	if (st->width > ft_max(len + st->plus*(n >= 0), st->precision + (n < 0)))
		return st->width + (n < 0);
	else
		return ft_max(len + st->plus*(n >= 0), st->precision + (n < 0));
}

int ft_hexlen(unsigned long long int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return 1;
	while (n)
	{
		n /= 16;
		i++;
	}
	return i;
}

void print_hexnbr(t_f *st, long long int n, int zero, int len)
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
		if (st->precision < len)
			print_sym_n('0', st->width - ft_max(len + 2*st->sharp*(n >= 0), st->precision));
		else
			print_sym_n(' ', st->width - ft_max(len + 2*st->sharp*(n >= 0), st->precision));
	}
	print_sym_n('0', st->precision - len);
	if (st->type == 'X')
		ft_puthex_fd(n, 1, 65);
	else
		ft_puthex_fd(n, 1, 97);
}

int print_hex(t_f *st, unsigned long int n)
{
	int	len;

	len = ft_hexlen(n);
	if (n == 0 && st->precision == 0)
		return print_str(st, "");
	if (st->sharp && n > 0)
		len = len + 2;
	if (st->space && st->width - len < 2)
		st->width = len + 1 + 2*st->sharp*(n > 0);
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
	if (st->width > ft_max(len, st->precision))
		return st->width - 2*st->sharp*(n > 0)*(st->space);
	else
		return ft_max(len, st->precision);
}

int print_point(t_f *st, unsigned long int p)
{
	st->sharp = 1;
	if (p)
		return print_hex(st, p);
	else
		return print_str(st, "(nil)");
}

int ft_handler(const char **s, va_list *argptr)
{
	t_f	flags;

	*s = get_struct(&flags, *s);
	if (flags.type == 'c')
		return print_char(&flags, va_arg(*argptr, int));
	else if (flags.type == 's')
		return print_str(&flags, va_arg(*argptr, char *));
	else if (flags.type == 'p')
		return print_point(&flags, va_arg(*argptr, unsigned long int));
	else if (flags.type == 'd' || flags.type == 'i')
		return print_int(&flags, va_arg(*argptr, int));
	else if (flags.type == 'u')
		return print_int(&flags, va_arg(*argptr, unsigned int));
	else if (flags.type == 'x' || flags.type == 'X')
		return print_hex(&flags, va_arg(*argptr, unsigned int));
	return 0;
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
		else if (*(++s) == '%')
			ft_putchar_fd(*s, 1);
		else
			len += ft_handler(&s, &argptr) - 1 ;
		++s;
		++len;
	}
	va_end(argptr);
	return (len);
}

// int main()
// {
// 	// char s[] = "%p|\n";
// 	char s[] = "%.1s|\n";
// 	int dec = 0;
// 	// void *p;
// 	int a, b;
// 	printf("0123456789012345678901234567891\n");
// 	a = printf(s, dec);
// 	b = ft_printf(s, dec);
// 	if (a == b)
// 		printf("return is good\n");
// 	else
// 		printf("orig func returns %d\nyour func returns %d\n", a, b);
	
// 	// printf("%d\n", ft_nbrlen(0));
// 	// ft_printf("% 20.10d\n", 12345);
// 	// ft_printf("%1.2s\n", "123");
// 	// ft_printf("121%-10c3123blabla%sbla\n", 'a', "(abra");
// 	// printf("%-20.2s\n", "-123");
// 	// printf("%-20.12d\n", 123456789);
// 	// printf("% -4d\n", 123);
// 	// printf("%sb", "abvgd");
// }
