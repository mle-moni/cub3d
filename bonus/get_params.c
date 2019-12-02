/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_params.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-moni <mle-moni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 09:10:12 by mle-moni          #+#    #+#             */
/*   Updated: 2019/11/23 16:09:29 by mle-moni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus/main.h"

int		get_res(char **line, t_config *conf)
{
	int		i;
	char	*err;

	i = 1;
	conf->res_x = ft_atoi((*line), &i);
	conf->res_y = ft_atoi((*line), &i);
	if (conf->res_x == 0 || conf->res_y == 0)
	{
		err = ft_str_cat("Wrong resolution, expected 'R res_x res_y' but got: ",
		(*line));
		conf->error_msg = err;
		free((*line));
		(*line) = NULL;
		return (-1);
	}
	if (conf->res_x > 2560)
		conf->res_x = 2560;
	if (conf->res_y > 1580)
		conf->res_y = 1580;
	free((*line));
	(*line) = NULL;
	return (1);
}

int		get_path(char **line, t_config *conf, int pos)
{
	int i;

	i = 0;
	while (is_from_str((*line)[i], " ASONWEF"))
		i++;
	if (pos == 4)
		conf->text_s.path = ft_str_cat((*line) + i, "");
	else
		conf->text_array[pos].path = ft_str_cat((*line) + i, "");
	return (1);
}

int		check_color(t_color color)
{
	if (color.r < 0 || color.r > 255)
		return (0);
	if (color.g < 0 || color.g > 255)
		return (0);
	if (color.b < 0 || color.b > 255)
		return (0);
	return (1);
}

int		check_err(char **line, t_config *conf, int i)
{
	char *err;

	if (i == -1)
	{
		err = ft_str_cat("Expected color RBG with range 0 -> 255 but got: ",
		(*line));
		conf->error_msg = err;
		free((*line));
		(*line) = NULL;
		return (-1);
	}
	free((*line));
	(*line) = NULL;
	return (1);
}

int		get_color(char **line, t_config *conf, char id)
{
	int i;

	i = 1;
	(void)id;
	if (id == 'C')
	{
		conf->color_c.r = ft_atoi((*line), &i);
		i++;
		conf->color_c.g = ft_atoi((*line), &i);
		i++;
		conf->color_c.b = ft_atoi((*line), &i);
		if (!check_color(conf->color_c))
			i = -1;
	}
	else
	{
		conf->color_f.r = ft_atoi((*line), &i);
		i++;
		conf->color_f.g = ft_atoi((*line), &i);
		i++;
		conf->color_f.b = ft_atoi((*line), &i);
		if (!check_color(conf->color_f))
			i = -1;
	}
	return (check_err(line, conf, i));
}
