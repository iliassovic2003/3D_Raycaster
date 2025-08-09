#include "Cub3D.h"

void	free_arr(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

static int	count_words(char const *s, char c)
{
	int	i;
	int	k;
	int	cpt;

	i = 0;
	cpt = 0;
	k = 1;
	while (s[i])
	{
		if (s[i] == c)
			k = 1;
		else if (s[i] != c && k == 1)
		{
			cpt++;
			k = 0;
		}
		i++;
	}
	return (cpt);
}

static char	*cl_al_fi(char const *s, char c)
{
	int		i;
	int		cpt;
	char	*p;

	i = 0;
	cpt = 0;
	while (s[i] && s[i] == c)
		i++;
	while (s[i + cpt] && s[i + cpt] != c)
		cpt++;
	p = malloc((cpt + 1) * sizeof(char));
	if (p)
	{
		ft_strlcpy(p, s + i, cpt + 1);
		p[cpt] = '\0';
	}
	return (p);
}

static char	**sub_split(char **strs, char c, char const *s)
{
	int	i;

	i = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
		{
			strs[i] = cl_al_fi(s, c);
			if (!strs[i])
			{
				free_arr(strs);
				return (NULL);
			}
			i++;
			while (*s && *s != c)
				s++;
		}
	}
	strs[i] = NULL;
	return (strs);
}

char	**ft_split(char const *s, char c)
{
	char	**strs;

	if (!s)
		return (NULL);
	strs = malloc((count_words(s, c) + 1) * sizeof(char *));
	if (!strs)
		return (NULL);
	strs = sub_split(strs, c, s);
	return (strs);
}
