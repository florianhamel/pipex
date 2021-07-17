/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhamel <fhamel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 18:21:17 by fhamel            #+#    #+#             */
/*   Updated: 2021/07/17 18:38:42 by fhamel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft.h"

void	*alloc(size_t size, size_t len)
{
	void	*alloc;

	alloc = malloc(size * len);
	if (!alloc)
		ft_exit(NULL);
	return (alloc);
}

int	str_is_ws(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_is_ws(str[i]))
			return (0);
		i++;
	}
	return (1);
}
