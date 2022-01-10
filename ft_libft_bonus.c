/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_libft.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarsha <fmarsha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 23:34:32 by fmarsha           #+#    #+#             */
/*   Updated: 2022/01/10 23:34:32 by fmarsha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <string.h>

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	write(fd, s, ft_strlen(s));
}

void	ft_putnstr_fd(char *s, int n, int fd)
{
	int	len;

	len = ft_strlen(s);
	if (!s)
		return ;
	else if (n < len)
		write(fd, s, n);
	else
		write(fd, s, len);
}

void	ft_puthex_fd(unsigned long long int n, int fd, int shift)
{
	if (n / 16 == 0)
	{
		if (n % 16 < 10)
			ft_putchar_fd('0' + n % 16, fd);
		else
			ft_putchar_fd(shift + n % 16 - 10, fd);
	}
	else
	{
		ft_puthex_fd(n / 16, fd, shift);
		if (n % 16 < 10)
			ft_putchar_fd('0' + n % 16, fd);
		else
			ft_putchar_fd(shift + n % 16 - 10, fd);
	}
}
