/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-moni <mle-moni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 12:26:17 by mle-moni          #+#    #+#             */
/*   Updated: 2019/10/23 11:46:55 by mle-moni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gnl/get_next_line.h"

int			has_char(char *buffer, char c)
{
	int i;

	i = 0;
	while (buffer[i])
	{
		if (buffer[i] == c)
			return (i);
		i++;
	}
	return (-42);
}

int			length(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int			cpy_answ(char **answ, char **total, int index)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = length(*total);
	str = malloc(j + 1 - index);
	if (!str || !(*answ = malloc(index + 1)))
		return (free_all(str, *answ, NULL));
	while (i < index)
	{
		(*answ)[i] = (*total)[i];
		i++;
	}
	(*answ)[i] = '\0';
	j = 0;
	i++;
	while ((*total)[i + j] > 0)
	{
		str[j] = (*total)[i + j];
		j++;
	}
	str[j] = '\0';
	free(*total);
	return (!(*total = str));
}

int			free_all(char *pt1, char *pt2, char *pt3)
{
	free(pt1);
	free(pt2);
	free(pt3);
	return (-1);
}

int			end_it(char **line, char **total, int dont_stop)
{
	*line = *total;
	*total = NULL;
	return (dont_stop);
}
