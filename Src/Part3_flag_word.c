/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Part3_flag_word.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 14:31:23 by aoesterl          #+#    #+#             */
/*   Updated: 2025/10/31 15:32:23 by aoesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void flag_for_expand(t_flag *flag, char *str)
{
	int i;

	i = 0;
	while(str[i] != '\0')
	{
		if(str[i] == '\"' || str[i] == '\'')
			flag->quote = QUOTE;
		if(str[i] ==  '$')
			flag->dollar = DOLLAR;
		i++;
	}
}

static void flag_file(t_list *lst)
{
    if(lst->next != NULL)
    {
        if(lst->next->flag.type == WORD)
            lst->next->flag.word_type = FILES;
    }
}

static void flag_delimitor(t_list *lst)
{ 
    if(lst->next != NULL)
    {
        if(lst->next->flag.type == WORD)
            lst->next->flag.word_type = DELIMITOR;
    }
}

static void flag_cmd(t_list *lst)
{
	while(lst != NULL)
	{
		if(lst->flag.type == WORD)
		{
			if(lst->flag.word_type == 0)
				lst->flag.word_type = CMD;
		}
		lst = lst->next;
	}
}

void flag_word(t_list *lst)
{
    t_list *tmp;

    tmp = lst;
    while(tmp != NULL)
    {
        if(tmp->flag.type == WORD)
            flag_for_expand(&tmp->flag, tmp->content);
        if(tmp->flag.redir == REDIR)
		{
			if(tmp->flag.redir_type == HEREDOC)
				flag_delimitor(tmp);
			else 
			 	flag_file(tmp);
		}
		tmp = tmp->next;
    }
    flag_cmd(lst);
}
