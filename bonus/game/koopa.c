/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   koopa.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-moni <mle-moni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 17:25:14 by mle-moni          #+#    #+#             */
/*   Updated: 2019/11/27 10:51:58 by mle-moni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus/main.h"

static void	koopa_end(t_config *conf)
{
	conf->koopa.exist = 0;
}

static void	koopa_collisions(t_config *conf)
{
	if (conf->koopa.x < 1 || conf->koopa.y < 1 ||
	conf->koopa.x > conf->map_w - 1 || conf->koopa.y > conf->map_h - 1)
		return (koopa_end(conf));
	if (conf->map[(int)conf->koopa.y][(int)conf->koopa.x] == '2')
	{
		conf->map[(int)conf->koopa.y][(int)conf->koopa.x] = '0';
		return (koopa_end(conf));
	}
	conf->map[(int)conf->koopa.y][(int)conf->koopa.x] = '3';
}

void		koopa_forward(t_config *conf)
{
	int	index_x1;
	int	index_y1;
	int	index_x2;
	int	index_y2;

	conf->map[(int)conf->koopa.y][(int)conf->koopa.x] = '0';
	index_y1 = (int)(conf->koopa.y);
	index_x1 = (int)(conf->koopa.x + conf->koopa.dir_x * MV_SPD *
	conf->dt);
	index_y2 = (int)(conf->koopa.y + conf->koopa.dir_y * MV_SPD *
	conf->dt);
	index_x2 = (int)(conf->koopa.x);
	if (conf->map[index_y1][index_x1] == '1')
		return (koopa_end(conf));
	if (conf->map[index_y2][index_x2] == '1')
		return (koopa_end(conf));
	conf->koopa.x += conf->koopa.dir_x * MV_SPD * conf->dt;
	conf->koopa.y += conf->koopa.dir_y * MV_SPD * conf->dt;
	koopa_collisions(conf);
}

void		koopa_attack(t_config *conf)
{
	if (!conf->koopa.exist)
	{
		conf->koopa.exist = 1;
		conf->koopa.x = conf->player.pos_x;
		conf->koopa.y = conf->player.pos_y;
		conf->koopa.dir_x = conf->player.dir_x * 1.5;
		conf->koopa.dir_y = conf->player.dir_y * 1.5;
		conf->player.bonus = 0;
	}
}
