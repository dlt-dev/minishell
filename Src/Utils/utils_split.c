/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_ split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 18:46:10 by aoesterl          #+#    #+#             */
/*   Updated: 2025/10/21 19:01:23 by aoesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_a_delimitor(char c, char *delimitor)
{
	int	i;

	i = 0;
	while (delimitor[i] != '\0')
	{
		if (c == delimitor[i])
			return (IS);
		i++;
	}
	return (IS_NOT);
}

int	ft_countword(char *str, char *delimit)
{
	int	i;
	int	count_word;

	i = 0;
	count_word = 0;
	while (str[i] != '\0')
	{
		while (is_a_delimitor(str[i], delimit) == IS && str[i] != '\0')
			i++;
		if (str[i] != '\0')
			count_word += 1;
		while (is_a_delimitor(str[i], delimit) == IS_NOT && str[i] != '\0')
			i++;
	}
	return (count_word);
}

int	ft_strlen_word(char *str, char *delimit)
{
	int	i;

	i = 0;
	while (is_a_delimitor(str[i], delimit) == IS_NOT && str[i] != '\0')
		i++;
	return (i);
}

char	*copy_until_delimit(char *str, char *delimit)
{
	char	*p;
	int		i;

	i = 0;
	p = malloc(sizeof(char) * (ft_strlen_word(str, delimit) + 1));
	if (p == NULL)
		return (NULL);
	while (is_a_delimitor(str[i], delimit) == IS_NOT && str[i] != '\0')
	{
		p[i] = str[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}

char	**ft_split_delimitor(char *str, char *delimit)
{
	char	**p;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (str == NULL || delimit == NULL)
		return (NULL);
	p = malloc(sizeof(char *) * (ft_countword(str, delimit) + 1));
	if (p == NULL)
		return (NULL);
	while (str[i] != '\0')
	{
		while (is_a_delimitor(str[i], delimit) == IS && str[i] != '\0')
			i++;
		if (str[i] == '\0')
			break ;
		p[j] = copy_until_delimit(&str[i], delimit);
		if (p[j] == NULL)
			return (ft_free_split(&p), NULL);
		i += ft_strlen_word(&str[i], delimit);
		j++;
	}
	p[j] = NULL;
	return (p);
}

/**
 * @brief 
 * @param is_a_delimitor regarde si char c fais partie de char delimitor
 * @return IS si char c est delimiteur, IS_NOT si char c n'est pas delimitor
 * @param count_word compte les mots par rapport a tous les caracteres qui sont
 * considere comme delimiteur.
 * @return le nombre de mots
 * @param copy_until_delimit copie les caracteres jusqu'a croiser un delimiteur
 * @return un char *str qui fera partie du char** 
 * 
 */