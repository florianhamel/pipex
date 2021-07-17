/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhamel <fhamel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 12:57:20 by fhamel            #+#    #+#             */
/*   Updated: 2021/07/17 12:24:53 by fhamel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gnl_bonus.h"

void	nl_surplus(char **line, char **surplus, int pos)
{
	char	*new_surp;

	ft_fill(*line, *surplus, '\n');
	if (!(*surplus)[pos + 1])
	{
		free(*surplus);
		*surplus = NULL;
		return ;
	}
	new_surp = new_surplus(&(*surplus)[pos + 1]);
	free(*surplus);
	*surplus = new_surp;
	if (!(*surplus))
	{
		free(*line);
		*line = NULL;
	}
}

int	ft_surplus(char **line, char **surplus)
{
	int	i;

	i = 0;
	if (!(*surplus))
		return (LINE_NOT_FULL);
	while ((*surplus)[i] && (*surplus)[i] != '\n')
		i++;
	if ((*surplus)[i] == '\n')
	{
		*line = malloc(sizeof(char) * (i + 2));
		nl_surplus(line, surplus, i);
		return (RETURN_LINE);
	}
	*line = malloc(sizeof(char) * (i + 1));
	if (!line)
		return (RETURN_LINE);
	ft_fill(*line, *surplus, '\0');
	free(*surplus);
	*surplus = NULL;
	return (LINE_NOT_FULL);
}

void	nl_buf(char **line, char *buf, char **surplus, int pos)
{
	int	i;

	i = pos + 1;
	if (!buf[i])
		return ;
	while (buf[i])
		i++;
	*surplus = malloc(sizeof(char) * (i + 1));
	if (!(*surplus))
	{
		free(*line);
		*line = NULL;
		return ;
	}
	ft_fill(*surplus, &buf[pos + 1], '\0');
}

int	ft_buf(char **line, char *buf, char **surplus)
{
	int	i;

	i = 0;
	while (buf[i] && buf[i] != '\n')
		i++;
	if (ft_concat(line, buf, buf[i]) == RETURN_LINE)
		return (RETURN_LINE);
	if (buf[i] == '\n')
	{
		nl_buf(line, buf, surplus, i);
		return (RETURN_LINE);
	}
	return (LINE_NOT_FULL);
}

char	*get_next_line(int fd)
{
	static char	*surplus = NULL;
	char		*line;
	char		buf[BUFFER_SIZE + 1];
	int			ret;

	line = NULL;
	if (ft_surplus(&line, &surplus) == RETURN_LINE)
		return (line);
	ret = read(fd, buf, BUFFER_SIZE);
	if (ret == ERROR)
		return (NULL);
	buf[ret] = '\0';
	while (ret)
	{
		ret = ft_buf(&line, buf, &surplus);
		if (ret == RETURN_LINE)
			return (line);
		ret = read(fd, buf, BUFFER_SIZE);
		if (ret == ERROR)
			return (NULL);
		buf[ret] = '\0';
	}
	return (line);
}
