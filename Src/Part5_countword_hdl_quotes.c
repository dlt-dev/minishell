/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Part5_countword_hdl_quotes.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 12:28:36 by aoesterl          #+#    #+#             */
/*   Updated: 2025/10/24 12:29:28 by aoesterl         ###   ########.fr       */
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