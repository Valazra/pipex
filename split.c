/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 14:11:23 by user42            #+#    #+#             */
/*   Updated: 2021/10/08 14:46:08 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	free_split(char **tab, unsigned int j)
{
	int	x;

	x = (int)j;
	while (--x >= 0)
		free((tab)[x]);
	free(tab);
	return (0);
}

unsigned int	get_nb_words(char const *s, char c)
{
	unsigned int	i;
	unsigned int	nb_words;

	i = 0;
	nb_words = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i])
			nb_words++;
		while (s[i] != c && s[i])
			i++;
	}
	return (nb_words);
}

int	splitter(char **tab, char const *s, char c, unsigned int n)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	wordlen;

	i = 0;
	j = 0;
	while (j < n)
	{
		wordlen = 0;
		while (s[i] && s[i] == c)
			i++;
		while (s[i] && s[i] != c)
		{
			i++;
			wordlen++;
		}
		tab[j] = ft_substr(s, (i - wordlen), wordlen);
		if (!tab[j])
			return (free_split(tab, j));
		j++;
	}
	tab[j] = NULL;
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char			**tab;
	unsigned int	nb_words;

	if (!s)
		return (NULL);
	nb_words = get_nb_words(s, c);
	tab = (char **)malloc(sizeof(char *) * (nb_words + 1));
	if (!tab)
		return (NULL);
	if (splitter(tab, s, c, nb_words))
		return (tab);
	return (NULL);
}