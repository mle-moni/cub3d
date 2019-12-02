/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-moni <mle-moni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 14:06:34 by mle-moni          #+#    #+#             */
/*   Updated: 2019/11/23 16:09:29 by mle-moni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus/main.h"

int		word_count(char *str, char *charset)
{
	int i;
	int word;
	int num_word;

	i = 0;
	word = 0;
	num_word = 0;
	while (str[i])
	{
		if (is_from_str(str[i], charset))
		{
			if (word)
			{
				num_word++;
				word = 0;
			}
		}
		else
		{
			word++;
		}
		i++;
	}
	return (word ? num_word + 1 : num_word);
}

char	*dupn(char *str, int n)
{
	int		i;
	char	*new;

	new = malloc((n + 1) * sizeof(char));
	if (!new)
		return (NULL);
	i = 0;
	while (str[i] && i < n)
	{
		new[i] = str[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

int		process(char **final, char *str, char *charset, int *index)
{
	int i;
	int is_word;

	i = 0;
	is_word = 0;
	while (str[i])
	{
		if (is_from_str(str[i], charset))
		{
			if (is_word)
			{
				final[*index] = dupn(str + i - is_word, is_word);
				if (!(final[*index]))
					return (0);
				(*index)++;
				is_word = 0;
			}
		}
		else
			is_word++;
		i++;
	}
	if (is_word)
		return ((int)(final[(*index)++] = dupn(str + i - is_word, is_word)));
	return (1);
}

char	**ft_split(char *str, char *charset)
{
	char	**final;
	int		words;
	int		index;

	words = word_count(str, charset);
	index = 0;
	final = malloc((words + 1) * sizeof(char*));
	if (!final)
		return (NULL);
	if (!process(final, str, charset, &index))
		return (NULL);
	final[index] = 0;
	return (final);
}
