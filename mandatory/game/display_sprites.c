/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_sprites.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-moni <mle-moni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 15:57:53 by mle-moni          #+#    #+#             */
/*   Updated: 2019/11/23 13:29:03 by mle-moni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mandatory/main.h"

void		set_sprite_infos(t_config *conf, int x)
{
	t_castv *castv;

	if (conf->obj.exist)
	{
		castv = &(conf->obj.castv);
		if (conf->obj.x == -1)
			conf->obj.x = x;
		conf->obj.exist = 0;
		conf->obj.w++;
		if (castv->side == 0)
			castv->ray_length = (castv->map_x - conf->player.pos_x +
			(1 - castv->step_x) / 2) / castv->ray_dir_x;
		else
			castv->ray_length = (castv->map_y - conf->player.pos_y +
			(1 - castv->step_y) / 2) / castv->ray_dir_y;
		castv->line_height = conf->distance_to_pjt_plane / castv->ray_length;
		if (castv->line_height > LINE_MAX)
			castv->line_height = LINE_MAX;
		if (conf->obj.h_min == -1 || conf->obj.h_min > castv->line_height)
			conf->obj.h_min = castv->line_height;
		if (conf->obj.h_max == -1 || conf->obj.h_max < castv->line_height)
			conf->obj.h_max = castv->line_height;
	}
}

void		draw_sprite(t_config *conf)
{
	int i;
	int average;

	i = conf->obj.x;
	average = (conf->obj.h_max + conf->obj.h_min) / 2;
	conf->obj.castv.line_height = average;
	conf->obj.castv.txt_id = -1;
	while (i < conf->obj.w + conf->obj.x)
	{
		conf->obj.castv.texel_x = ((i - conf->obj.x) * TXTR_SIZE) / conf->obj.w;
		draw_stripe(conf, &conf->obj.castv, i);
		i++;
	}
}
