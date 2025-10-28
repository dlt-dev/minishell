/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Part5_countword_hdl_quotes.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 12:28:36 by aoesterl          #+#    #+#             */
/*   Updated: 2025/10/28 18:50:29 by aoesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int skip_quotes(char *str)
{
	int flag_quotes;
	int i;

	i = 0;
	flag_quotes = str[i];
	i++;
	while(str[i] != flag_quotes && str[i] != '\0')
		i++;
	if(str[i] == flag_quotes)
		i++;
	return(i);
}

int skip_word(char *str)
{
	int  i;
	i = 0;
	while(is_char_in_str(str[i], " \t\n") == IS_NOT && str[i] != '\0')
	{
		if(str[i] == '\"' || str[i] == '\'')
			i += skip_quotes(&str[i]);
		else
			i++;
	}
	return(i);
}

/**
 * @brief @param skip_word on parcours le mot jusqu'au \0 ou
 * jusqu'au prochaine espacement, si on rencontre un quotes on
 * rentre dans @param skip_quotes. les quotes skip les caracteres jusqu'au
 * \0 ou jusqu'a la quotes la suivante.
 * @return int 
 */

int count_word_hdle_quotes(char *str)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while(str[i] != '\0')
	{
		while(is_char_in_str(str[i], " \t\n") == IS && str[i] != '\0')
			i++;
		if(str[i] != '\0')
		{
			i += skip_word(&str[i]);
			count += 1;
		}
	}
	return(count);
}

/**
 * @brief @param count_word_hdle_quotes va parcourir la chaine content
 * de notre node. si un mot est rencontrer on va dans skip word et on fait
 * +1.
 * @param str: Chaine de caractere a split
 */