/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-moni <mle-moni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 16:34:29 by mle-moni          #+#    #+#             */
/*   Updated: 2019/11/22 17:05:34 by mle-moni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

void	put_str_fd(const char *str, int fd)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	write(fd, str, i);
}

int		is_from_str(char c, char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int		ft_atoi(const char *str, int *i)
{
	int ret;

	ret = 0;
	while (is_from_str(str[*i], " "))
		(*i)++;
	while (is_from_str(str[*i], "0123456789-"))
	{
		if (str[*i] == '-')
			return (-1);
		ret = ret * 10 + (str[*i] - '0');
		(*i)++;
	}
	return (ret);
}

int		str_len(const char *str)
{
	int i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

char	*ft_str_cat(const char *str, const char *str2)
{
	char	*new_str;
	int		i;
	int		j;

	i = str_len(str) + str_len(str2);
	if (!(new_str = malloc(i + 1)))
		return (NULL);
	i = 0;
	while (str && str[i])
	{
		new_str[i] = str[i];
		i++;
	}
	j = 0;
	while (str2 && str2[j])
	{
		new_str[i + j] = str2[j];
		j++;
	}
	new_str[i + j] = '\0';
	return (new_str);
}
