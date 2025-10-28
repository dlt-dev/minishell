/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Part3_flag_word.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 14:31:23 by aoesterl          #+#    #+#             */
/*   Updated: 2025/10/27 15:04:32 by aoesterl         ###   ########.fr       */
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
            lst->next->flag.file = FILES;
    }
}

static void flag_cmd(t_list *lst)
{
	while(lst != NULL)
	{
		if(lst->flag.type == WORD)
		{
			if(lst->flag.file == 0)
				lst->flag.cmd = CMD;
		}
		lst = lst->next;
	}
}

void flag_word(t_list*lst)
{
    t_list *tmp;

    tmp = lst;
    while(tmp != NULL)
    {
        if(tmp->flag.type == WORD)
            flag_for_expand(&tmp->flag, tmp->content);
        if(tmp->flag.redir == REDIR)
            flag_file(tmp);
		tmp = tmp->next;
    }
    flag_cmd(lst);
}