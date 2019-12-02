/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-moni <mle-moni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 16:28:05 by mle-moni          #+#    #+#             */
/*   Updated: 2019/11/27 08:05:11 by mle-moni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus/main.h"

void		get_texel_and_tex_id(t_castv *castv)
{
	castv->texel_x = (int)(castv->wall_x * (double)TXTR_SIZE);
	if (castv->side == 0 && castv->ray_dir_x > 0)
		castv->texel_x = TXTR_SIZE - castv->texel_x - 1;
	if (castv->side == 1 && castv->ray_dir_y < 0)
		castv->texel_x = TXTR_SIZE - castv->texel_x - 1;
	if (castv->side == 0)
	{
		if (castv->ray_dir_x > 0)
			castv->txt_id = 0;
		else
			castv->txt_id = 2;
	}
	if (castv->side == 1)
	{
		if (castv->ray_dir_y > 0)
			castv->txt_id = 3;
		else
			castv->txt_id = 1;
	}
}

void		draw_stripe(t_config *conf, t_castv *castv, int x)
{
	int		i;
	int		index;
	int		index_tex;
	t_img	texture;

	texture = conf->text_array[castv->txt_id].img;
	if (castv->txt_id < 0)
		texture = get_texture_by_id(conf, castv->txt_id * -1);
	i = 0;
	while (i < castv->line_height)
	{
		index = get_pixel_index(conf->img, conf->res_x - x,
		(conf->res_y / 2) - (castv->line_height / 2) + i);
		index_tex = (i * TXTR_SIZE / castv->line_height) * (TXTR_SIZE * 4) +
		castv->texel_x * 4;
		if ((texture.data)[index_tex + 3] != (char)255)
		{
			conf->img.data[index] = (texture.data)[index_tex];
			conf->img.data[index + 1] = (texture.data)[index_tex + 1];
			conf->img.data[index + 2] = (texture.data)[index_tex + 2];
			shift_color(conf, index, castv->ray_length);
		}
		i++;
	}
}

static void	cast_ray(t_config *conf, int x)
{
	t_castv test;
	t_castv *castv;

	castv = &test;
	dda(conf, castv, x);
	if (castv->side == 0)
		castv->ray_length = (castv->map_x - conf->player.pos_x +
		(1 - castv->step_x) / 2) / castv->ray_dir_x;
	else
		castv->ray_length = (castv->map_y - conf->player.pos_y +
		(1 - castv->step_y) / 2) / castv->ray_dir_y;
	castv->line_height = conf->distance_to_pjt_plane / castv->ray_length;
	if (castv->side == 0)
		castv->wall_x = conf->player.pos_y + castv->ray_length *
		castv->ray_dir_y;
	else
		castv->wall_x = conf->player.pos_x + castv->ray_length *
		castv->ray_dir_x;
	castv->wall_x -= floor((castv->wall_x));
	get_texel_and_tex_id(castv);
	if (castv->line_height > LINE_MAX)
		castv->line_height = LINE_MAX;
	draw_stripe(conf, castv, x);
	set_sprite_infos(conf, x);
}

void		cast_all(t_config *conf)
{
	int		x;

	x = 0;
	conf->obj.exist = 0;
	conf->obj.x = -1;
	conf->obj.w = 0;
	conf->obj.h_max = -1;
	conf->obj.h_min = -1;
	conf->obj.line_height = -1;
	while (x < conf->res_x)
	{
		cast_ray(conf, x);
		x += RAY;
	}
	slice(conf, 0, 0, conf->res_y);
	if (conf->obj.x != -1)
		draw_sprite(conf);
}
