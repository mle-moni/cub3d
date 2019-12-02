/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-moni <mle-moni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 12:04:48 by mle-moni          #+#    #+#             */
/*   Updated: 2019/11/27 14:56:44 by mle-moni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus/main.h"

int			exit_hook(void *config)
{
	free_config(config);
	exit(0);
}

static int	update_loop(t_config *conf)
{
	if (conf->player.lives > 0)
	{
		if (conf->win == 2)
			put_img(conf, &conf->win_img, conf->res_x / 2 - conf->lose.w / 2,
		conf->res_y / 2 - conf->lose.h / 2);
		else
		{
			init_sky_and_floor(conf);
			if (conf->koopa.exist)
				koopa_forward(conf);
			cast_all(conf);
			move_player(conf);
			if (conf->res_y > 800 && conf->res_x > 800)
				draw_map(conf);
			save_map(conf);
			get_microtime(conf, &conf->ms);
			frame_update(conf);
			display_hud(conf);
		}
	}
	else
		put_img(conf, &conf->lose, conf->res_x / 2 - conf->lose.w / 2,
		conf->res_y / 2 - conf->lose.h / 2);
	mlx_put_image_to_window(conf->init, conf->window, conf->img.img, 0, 0);
	return (1);
}

static int	key_release_hook(int keycode, void *param)
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
	else if (keycode == K_J)
		conf->keyboard.jump = 0;
	update_loop(param);
	return (0);
}

static int	key_press_hook(int keycode, void *param)
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
	else if (keycode == K_J)
		conf->keyboard.jump = 1;
	else if (keycode == K_F && conf->player.bonus)
		koopa_attack(conf);
	konami_step(conf, keycode);
	update_loop(param);
	return (0);
}

void		set_hooks(t_config *conf)
{
	mlx_do_key_autorepeatoff(conf->init);
	mlx_loop_hook(conf->init, update_loop, conf);
	mlx_hook(conf->window, 2, 0, key_press_hook, conf);
	mlx_hook(conf->window, 3, 0, key_release_hook, conf);
	mlx_hook(conf->window, 17, 0, exit_hook, conf);
}
