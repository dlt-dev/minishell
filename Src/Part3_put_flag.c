/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Part3_put_flag.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 23:12:31 by aoesterl          #+#    #+#             */
/*   Updated: 2025/10/21 14:43:12 by aoesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void flag_word(t_flag *flag, char *str)
{
	int i;

	i = 0;
	while(str[i] != '\0')
	{
		if(str[i] == '=')
			flag->affec_var = AFFEC_VAR;
		if(str[i] == '\"' || str[i] == '\'')
			flag->quote = QUOTE;
		if(str[i] ==  '$')
				flag->dollar = DOLLAR;
		i++;
	}
}

static void flag_meta(t_flag *flag, char *str)
{
	int  i;

	i = 0;
	while(str[i] != '\0')
	{
		if(str[i] == '<' || str[i] == '>')
			flag->redir = REDIR;
		if(str[i] == '|')
			flag->pipe = PIPE;
		i++;
	}
}

static void content_flag(t_flag* flag, char *str)
{ 
	if(flag->type == WORD)
		flag_word(flag, str);
	if(flag->type == META)
		flag_meta(flag, str);
}

void put_flags(t_list *lst)
{ 
	if(lst == NULL)
		return;
	while(lst != NULL)
	{ 
		content_flag(&lst->flag, lst->content);
		lst = lst->next;
	}
}
