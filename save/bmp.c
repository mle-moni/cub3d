/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-moni <mle-moni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 09:47:52 by mle-moni          #+#    #+#             */
/*   Updated: 2019/11/23 14:48:18 by mle-moni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "save/bmp.h"
#include <errno.h>

static void	write_32b_tohex_l_endian(int pixels, int fd)
{
	int				i;
	unsigned char	c;

	i = 0;
	while (i < 4)
	{
		c = pixels % 256;
		pixels /= 256;
		i++;
		write(fd, &c, 1);
	}
}

static void	write_pixels(t_config *conf, t_img *img, int fd)
{
	int		i;
	int		j;
	int		offset;

	j = conf->res_y - 1;
	while (j >= 0)
	{
		i = get_pixel_index(*img, 0, j);
		offset = 0;
		write(fd, img->data + i, img->size_line);
		j--;
	}
}

int			save(t_config *conf, t_img *img)
{
	int		fd;

	fd = open("save.bmp", O_CREAT | O_WRONLY, 0666);
	if (fd == -1)
		return (quick_error("Error while creating file: ", "save.bmp", conf));
	write(fd, "BM", 2);
	write_32b_tohex_l_endian(img->max + 0x28, fd);
	write(fd, "\0\0\0\0", 4);
	write(fd, "6\0\0\0", 4);
	write(fd, "(\0\0\0", 4);
	write_32b_tohex_l_endian(conf->res_x, fd);
	write_32b_tohex_l_endian(conf->res_y, fd);
	write(fd, "\1\0", 2);
	write(fd, " \0", 2);
	write(fd, "\0\0\0\0\0\0\0\0", 8);
	write(fd, "\0\0\0\0\0\0\0\0", 8);
	write(fd, "\0\0\0\0\0\0\0\0", 8);
	write_pixels(conf, img, fd);
	return (0);
}
