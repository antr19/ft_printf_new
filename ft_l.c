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

void ft_puthex_fd(unsigned long long int n, int fd, int shift)
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

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

static int	ft_isspace(char c)
{
	int	term1;
	int	term2;

	term1 = c == '\t' || c == '\n' || c == '\v';
	term2 = c == '\f' || c == '\r' || c == ' ';
	return (term1 || term2);
}

int	ft_atoi(const char *str)
{
	int	num;
	int	sign;

	num = 0;
	sign = -1;
	while (ft_isspace(*str))
		str++;
	if (*str == '-')
		str++;
	else if (*str == '+')
	{
		str++;
		sign = 1;
	}
	else
		sign = 1;
	while (*str && ft_isdigit(*str))
	{
		num = num * 10 + (*str - '0');
		str++;
	}
	return (num * sign);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	while (*s1 == *s2 && s1 && s2 && *s1 && *s2 && n--)
	{
		s1++;
		s2++;
	}
	if (n == 0)
		return (0);
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}