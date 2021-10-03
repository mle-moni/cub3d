/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-moni <mle-moni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 12:26:37 by mle-moni          #+#    #+#             */
/*   Updated: 2019/11/13 08:51:52 by mle-moni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 64
# endif

int			get_next_line(int fd, char **line);
int			has_char(char *buffer, char c);
char		*cp_until(char *buffer, int limit, int totalsize);
char		*dup_str(char *str, int size);
int			cpy_answ(char **answ, char **total, int index);
int			length(char *str);
int			free_all(char *pt1, char *pt2, char *pt3);
int			end_it(char **line, char **total, int dont_stop);

#endif
