/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelattr <jdelattr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 15:41:16 by jdelattr          #+#    #+#             */
/*   Updated: 2025/11/14 15:41:41 by jdelattr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_count(char const *s, char c)
{
	int	i;
	int	wordcount;
	int	inworld;

	i = 0;
	wordcount = 0;
	inworld = 0;
	while (s[i])
	{
		if (s[i] == c)
			inworld = 0;
		else if (s[i] != c)
		{
			if (inworld == 0)
				wordcount++;
			inworld = 1;
		}
		i++;
	}
	return (wordcount);
}

static char	**ft_allocsplit(int wordcount)
{
	int		i;
	char	**split;

	i = 0;
	split = malloc(sizeof(char *) * (wordcount + 1));
	if (!split)
		return (NULL);
	while (i < (wordcount + 1))
	{
		split[i] = NULL;
		i++;
	}
	return (split);
}

static char	**ft_freesplit(char **split, int j)
{
	while (j > 0)
	{
		j--;
		free(split[j]);
	}
	free(split);
	return (0);
}

static char	**ft_fillsplit(char **split, char const *s, char c)
{
	int	i;
	int	j;
	int	start;

	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		start = i;
		while (s[i] && s [i] != c)
			i++;
		if (i > start)
		{
			split[j] = ft_substr(s, start, i - start);
			if (split[j] == 0)
				return (ft_freesplit(split, j));
			j++;
		}
	}
	split[j] = NULL;
	return (split);
}

char	**ft_split(char const *s, char c)
{
	char	**split;
	int		wordcount;

	wordcount = ft_count(s, c);
	split = ft_allocsplit(wordcount);
	if (!split)
		return (NULL);
	split = ft_fillsplit(split, s, c);
	return (split);
}