/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-moni <mle-moni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 17:24:40 by mle-moni          #+#    #+#             */
/*   Updated: 2019/11/23 13:29:03 by mle-moni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mandatory/main.h"

void		init_color(t_color *color, int r, int g, int b)
{
	color->r = r;
	color->g = g;
	color->b = b;
}

void		init_config(t_config *conf)
{
	conf->init = NULL;
	conf->window = NULL;
	conf->map = NULL;
	conf->error_msg = NULL;
	conf->res_x = -1;
	conf->res_y = -1;
	conf->text_array[0].path = NULL;
	conf->text_array[1].path = NULL;
	conf->text_array[2].path = NULL;
	conf->text_array[3].path = NULL;
	conf->text_s.path = NULL;
	init_color(&(conf->color_c), -1, -1, -1);
	init_color(&(conf->color_f), -1, -1, -1);
	conf->keyboard.down = 0;
	conf->keyboard.up = 0;
	conf->keyboard.right = 0;
	conf->keyboard.left = 0;
	set_color(&(conf->wt), 255, 255, 255);
	set_color(&conf->red, 255, 0, 0);
	set_color(&conf->green, 0, 255, 0);
	set_color(&conf->black, 0, 0, 0);
	conf->obj.exist = 0;
	conf->save = -1;
}

int			init_textures(t_config *conf)
{
	int			i;
	t_texture	*txtr;

	i = 0;
	while (i < 4)
	{
		txtr = &conf->text_array[i];
		txtr->img.img = mlx_xpm_file_to_image(conf->init,
		txtr->path, &txtr->img.w, &txtr->img.h);
		if (!txtr->img.img)
			return (quick_error("Could not load img: ", txtr->path, conf));
		txtr->img.data = mlx_get_data_addr(txtr->img.img,
		&txtr->img.bpp, &txtr->img.size_line, &txtr->img.endian);
		i++;
	}
	txtr = &conf->text_s;
	txtr->img.img = mlx_xpm_file_to_image(conf->init,
	txtr->path, &txtr->img.w, &txtr->img.h);
	if (!txtr->img.img)
		return (quick_error("Could not load img: ", txtr->path, conf));
	txtr->img.data = mlx_get_data_addr(txtr->img.img,
	&txtr->img.bpp, &txtr->img.size_line, &txtr->img.endian);
	return (1);
}
