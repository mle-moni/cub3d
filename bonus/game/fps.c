/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fps.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-moni <mle-moni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 15:41:47 by mle-moni          #+#    #+#             */
/*   Updated: 2019/11/27 11:12:20 by mle-moni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus/main.h"
#include <sys/time.h>
#include "save/bmp.h"

void	get_microtime(t_config *conf, long *u_time)
{
	struct timeval	current_time;
	long			tmp_time;

	gettimeofday(&current_time, NULL);
	tmp_time = current_time.tv_sec * (int)1e6 + current_time.tv_usec;
	tmp_time /= 1000;
	if (conf->ms != 0)
		conf->dt = tmp_time - conf->ms;
	*u_time = tmp_time;
}

void	save_map(t_config *conf)
{
	if (conf->save == 1)
	{
		conf->save = 0;
		if (save(conf, &conf->img) == -1)
		{
			put_error(conf);
			exit_hook(conf);
		}
	}
}
