/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Part3_flags_main.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 23:12:31 by aoesterl          #+#    #+#             */
/*   Updated: 2025/11/19 13:46:18 by aoesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



static void flag_redir_type(t_flag *flag, char *str)
{ 
	int i;
	i = 0;
	if(str[i] == '>')
	{ 
		if(str[i+1] == '>')
			flag->redir_type = OUTFILE_APPEND;
		else
			flag->redir_type = OUTFILE;
	}
	if(str[i] == '<')
	{ 
		if(str[i+1] == '<')
			flag->redir_type = HEREDOC;
		else
			flag->redir_type = INFILE;
	}
	
}

static void flag_meta(t_flag *flag, char *str)
{
	int  i;

	i = 0;
	if(str[i] == '<' || str[i] == '>')
	{ 
		flag->redir = REDIR;
		flag_redir_type(flag, str);
	}
	if(str[i] == '|')
		flag->pipe = PIPE;
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
