/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-moni <mle-moni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 16:27:41 by mle-moni          #+#    #+#             */
/*   Updated: 2019/11/23 16:09:29 by mle-moni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus/main.h"
#include "gnl/get_next_line.h"
#include "bonus/parsing.h"

int		quick_error(char *msg, char *msg2, t_config *config)
{
	config->error_msg = ft_str_cat(msg, msg2);
	return (-1);
}

int		get_config(char *line, t_config *conf, int fd)
{
	conf->ret = 1;
	if (line && line[0] == 'R')
		conf->ret = get_res(&line, conf);
	else if (line && line[0] == 'E' && line[1] == 'A')
		conf->ret = get_path(&line, conf, 0);
	else if (line && line[0] == 'N' && line[1] == 'O')
		conf->ret = get_path(&line, conf, 1);
	else if (line && line[0] == 'W' && line[1] == 'E')
		conf->ret = get_path(&line, conf, 2);
	else if (line && line[0] == 'S' && line[1] == 'O')
		conf->ret = get_path(&line, conf, 3);
	else if (line && line[0] == 'S')
		conf->ret = get_path(&line, conf, 4);
	else if (line && (line[0] == 'F' || line[0] == 'C'))
		conf->ret = get_color(&line, conf, line[0]);
	else if (line && line[0] == '1')
		conf->ret = get_map(&line, conf, fd);
	else if (line && line[0] != '\0')
	{
		quick_error("Unknown identifier, got: ", line, conf);
		free(line);
		return (-1);
	}
	free(line);
	return (conf->ret);
}

int		verif_path(const char *path)
{
	int i;

	i = str_len(path);
	if (i > 4 && path[i - 1] == 'b' && path[i - 2] == 'u'
	&& path[i - 3] == 'c' && path[i - 4] == '.')
		return (1);
	return (0);
}

int		parsing(t_config *conf, char *path)
{
	int		fd;
	int		ret;
	char	*line;

	if (!verif_path(path))
		return (quick_error("Wrong conf file: expected \"*.cub\", got: ",
			path, conf));
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (quick_error("Error while oppening conf file, path was: ",
		path, conf));
	ret = 1;
	while (ret == 1)
	{
		ret = get_next_line(fd, &line);
		if (ret == -1 || get_config(line, conf, fd) == -1)
			return (-1);
	}
	return (1);
}

int		free_config(t_config *config)
{
	free_split(config->map);
	free(config->error_msg);
	free(config->text_array[0].path);
	free(config->text_array[1].path);
	free(config->text_array[2].path);
	free(config->text_array[3].path);
	free(config->text_s.path);
	free(config->window);
	free(config->init);
	init_config(config);
	return (-1);
}
