#include "Cub3D.h"

static unsigned long long	ft_helper(const char *str, int *i,
		unsigned long long *number, int *sign)
{
	while (str[*i] && str[*i] >= '0' && str[*i] <= '9')
	{
		*number = (*number * 10) + (str[(*i)++] - '0');
		if (*number >= LONG_MAX && *sign == 1)
			return (-1);
		if (*number >= LONG_MAX && *sign == -1)
			return (0);
	}
	return (*number);
}

int	ft_atoi(const char *str)
{
	unsigned long long	number;
	int					sign;
	int					i;

	sign = 1;
	number = 0;
	i = 0;
	if (!str)
		return (0);
	while (str[i] && (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
			|| str[i] == '\r' || str[i] == '\v' || str[i] == '\f'))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	number = ft_helper(str, &i, &number, &sign);
	free((void *)str);
	if ((int)number == -1 || (int)number == 0)
		return ((int)number);
	return (sign * number);
}

void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*ss;

	if (n == 0)
		return ;
	ss = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		ss[i] = 0;
		i++;
	}
}

static int	is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r');
}

char	*ft_strtrim(char *s)
{
	size_t	start;
	size_t	end;
	size_t	len;
	char	*trimmed;

	if (!s)
		return (NULL);
	start = 0;
	while (s[start] && is_whitespace(s[start]))
		start++;
	end = ft_strlen(s);
	while (end > start && is_whitespace(s[end - 1]))
		end--;
	len = end - start;
	trimmed = (char *)malloc(len + 1);
	if (!trimmed)
		return (NULL);
	ft_strlcpy(trimmed, s + start, len + 1);
	return (trimmed);
}
