/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhamel <fhamel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 18:21:17 by fhamel            #+#    #+#             */
/*   Updated: 2021/07/14 19:06:15 by fhamel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (-1);
	while (s1[i] && s2[i] && (s1[i] - s2[i] == 0))
		i++;
	return (s1[i] - s2[i]);
}

void	ft_free(void **ptr)
{
	free(*ptr);
	*ptr = NULL;
}

void	ft_exit(const char *str_error)
{
	int	errno;

	perror(str_error);
	exit(errno);
}

void	*alloc(size_t size, size_t len)
{
	void	*alloc;

	alloc = malloc(size * len);
	if (!alloc)
		ft_exit(NULL);
	return (alloc);
}
