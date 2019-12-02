/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   laiktu.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-moni <mle-moni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 09:36:18 by mle-moni          #+#    #+#             */
/*   Updated: 2019/11/27 10:06:25 by mle-moni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus/main.h"

void		load_laiktu(t_config *conf)
{
	int			i;
	static char	template[32] = "./img/laiktu_xpm/laiktu_00.xpm";

	i = 0;
	conf->laiktu.frame_id = 0;
	while (i < 32)
	{
		template[24] = i / 10 + '0';
		template[25] = i % 10 + '0';
		load_sprite(conf, template, &(conf->laiktu.frames[i]));
		i++;
	}
	conf->laiktu.current_frame = conf->laiktu.frames[0];
}

void		frame_update(t_config *conf)
{
	int frame;

	conf->laiktu.frame_id++;
	if (conf->laiktu.frame_id >= 32)
		conf->laiktu.frame_id = 0;
	frame = conf->laiktu.frame_id;
	conf->laiktu.current_frame = conf->laiktu.frames[frame];
}
