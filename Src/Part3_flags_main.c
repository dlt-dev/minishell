/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Part3_flags_main.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 23:12:31 by aoesterl          #+#    #+#             */
/*   Updated: 2025/10/27 19:17:21 by aoesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


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


void put_flags(t_list *lst)
{
	if(lst == NULL)
		return;
	t_list *tmp;

	tmp = lst;
	if(lst == NULL)
		return;
	while(tmp != NULL)
	{ 
		if(tmp->flag.type == META)
			flag_meta(&tmp->flag, tmp->content);
		tmp = tmp->next;
	}
	flag_word(lst);
}
