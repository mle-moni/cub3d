/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-moni <mle-moni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 19:25:22 by mle-moni          #+#    #+#             */
/*   Updated: 2019/11/27 11:14:57 by mle-moni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus/main.h"

void		put_img(t_config *conf, t_img *img, int x, int y)
{
	int index;
	int index2;
	int i;
	int j;

	j = 0;
	while (j < img->h)
	{
		i = 0;
		while (i < img->w)
		{
			index = get_pixel_index(*img, i, j);
			index2 = get_pixel_index(conf->img, x + i, y + j);
			if (img->data[index + 3] != (char)255 && index2 > 0)
			{
				conf->img.data[index2] = img->data[index];
				conf->img.data[index2 + 1] = img->data[index + 1];
				conf->img.data[index2 + 2] = img->data[index + 2];
			}
			i++;
		}
		j++;
	}
}

static void	display_kart(t_config *conf, int k)
{
	int index;
	int index2;
	int i;

	i = 0;
	conf->tj = 0;
	while (conf->tj < 256)
	{
		i = 0;
		while (i < 256)
		{
			index = get_pixel_index(conf->main_sp, i + (k * 256), conf->tj);
			index2 = get_pixel_index(conf->img, conf->res_x / 2 - 128 + i,
			conf->res_y - 256 + conf->tj - conf->jump);
			if (conf->main_sp.data[index + 3] != (char)255)
			{
				conf->img.data[index2] = conf->main_sp.data[index];
				conf->img.data[index2 + 1] = conf->main_sp.data[index + 1];
				conf->img.data[index2 + 2] = conf->main_sp.data[index + 2];
			}
			i++;
		}
		conf->tj++;
	}
}

void		display_hud(t_config *conf)
{
	int	i;

	if (conf->keyboard.left == 1)
		display_kart(conf, 1);
	else if (conf->keyboard.right == 1)
		display_kart(conf, 2);
	else
		display_kart(conf, 0);
	if (conf->player.bonus)
		put_img(conf, &conf->shell, conf->res_x / 5 - 32, conf->res_y - 64);
	i = 0;
	while (i < conf->player.lives)
	{
		put_img(conf, &conf->heart, conf->res_x / 5 + 48 + (70 * i),
		conf->res_y - 64);
		i++;
	}
}
