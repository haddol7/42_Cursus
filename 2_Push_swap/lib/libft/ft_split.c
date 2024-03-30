/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 16:51:15 by daeha             #+#    #+#             */
/*   Updated: 2023/11/20 17:57:33 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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

char	**ft_split(char const *s, char c)
{
	char	**word_set;
	size_t	word;
	size_t	i;
	size_t	offset;

	if (s == NULL)
		return (NULL);
	i = 0;
	offset = 0;
	word = my_count_word(s, c);
	word_set = (char **)malloc((word + 1) * sizeof(char *));
	if (word_set == NULL)
		return (0);
	while (i < word)
	{
		while (s[offset] == c)
			offset++;
		word_set[i] = my_make_word(s + offset, c, &offset);
		if (word_set[i] == 0)
			return (my_free_word(word_set, i));
		i++;
	}
	word_set[word] = 0;
	return (word_set);
}
// #include <stdio.h>
// int	main(int argc, char **argv)
// {
// 	char	**word_set;
// 	word_set = ft_split(NULL, '^');
// 	while (*word_set != 0)
// 	{
// 		printf("%s\n", *word_set);
// 		word_set++;
// 	}
// 	return (0);
// }
