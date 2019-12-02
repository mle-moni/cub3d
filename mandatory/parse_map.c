/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-moni <mle-moni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 14:15:57 by mle-moni          #+#    #+#             */
/*   Updated: 2019/11/23 13:29:38 by mle-moni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mandatory/main.h"
#include "gnl/get_next_line.h"
#include "mandatory/parsing.h"

int		check_bounds(t_config *cnf)
{
	int		i;

	i = 0;
	while ((cnf->map)[0][i] && (cnf->map)[0][i] != ' ')
		if ((cnf->map)[0][i++] != '1')
			return (quick_error("Open map: ", (cnf->map)[0], cnf));
	cnf->map_w = i;
	i = 0;
	while ((cnf->map)[cnf->map_h - 1][i] &&
	(cnf->map)[cnf->map_h - 1][i] != ' ')
		if ((cnf->map)[cnf->map_h - 1][i++] != '1')
			return (quick_error("Open map: ", (cnf->map)[cnf->map_h - 1], cnf));
	i = 1;
	while ((cnf->map)[i])
		if ((cnf->map)[i++][0] != '1')
			return (quick_error("Open map: ", (cnf->map)[i - 1], cnf));
	i = 1;
	while ((cnf->map)[i])
		if ((cnf->map)[i++][cnf->map_w - 1] != '1')
			return (quick_error("Open map: ", (cnf->map)[i - 1], cnf));
	return (1);
}

int		map_errors(t_config *cnf)
{
	int y;
	int x;
	int num;

	y = 0;
	num = -1;
	while ((cnf->map)[y])
	{
		x = 0;
		while ((cnf->map)[y][x])
		{
			if ((cnf->map)[y][x] == ' ')
			{
				if (num != x && num != -1)
					return (quick_error("Diff width in map lines", "", cnf));
				num = x;
				break ;
			}
			if (!is_from_str((cnf->map)[y][x++], "012NSEW"))
				return (quick_error("Bad char in map: ", (cnf->map)[y], cnf));
		}
		y++;
	}
	cnf->map_h = y;
	return (check_bounds(cnf));
}

void	shift_on_left(char c, t_config *config, int y)
{
	int x;

	x = 0;
	while (config->map[y][x])
	{
		if (config->map[y][x] == ' ')
		{
			config->map[y][x] = c;
			return ;
		}
		x++;
	}
}

void	reformat_map(t_config *config)
{
	int		y;
	int		x;
	int		sp;

	y = 0;
	sp = 0;
	while ((config->map)[y])
	{
		x = 0;
		while (config->map[y][x])
		{
			if (config->map[y][x] == ' ')
				sp = 1;
			else if (sp)
			{
				sp = 0;
				shift_on_left(config->map[y][x], config, y);
				config->map[y][x] = ' ';
			}
			x++;
		}
		y++;
	}
}

int		get_map(char **line, t_config *conf, int fd)
{
	int		ret;
	char	*map;
	char	*map_tmp;

	map = ft_str_cat(*line, "x");
	free((*line));
	ret = 1;
	while (ret == 1)
	{
		ret = get_next_line(fd, line);
		map_tmp = ft_str_cat(map, *line);
		free(map);
		free((*line));
		(*line) = NULL;
		map = map_tmp;
		map_tmp = ft_str_cat(map, "x");
		free(map);
		map = map_tmp;
	}
	conf->map = ft_split(map, "x");
	free(map);
	if (!conf->map)
		return (quick_error("Error while parsing the map", "", conf));
	reformat_map(conf);
	return (map_errors(conf));
}
