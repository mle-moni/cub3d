/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   konami.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-moni <mle-moni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 14:40:28 by mle-moni          #+#    #+#             */
/*   Updated: 2019/11/27 14:56:12 by mle-moni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus/main.h"

void		set_code(t_config *conf)
{
	conf->konami.max = 10;
	conf->konami.solve = 0;
	conf->konami.code[0] = K_ARR_UP;
	conf->konami.code[1] = K_ARR_UP;
	conf->konami.code[2] = K_ARR_DOWN;
	conf->konami.code[3] = K_ARR_DOWN;
	conf->konami.code[4] = K_ARR_LEFT;
	conf->konami.code[5] = K_ARR_RIGHT;
	conf->konami.code[6] = K_ARR_LEFT;
	conf->konami.code[7] = K_ARR_RIGHT;
	conf->konami.code[8] = K_B;
	conf->konami.code[9] = K_A;
}

void		konami_step(t_config *conf, int keycode)
{
	if (keycode == conf->konami.code[conf->konami.solve])
	{
		conf->konami.solve++;
		if (conf->konami.solve == conf->konami.max && conf->win == 1)
		{
			conf->konami.solve = 0;
			conf->map[4][18] = '0';
		}
	}
	else
		conf->konami.solve = 0;
}
