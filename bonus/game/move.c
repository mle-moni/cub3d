/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-moni <mle-moni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 12:46:41 by mle-moni          #+#    #+#             */
/*   Updated: 2019/11/27 10:54:13 by mle-moni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus/main.h"

static void	move_up(t_config *conf)
{
	int	index_x1;
	int	index_y1;
	int	index_x2;
	int	index_y2;

	index_y1 = (int)(conf->player.pos_y);
	index_x1 = (int)(conf->player.pos_x + conf->player.dir_x * MV_SPD *
	conf->dt + (conf->player.dir_x * HITBOX));
	index_y2 = (int)(conf->player.pos_y + conf->player.dir_y * MV_SPD *
	conf->dt + (conf->player.dir_y * HITBOX));
	index_x2 = (int)(conf->player.pos_x);
	if (conf->map[index_y1][index_x1] != '1')
		conf->player.pos_x += conf->player.dir_x * MV_SPD * conf->dt;
	if (conf->map[index_y2][index_x2] != '1')
		conf->player.pos_y += conf->player.dir_y * MV_SPD * conf->dt;
	collisions(conf);
}

static void	move_down(t_config *conf)
{
	int	index_x1;
	int	index_y1;
	int	index_x2;
	int	index_y2;

	index_y1 = (int)(conf->player.pos_y);
	index_x1 = (int)(conf->player.pos_x - conf->player.dir_x * MV_SPD
	* conf->dt - (conf->player.dir_x * HITBOX));
	index_y2 = (int)(conf->player.pos_y - conf->player.dir_y * MV_SPD
	* conf->dt - (conf->player.dir_y * HITBOX));
	index_x2 = (int)(conf->player.pos_x);
	if (conf->map[index_y1][index_x1] != '1')
		conf->player.pos_x -= conf->player.dir_x * MV_SPD * conf->dt;
	if (conf->map[index_y2][index_x2] != '1')
		conf->player.pos_y -= conf->player.dir_y * MV_SPD * conf->dt;
	collisions(conf);
}

static void	turn_left(t_config *conf)
{
	double old_dir_x;
	double old_plane_x;

	old_dir_x = conf->player.dir_x;
	old_plane_x = conf->player.plane_x;
	conf->player.dir_x = conf->player.dir_x *
	cos(-RT_SPD) - conf->player.dir_y * sin(-RT_SPD);
	conf->player.dir_y = old_dir_x * sin(-RT_SPD) +
	conf->player.dir_y * cos(-RT_SPD);
	conf->player.plane_x = conf->player.plane_x * cos(-RT_SPD) -
	conf->player.plane_y * sin(-RT_SPD);
	conf->player.plane_y = old_plane_x * sin(-RT_SPD) +
	conf->player.plane_y * cos(-RT_SPD);
}

static void	turn_right(t_config *conf)
{
	double old_dir_x;
	double old_plane_x;

	old_dir_x = conf->player.dir_x;
	old_plane_x = conf->player.plane_x;
	conf->player.dir_x = conf->player.dir_x * cos(RT_SPD) -
	conf->player.dir_y * sin(RT_SPD);
	conf->player.dir_y = old_dir_x * sin(RT_SPD) +
	conf->player.dir_y * cos(RT_SPD);
	conf->player.plane_x = conf->player.plane_x * cos(RT_SPD) -
	conf->player.plane_y * sin(RT_SPD);
	conf->player.plane_y = old_plane_x * sin(RT_SPD) +
	conf->player.plane_y * cos(RT_SPD);
}

void		move_player(t_config *conf)
{
	if (conf->keyboard.up)
		move_up(conf);
	if (conf->keyboard.down)
		move_down(conf);
	if (conf->keyboard.left)
		turn_left(conf);
	if (conf->keyboard.right)
		turn_right(conf);
	jump(conf);
}
