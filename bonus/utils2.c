/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-moni <mle-moni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 16:27:38 by mle-moni          #+#    #+#             */
/*   Updated: 2019/11/23 16:09:29 by mle-moni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus/main.h"

int			put_error(t_config *config)
{
	put_str_fd("Error\n", 2);
	if (config->error_msg)
		put_str_fd(config->error_msg, 2);
	else
		put_str_fd("malloc seems to fail", 2);
	write(1, "\n", 1);
	free_config(config);
	exit(-1);
}

int			free_split(char **strs)
{
	int i;

	i = 0;
	if (strs)
	{
		while (strs[i])
		{
			free(strs[i]);
			i++;
		}
		free(strs);
	}
	return (1);
}

double		get_rot(char c)
{
	if (c == 'E')
		return (0.0);
	else if (c == 'N')
		return (M_PI_2);
	else if (c == 'W')
		return (M_PI);
	else
		return (M_PI_2 + M_PI);
}

void		set_color(t_color *color, int r, int g, int b)
{
	color->r = r;
	color->g = g;
	color->b = b;
}

void		fill_space(t_config *conf, int y, int h, t_color color)
{
	int c;

	c = y;
	while (c < h)
	{
		trait(conf, c, conf->res_x, color);
		c++;
	}
}
