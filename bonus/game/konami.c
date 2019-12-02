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
	conf->konami.code[0] = 126;
	conf->konami.code[1] = 126;
	conf->konami.code[2] = 125;
	conf->konami.code[3] = 125;
	conf->konami.code[4] = 123;
	conf->konami.code[5] = 124;
	conf->konami.code[6] = 123;
	conf->konami.code[7] = 124;
	conf->konami.code[8] = 11;
	conf->konami.code[9] = 0;
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
