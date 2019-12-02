/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-moni <mle-moni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 09:12:45 by mle-moni          #+#    #+#             */
/*   Updated: 2019/11/13 14:55:05 by mle-moni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
# include "main.h"

char	**ft_split(char *str, char *charset);
int		get_res(char **line, t_config *conf);
int		get_map(char **line, t_config *conf, int fd);
int		get_path(char **line, t_config *conf, int pos);
int		get_color(char **line, t_config *conf, char id);

#endif
