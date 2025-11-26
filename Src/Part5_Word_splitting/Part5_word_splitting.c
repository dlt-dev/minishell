/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Part5_word_splitting.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelattr <jdelattr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 17:17:34 by aoesterl          #+#    #+#             */
/*   Updated: 2025/11/25 21:06:03 by jdelattr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	fill_quotes_in_buffer(t_cb *lst_buffer, char *str)
{
	int	i;
	int	flag_quotes;

	i = 0;
	flag_quotes = str[i];
	if (cb_append_char(lst_buffer, str[i]) == ERROR)
		return (ERROR);
	i++;
	while (str[i] != flag_quotes && str[i] != '\0')
	{
		if (cb_append_char(lst_buffer, str[i]) == ERROR)
			return (ERROR);
		i++;
	}
	if (str[i] == flag_quotes)
	{
		if (cb_append_char(lst_buffer, str[i]) == ERROR)
			return (ERROR);
		i++;
	}
	return (i);
}

/**
 * @brief on retient avec flag_quotes le type de quotes qui est apparu. et
 * on parcours ensuite la chaine jusqu'au prochain quotes suivant ou jusqu'a
 * ce que \0 soit rencontrer
 * @return i: le nombre d'elements dans les qutes qu'il faut skip.
 */

int	substr_buffer_full(t_cb *lst_buffer, char *str)
{
	int	i;
	int	check_failed;

	i = 0;
	while (is_char_in_str(str[i], " \t\n") == IS_NOT && str[i] != '\0')
	{
		if (str[i] == '\"' || str[i] == '\'')
		{
			check_failed = fill_quotes_in_buffer(lst_buffer, &str[i]);
			if (check_failed == ERROR)
				return (ERROR);
			i += check_failed;
		}
		else
		{
			if (cb_append_char(lst_buffer, str[i]) == ERROR)
				return (ERROR);
			i++;
		}
	}
	return (i);
}

/**

	* @brief @param Substr_buffer_full va parcourir le mot et 
	le mettre dans notre buffer

	* chunker. On continue tant qu'on ne rencontre pas le \0 ou un espace.
	Toutefois,
	si on

	* espace entre " ".  ca ne doti pas arrerter le mot. c'est 
	pourquoi @param fill_quotes_buffer
 * va nour permettre de mettre tout ce qu'il y a entre quotes dans un buffer.
 *
 * @return
 */

char	*substr_hdle_quotes(char *str, int *i)
{
	t_cb	lst_buffer;
	char	*p;
	int		check_failed;

	if (init_chunk_buffer(&lst_buffer, 10, 2) == ERROR)
		return (NULL);
	check_failed = substr_buffer_full(&lst_buffer, str);
	if (check_failed == ERROR)
		return (free_chunk_buffer(&lst_buffer), NULL);
	*i += check_failed;
	p = fusion_all_chunk(&lst_buffer);
	if (p == NULL)
		return (free_chunk_buffer(&lst_buffer), NULL);
	return (p);
}

char	**word_splitting(char *str, int count_word)
{
	char	**tab;
	int		i;
	int		j;

	i = 0;
	j = 0;
	tab = malloc(sizeof(char *) * (count_word + 1));
	if (tab == NULL)
		return (NULL);
	while (str[i] != '\0')
	{
		while (is_char_in_str(str[i], " \t\n") == IS && str[i] != '\0')
			i++;
		if (str[i] != '\0')
		{
			tab[j] = substr_hdle_quotes(&str[i], &i);
			if (tab[j] == NULL)
				return (ft_free_split(&tab), NULL);
			j++;
		}
	}
	tab[j] = NULL;
	return (tab);
}
