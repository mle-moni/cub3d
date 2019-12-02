/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shift_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-moni <mle-moni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 10:22:52 by mle-moni          #+#    #+#             */
/*   Updated: 2019/11/27 07:46:02 by mle-moni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus/main.h"

void		shift_color(t_config *conf, int index, double distance)
{
	int shift;

	shift = (distance * 80 / 12);
	if ((unsigned char)conf->img.data[index] - shift > 0)
		conf->img.data[index] -= shift;
	else
		conf->img.data[index] = 0;
	if ((unsigned char)conf->img.data[index + 1] - shift > 0)
		conf->img.data[index + 1] -= shift;
	else
		conf->img.data[index + 1] = 0;
	if ((unsigned char)conf->img.data[index + 2] - shift > 0)
		conf->img.data[index + 2] -= shift;
	else
		conf->img.data[index + 2] = 0;
}
