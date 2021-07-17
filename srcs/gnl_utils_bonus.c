/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_utils_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhamel <fhamel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 20:01:23 by fhamel            #+#    #+#             */
/*   Updated: 2021/07/17 12:24:59 by fhamel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gnl_bonus.h"

void	ft_fill(char *dst, const char *src, char lim)
{
	int	i;

	i = 0;
	while (src[i] && src[i] != lim)
	{
		dst[i] = src[i];
		i++;
	}
	if (lim == '\n')
	{
		dst[i] = '\n';
		dst[i + 1] = '\0';
	}
	else
		dst[i] = '\0';
}

int	ft_concat(char **line, char *buf, char lim)
{
	char	*new_line;
	int		len_line;
	int		len_buf;

	len_line = 0;
	len_buf = 0;
	if (*line)
		while ((*line)[len_line])
			len_line++;
	while (buf[len_buf] && buf[len_buf] != lim)
		len_buf++;
	new_line = malloc(sizeof(char) * (len_line + len_buf + 1));
	if (!new_line)
	{
		free(*line);
		*line = NULL;
		return (RETURN_LINE);
	}
	if (*line)
		ft_fill(new_line, *line, lim);
	ft_fill(&new_line[len_line], buf, lim);
	free(*line);
	*line = new_line;
	return (CONCAT_DONE);
}

char	*new_surplus(char *surplus)
{
	char	*new_surp;
	int		i;

	i = 0;
	while (surplus[i])
		i++;
	new_surp = malloc(sizeof(char) * (i + 1));
	if (!new_surp)
		return (NULL);
	ft_fill(new_surp, surplus, '\0');
	return (new_surp);
}
