/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_move.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-moni <mle-moni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 09:26:00 by mle-moni          #+#    #+#             */
/*   Updated: 2019/11/27 13:50:58 by mle-moni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus/main.h"

void		jump(t_config *conf)
{
	if (conf->keyboard.jump)
	{
		if (conf->jump < 40)
			conf->jump += 8;
		else
			conf->keyboard.jump = 0;
	}
	else
	{
		if (conf->jump > 0)
			conf->jump -= 8;
	}
}

void		collisions(t_config *conf)
{
	if (conf->map[(int)conf->player.pos_y][(int)conf->player.pos_x] == '3'
	&& !conf->koopa.exist)
	{
		conf->player.bonus = 1;
		conf->map[(int)conf->player.pos_y][(int)conf->player.pos_x] = '0';
	}
	else if (conf->map[(int)conf->player.pos_y][(int)conf->player.pos_x] == '2')
	{
		conf->map[(int)conf->player.pos_y][(int)conf->player.pos_x] = '0';
		conf->player.lives--;
	}
	else if (conf->map[(int)conf->player.pos_y][(int)conf->player.pos_x] == '9')
	{
		conf->win++;
		if (conf->win == 1)
		{
			change_map(conf);
			conf->player.pos_x = 3.0;
			conf->player.pos_y = 13.0;
		}
	}
}
