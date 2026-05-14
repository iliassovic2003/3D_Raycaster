/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izahr <izahr@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 02:23:32 by izahr             #+#    #+#             */
/*   Updated: 2025/08/24 02:23:33 by izahr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3D.h"

static char	*read_bytes(char *line, int fd)
{
	char	*buffer;
	ssize_t	size_bytes;

	buffer = malloc((size_t)BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	size_bytes = 1;
	while (!ft_strchr(line, '\n') && size_bytes > 0)
	{
		size_bytes = read(fd, buffer, BUFFER_SIZE);
		if (size_bytes == -1)
		{
			free(buffer);
			free(line);
			return (NULL);
		}
		buffer[size_bytes] = '\0';
		line = ft_strjoin(line, buffer);
	}
	free(buffer);
	return (line);
}

static char	*getting_line(char *line)
{
	char	*temp;
	int		n;
	int		i;

	n = 0;
	if (!line[0])
		return (NULL);
	while (line[n])
	{
		if (line[n] == '\n')
			break ;
		n++;
	}
	if (line[n] == '\n')
		n++;
	temp = malloc(n + 1);
	if (!temp)
		return (NULL);
	i = -1;
	while (i++ < n)
		temp[i] = line[i];
	temp[n] = '\0';
	return (temp);
}

static char	*remod_line(char *line, char *new_line)
{
	char	*t;
	int		i;
	int		j;

	if (!new_line)
	{
		free(line);
		return (NULL);
	}
	i = ft_strlen(line) - ft_strlen(new_line);
	t = malloc(i + 1);
	if (!t)
		return (NULL);
	j = 0;
	while (j < i)
	{
		t[j] = line[j + ft_strlen(new_line)];
		j++;
	}
	t[j] = '\0';
	free(line);
	return (t);
}

char	*get_next_line(int fd, int k)
{
	static char	*line;
	char		*new_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (k == -1)
	{
		free(line);
		line = NULL;
		return (NULL);
	}
	line = read_bytes(line, fd);
	if (!line)
		return (NULL);
	new_line = getting_line(line);
	line = remod_line(line, new_line);
	return (new_line);
}
