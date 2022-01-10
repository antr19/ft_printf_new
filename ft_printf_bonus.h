/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarsha <fmarsha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 23:29:50 by fmarsha           #+#    #+#             */
/*   Updated: 2022/01/11 00:11:17 by fmarsha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <string.h>

typedef struct s_flags
{
	char	type;
	int		width;
	int		minus;
	int		zero;
	int		precision;
	int		sharp;
	int		space;
	int		plus;
}	t_f;

void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);
void		ft_putnbr_fd(long long int n, int fd);
int			ft_atoi(const char *str);
int			ft_isdigit(int c);
size_t		ft_strlen(const char *s);
void		ft_putnstr_fd(char *s, int n, int fd);
void		ft_puthex_fd(long long int n, int fd, int shift);
int			ft_max(int a, int b);
const char	*get_struct(t_f *st, const char *s);
void		print_sym_n(char c, int n);
int			print_str(t_f *st, char *s);
int			print_int(t_f *st, long long int n);
int			print_hex(t_f *st, unsigned long int n);
int			ft_printf(const char *s, ...);
#endif