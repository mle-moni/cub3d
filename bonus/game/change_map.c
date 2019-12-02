/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-moni <mle-moni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 12:40:07 by mle-moni          #+#    #+#             */
/*   Updated: 2019/11/27 14:49:07 by mle-moni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus/main.h"

static void	reset_map(t_config *conf)
{
	int x;
	int y;

	y = 0;
	while (y < conf->map_h)
	{
		x = 0;
		while (x < conf->map_w)
		{
			if (x != 0 && x != conf->map_w - 1 &&
			y != 0 && y != conf->map_h - 1)
				conf->map[y][x] = '1';
			x++;
		}
		y++;
	}
}

static void	put_line_hori(t_config *conf, int x, int y, int w)
{
	int pos_x;

	pos_x = x;
	while (pos_x < conf->map_w && pos_x < x + w)
	{
		conf->map[y][pos_x] = '0';
		pos_x++;
	}
}

static void	put_line_verti(t_config *conf, int x, int y, int w)
{
	int pos_y;

	pos_y = y;
	while (pos_y < conf->map_h && pos_y < y + w)
	{
		conf->map[pos_y][x] = '0';
		pos_y++;
	}
}

void		change_map(t_config *conf)
{
	reset_map(conf);
	put_line_hori(conf, 2, 3, 17);
	put_line_verti(conf, 1, 3, 17);
	put_line_verti(conf, 2, 3, 17);
	put_line_verti(conf, 3, 3, 17);
	conf->map[16][3] = '3';
	conf->map[3][7] = '2';
	put_line_hori(conf, 18, 5, 6);
	put_line_hori(conf, 18, 6, 6);
	put_line_hori(conf, 18, 7, 6);
	put_line_hori(conf, 18, 8, 6);
	conf->map[7][22] = '9';
}
