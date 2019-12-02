/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-moni <mle-moni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 16:24:04 by mle-moni          #+#    #+#             */
/*   Updated: 2019/11/23 16:09:29 by mle-moni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus/main.h"

int			get_pixel_index(t_img img, int x, int y)
{
	int index;

	index = y * img.size_line + x * 4;
	if (index >= img.max || index < 0)
	{
		return (-1);
	}
	return (index);
}

void		slice(t_config *conf, int x, int y, int w)
{
	int		index;
	int		j;
	t_color	color;

	if (w > TILE_SIZE / 2)
		color = conf->black;
	else
		color = conf->tmp_c;
	j = y;
	while (j < w + y)
	{
		index = get_pixel_index(conf->img, x, j);
		(conf->img.data)[index] = color.b;
		(conf->img.data)[index + 1] = color.g;
		(conf->img.data)[index + 2] = color.r;
		j++;
	}
}

void		trait(t_config *conf, int y, int w, t_color color)
{
	int index;
	int i;

	i = 0;
	while (i < w)
	{
		index = get_pixel_index(conf->img, i, y);
		(conf->img.data)[index] = color.b;
		(conf->img.data)[index + 1] = color.g;
		(conf->img.data)[index + 2] = color.r;
		i++;
	}
}

void		carre(t_config *conf, int x, int y, int w)
{
	int i;

	i = x;
	while (i < w + x)
	{
		slice(conf, i, y, w);
		i++;
	}
}

void		draw_map(t_config *cf)
{
	cf->tj = 0;
	cf->ta = TILE_SIZE / 2;
	while (cf->tj < cf->map_h)
	{
		cf->ti = 0;
		while (cf->ti < cf->map_w)
		{
			if (cf->map[cf->tj][cf->ti] == '2')
			{
				cf->tmp_c = cf->green;
				carre(cf, cf->ti * cf->ta, cf->tj * cf->ta, cf->ta);
			}
			else
			{
				cf->tmp_c = cf->map[cf->tj][cf->ti] == '1' ? cf->red : cf->wt;
				carre(cf, cf->ti * cf->ta, cf->tj * cf->ta, cf->ta);
			}
			slice(cf, cf->ti * cf->ta, 0, cf->ta * cf->map_h);
			cf->ti++;
		}
		trait(cf, cf->tj * cf->ta, cf->ta * cf->map_w, cf->black);
		cf->tj++;
	}
	cf->tmp_c = cf->green;
	carre(cf, cf->player.pos_x * cf->ta - 2, cf->player.pos_y * cf->ta - 2, 4);
}
