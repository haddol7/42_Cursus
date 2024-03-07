/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_in_atoi.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 20:20:18 by daeha             #+#    #+#             */
/*   Updated: 2024/03/05 20:21:30 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static size_t	my_count_word(char const *s, char c)
{
	size_t	count;
	size_t	i;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			count++;
		i++;
	}
	return (count);
}

static char	*my_make_word(char const *s, char c, size_t *offset)
{
	char	*word;
	size_t	i;

	i = 0;
	while (s[i] != '\0' && s[i] != c)
		i++;
	*offset += i;
	word = (char *)malloc((i + 1) * sizeof(char));
	if (word == NULL)
		return (NULL);
	ft_strlcpy(word, s, i + 1);
	return (word);
}

static char	**my_free_word(char **word_set, size_t i)
{
	size_t	k;

	k = 0;
	while (k < i)
	{
		free(word_set[k]);
		k++;
	}
	free(word_set);
	return (0);
}

char	**split_in_atoi(char const *s, t_map *map)
{
	char	**word_set;
	size_t	word;
	size_t	i;
	size_t	offset;

	if (s == NULL)
		return (NULL);
	i = 0;
	offset = 0;
	word = my_count_word(s, ' ');
	word_set = (char **)malloc((word + 1) * sizeof(char *));
	if (word_set == NULL)
		return (0);
	while (i < word)
	{
		while (s[offset] == ' ')
			offset++;
		word_set[i] = my_make_word(s + offset, ' ', &offset);
		if (word_set[i] == 0)
			return (my_free_word(word_set, i));
		i++;
	}
	word_set[word] = 0;
	return (word_set);
}
