/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhamel <fhamel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 15:06:48 by fhamel            #+#    #+#             */
/*   Updated: 2021/07/12 15:19:01 by fhamel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
# endif

# include <stdlib.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>

/*
** get_next_line.c
*/
int		rest_mgmt(char **rest, char **line);
int		buff_mgmt(char **rest, char **line, char *buff);
int		get_next_line(int fd, char **line);

/*
** get_next_line_utils.c
*/
void	fill(char *dst, const char *src, char end);
int		concat(char **line, char *buff, char end);
int		only_eof(char **line);

#endif
