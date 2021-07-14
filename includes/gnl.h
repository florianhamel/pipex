/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhamel <fhamel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 13:30:48 by fhamel            #+#    #+#             */
/*   Updated: 2021/07/14 16:51:38 by fhamel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GNL_H
# define GNL_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
# endif

# define ERROR -1
# define RETURN_LINE 0
# define LINE_NOT_FULL 1
# define CONCAT_DONE 1

# include <unistd.h>
# include <stdlib.h>

/*
** gnl.c
*/

void	nl_surplus(char **line, char **surplus, int pos);
int		ft_surplus(char **line, char **surplus);
void	nl_buf(char **line, char *buf, char **surplus, int pos);
int		ft_buf(char **line, char *buf, char **surplus);
char	*get_next_line(int fd);

/*
** gnl_utils.c
*/
char	*new_surplus(char *surplus);
void	ft_fill(char *dst, const char *src, char lim);
int		ft_concat(char **line, char *buf, char lim);

#endif