/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-moni <mle-moni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 12:04:48 by mle-moni          #+#    #+#             */
/*   Updated: 2019/11/27 11:51:48 by mle-moni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mandatory/main.h"
#include "save/bmp.h"

int		exit_hook(void *config)
{
	free_config(config);
	exit(0);
}

int		update_loop(t_config *conf)
{
	fill_space(conf, 0, conf->res_y / 2, conf->color_c);
	fill_space(conf, conf->res_y / 2, conf->res_y, conf->color_f);
	cast_all(conf);
	move_player(conf);
	if (conf->res_y > 800 && conf->res_x > 800)
		draw_map(conf);
	if (conf->save == 1)
	{
		conf->save = 0;
		if (save(conf, &conf->img) == -1)
		{
			put_error(conf);
			exit_hook(conf);
		}
	}
	mlx_put_image_to_window(conf->init, conf->window, conf->img.img, 0, 0);
	return (1);
}

int		key_release_hook(int keycode, void *param)
{
	t_config	*conf;

	conf = (t_config*)param;
	if (keycode == K_W)
		conf->keyboard.up = 0;
	else if (keycode == K_S)
		conf->keyboard.down = 0;
	else if (keycode == K_D)
		conf->keyboard.right = 0;
	else if (keycode == K_A)
		conf->keyboard.left = 0;
	else if (keycode == K_L)
		conf->keyboard.l = 0;
	else if (keycode == K_R)
		conf->keyboard.r = 0;
	update_loop(param);
	return (0);
}

int		key_press_hook(int keycode, void *param)
{
	t_config	*conf;

	conf = (t_config*)param;
	if (keycode == 53)
		exit_hook(param);
	if (keycode == K_W)
		conf->keyboard.up = 1;
	else if (keycode == K_S)
		conf->keyboard.down = 1;
	else if (keycode == K_D)
		conf->keyboard.right = 1;
	else if (keycode == K_A)
		conf->keyboard.left = 1;
	else if (keycode == K_L)
		conf->keyboard.l = 1;
	else if (keycode == K_R)
		conf->keyboard.r = 1;
	update_loop(param);
	return (0);
}

void	set_hooks(t_config *conf)
{
	mlx_do_key_autorepeatoff(conf->init);
	mlx_loop_hook(conf->init, update_loop, conf);
	mlx_hook(conf->window, 2, 0, key_press_hook, conf);
	mlx_hook(conf->window, 3, 0, key_release_hook, conf);
	mlx_hook(conf->window, 17, 0, exit_hook, conf);
}
