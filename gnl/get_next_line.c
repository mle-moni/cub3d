/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-moni <mle-moni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 12:26:35 by mle-moni          #+#    #+#             */
/*   Updated: 2019/10/23 11:46:32 by mle-moni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gnl/get_next_line.h"

static void		*my_memset(void *s, size_t n, int fd, int *dont_stop)
{
	size_t	i;
	char	*str;

	str = s;
	i = 0;
	while (i < n)
	{
		str[i] = 0;
		i++;
	}
	*dont_stop = read(fd, s, BUFFER_SIZE);
	return (s);
}

static int		add_to_total(char **total, char *buff, int len)
{
	char	*str;
	int		i;
	int		j;

	j = 0;
	if (!(str = malloc(length(*total) + len + 1)))
		return (free_all(str, NULL, NULL));
	i = 0;
	while ((*total)[i] > 0)
	{
		str[i] = (*total)[i];
		i++;
	}
	while (buff[j] > 0 && j < len)
	{
		str[i + j] = buff[j];
		j++;
	}
	str[i + j] = '\0';
	free(*total);
	*total = str;
	return (0);
}

void			set_vars_xd(int *dont_stop, int *i, int *len)
{
	*dont_stop = 42;
	*i = 0;
	*len = 0;
}

static int		process(char **total, int fd, char **line,
char buffer[BUFFER_SIZE + 1])
{
	int			i;
	int			dont_stop;
	int			len;
	char		*working_line;

	set_vars_xd(&dont_stop, &i, &len);
	while (dont_stop > 0)
	{
		if ((len = has_char(*total, '\n')) >= 0)
		{
			if ((cpy_answ(&working_line, total, len)) == -1)
				return (free_all(working_line, *line, NULL));
			*line = working_line;
			return (1);
		}
		my_memset(buffer, BUFFER_SIZE, fd, &dont_stop);
		if (dont_stop > 0)
		{
			if (add_to_total(total, buffer, dont_stop) == -1)
				return (-1);
		}
		else
			return (end_it(line, total, dont_stop));
	}
	return (dont_stop);
}

int				get_next_line(int fd, char **line)
{
	char		buffer[BUFFER_SIZE + 1];
	static char	*total = NULL;
	int			state;

	if (!total)
	{
		total = malloc(1);
		if (!total)
			return (free_all(total, NULL, NULL));
		total[0] = '\0';
	}
	if (fd == -1)
		return (free_all(total, NULL, NULL));
	state = process(&total, fd, line, buffer);
	if (state == -1)
	{
		*line = NULL;
		free(total);
		total = NULL;
	}
	return (state);
}
