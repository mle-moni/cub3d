/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-moni <mle-moni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 16:57:39 by mle-moni          #+#    #+#             */
/*   Updated: 2019/11/23 13:29:03 by mle-moni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mandatory/main.h"

static void	set_steps(t_config *conf, t_castv *castv)
{
	if (castv->ray_dir_x < 0)
	{
		castv->step_x = -1;
		castv->side_dist_x = (conf->player.pos_x - castv->map_x) *
		castv->delta_dist_x;
	}
	else
	{
		castv->step_x = 1;
		castv->side_dist_x = (castv->map_x + 1.0 - conf->player.pos_x) *
		castv->delta_dist_x;
	}
	if (castv->ray_dir_y < 0)
	{
		castv->step_y = -1;
		castv->side_dist_y = (conf->player.pos_y - castv->map_y) *
		castv->delta_dist_y;
	}
	else
	{
		castv->step_y = 1;
		castv->side_dist_y = (castv->map_y + 1.0 - conf->player.pos_y) *
		castv->delta_dist_y;
	}
}

static void	prepare_dda(t_config *conf, t_castv *castv, int x)
{
	castv->camera_x = 2 * (x) / (double)(conf->res_x) - 1;
	castv->ray_dir_x = conf->player.dir_x + conf->player.plane_x *
	castv->camera_x;
	castv->ray_dir_y = conf->player.dir_y + conf->player.plane_y *
	castv->camera_x;
	castv->map_x = (int)(conf->player.pos_x);
	castv->map_y = (int)(conf->player.pos_y);
	castv->delta_dist_x = fabs(1 / castv->ray_dir_x);
	castv->delta_dist_y = fabs(1 / castv->ray_dir_y);
	castv->hit = 0;
	set_steps(conf, castv);
}

static void	cpy_castv(t_castv *castv, t_castv *cpy)
{
	cpy->camera_x = castv->camera_x;
	cpy->ray_dir_x = castv->ray_dir_x;
	cpy->ray_dir_y = castv->ray_dir_y;
	cpy->side_dist_x = castv->side_dist_x;
	cpy->side_dist_y = castv->side_dist_y;
	cpy->delta_dist_x = castv->delta_dist_x;
	cpy->delta_dist_y = castv->delta_dist_y;
	cpy->ray_length = castv->ray_length;
	cpy->line_height = castv->line_height;
	cpy->step_x = castv->step_x;
	cpy->step_y = castv->step_y;
	cpy->side = castv->side;
	cpy->map_x = castv->map_x;
	cpy->map_y = castv->map_y;
	cpy->txt_id = castv->txt_id;
	cpy->texel_x = castv->texel_x;
	cpy->hit = castv->hit;
}

void		dda(t_config *conf, t_castv *castv, int x)
{
	prepare_dda(conf, castv, x);
	while (castv->hit == 0)
	{
		if (castv->side_dist_x < castv->side_dist_y)
		{
			castv->side_dist_x += castv->delta_dist_x;
			castv->map_x += castv->step_x;
			castv->side = 0;
		}
		else
		{
			castv->side_dist_y += castv->delta_dist_y;
			castv->map_y += castv->step_y;
			castv->side = 1;
		}
		if (conf->map[castv->map_y][castv->map_x] == '1')
			castv->hit = 1;
		if (conf->map[castv->map_y][castv->map_x] == '2')
		{
			cpy_castv(castv, &(conf->obj.castv));
			conf->obj.exist = 1;
		}
	}
}
