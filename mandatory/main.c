/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-moni <mle-moni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 16:27:47 by mle-moni          #+#    #+#             */
/*   Updated: 2019/11/27 11:38:18 by mle-moni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mandatory/main.h"

static int	init_mlx_and_start(t_config *conf)
{
	conf->init = mlx_init();
	if (init_textures(conf) == -1)
		return (put_error(conf));
	conf->img.img = mlx_new_image(conf->init, conf->res_x, conf->res_y);
	conf->img.data = mlx_get_data_addr(conf->img.img, &(conf->img.bpp),
	&(conf->img.size_line), &(conf->img.endian));
	conf->img.max = conf->img.size_line * conf->res_y;
	conf->window = mlx_new_window(conf->init,
	conf->res_x, conf->res_y, "Cub3D");
	conf->keyboard.l = 0;
	conf->keyboard.r = 0;
	set_hooks(conf);
	mlx_loop(conf->init);
	return (0);
}

static int	same_str(const char *str1, const char *str2)
{
	int i;

	i = 0;
	while (1)
	{
		if (!str1[i] && !str2[i])
			return (1);
		if (str1[i] != str2[i])
			return (0);
		i++;
	}
	return (1);
}

int			main(int ac, char **av)
{
	t_config	config;

	init_config(&config);
	if (ac == 3)
	{
		if (str_len(av[2]) == 5 && same_str(av[2], "-save"))
			config.save = 1;
		else
		{
			quick_error("Unknown parameter: ", av[2], &config);
			return (put_error(&config));
		}
	}
	if (ac >= 2)
	{
		if (parsing(&config, av[1]) == -1)
			return (put_error(&config));
		if (verif_config(&config) == -1)
			return (put_error(&config));
		return (init_mlx_and_start(&config));
	}
	return (0);
}
