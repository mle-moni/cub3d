/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-moni <mle-moni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 12:46:41 by mle-moni          #+#    #+#             */
/*   Updated: 2019/11/27 11:44:23 by mle-moni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mandatory/main.h"

static void	move_up(t_config *conf)
{
	int	index_x1;
	int	index_y1;
	int	index_x2;
	int	index_y2;

	index_y1 = (int)(conf->player.pos_y);
	index_x1 = (int)(conf->player.pos_x + conf->player.dir_x * MV_SPD * HITBOX);
	index_y2 = (int)(conf->player.pos_y + conf->player.dir_y * MV_SPD * HITBOX);
	index_x2 = (int)(conf->player.pos_x);
	if (conf->map[index_y1][index_x1] != '1')
		conf->player.pos_x += conf->player.dir_x * MV_SPD;
	if (conf->map[index_y2][index_x2] != '1')
		conf->player.pos_y += conf->player.dir_y * MV_SPD;
}

static void	move_down(t_config *conf)
{
	int	index_x1;
	int	index_y1;
	int	index_x2;
	int	index_y2;

	index_y1 = (int)(conf->player.pos_y);
	index_x1 = (int)(conf->player.pos_x - conf->player.dir_x * MV_SPD * HITBOX);
	index_y2 = (int)(conf->player.pos_y - conf->player.dir_y * MV_SPD * HITBOX);
	index_x2 = (int)(conf->player.pos_x);
	if (conf->map[index_y1][index_x1] != '1')
		conf->player.pos_x -= conf->player.dir_x * MV_SPD;
	if (conf->map[index_y2][index_x2] != '1')
		conf->player.pos_y -= conf->player.dir_y * MV_SPD;
}

static void	turn(t_config *conf, double angle)
{
	double old_dir_x;
	double old_plane_x;

	old_dir_x = conf->player.dir_x;
	old_plane_x = conf->player.plane_x;
	conf->player.dir_x = conf->player.dir_x * cos(angle) -
	conf->player.dir_y * sin(angle);
	conf->player.dir_y = old_dir_x * sin(angle) +
	conf->player.dir_y * cos(angle);
	conf->player.plane_x = conf->player.plane_x * cos(angle) -
	conf->player.plane_y * sin(angle);
	conf->player.plane_y = old_plane_x * sin(angle) +
	conf->player.plane_y * cos(angle);
}

static void	move(t_config *conf, double angle)
{
	turn(conf, angle);
	move_up(conf);
	turn(conf, -angle);
}

void		move_player(t_config *conf)
{
	if (conf->keyboard.up)
		move_up(conf);
	if (conf->keyboard.down)
		move_down(conf);
	if (conf->keyboard.left)
		turn(conf, -RT_SPD);
	if (conf->keyboard.right)
		turn(conf, RT_SPD);
	if (conf->keyboard.l)
		move(conf, -M_PI_2);
	if (conf->keyboard.r)
		move(conf, M_PI_2);
}
