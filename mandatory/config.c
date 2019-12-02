/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-moni <mle-moni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 10:40:55 by mle-moni          #+#    #+#             */
/*   Updated: 2019/11/23 13:29:03 by mle-moni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mandatory/main.h"

static void	map_loop(t_config *conf, int i, int j, int *ok)
{
	while ((conf->map)[i][j])
		if (is_from_str((conf->map)[i][j++], "NSEW"))
		{
			*ok = 1;
			conf->player.pos_x = (double)((j - 1) * TILE_SIZE);
			conf->player.pos_y = (double)(i * TILE_SIZE);
			conf->player.angle = get_rot((conf->map)[i][j - 1]);
			conf->player.dir_x = cos(conf->player.angle);
			conf->player.dir_y = -sin(conf->player.angle);
			conf->player.plane_x = 0.0 * cos(conf->player.angle) -
			(-0.66 * sin(conf->player.angle));
			conf->player.plane_y = 0.0 * sin(conf->player.angle) +
			(-0.66 * cos(conf->player.angle));
			conf->map[i][j - 1] = '0';
		}
}

int			verif_map(t_config *conf)
{
	int		i;
	int		j;
	int		ok;

	i = 0;
	ok = 0;
	if (!(conf->map))
		return (quick_error("Failed to load map", "", conf));
	while ((conf->map)[i])
	{
		j = 0;
		map_loop(conf, i, j, &ok);
		i++;
	}
	if (!ok)
		return (quick_error("Map has no player", "", conf));
	return (1);
}

int			verif_config(t_config *config)
{
	if (!verif_map(config))
		return (-1);
	if (!check_color(config->color_c) || !check_color(config->color_f))
		return (quick_error("Some colors are missing", "", config));
	if (config->error_msg)
		return (put_error(config));
	if (!config->text_array[0].path || !config->text_array[1].path)
		return (quick_error("Some textures are missing", "", config));
	if (!config->text_array[2].path || !config->text_array[3].path)
		return (quick_error("Some textures are missing", "", config));
	if (!config->text_s.path)
		return (quick_error("Some textures are missing", "", config));
	if (config->res_x == -1 || config->res_y == -1)
		return (quick_error("No resolution given", "", config));
	config->distance_to_pjt_plane = (int)(((double)(config->res_x / 2)
	/ tan(M_PI / 6)));
	config->player.pos_x = config->player.pos_x / TILE_SIZE + 0.5;
	config->player.pos_y = config->player.pos_y / TILE_SIZE + 0.5;
	config->player.dir_x = cos(config->player.angle);
	config->player.dir_y = -sin(config->player.angle);
	config->player.plane_x = +0.66 * sin(-config->player.angle);
	config->player.plane_y = -0.66 * cos(-config->player.angle);
	return (1);
}
