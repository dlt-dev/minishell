/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Part3_put_flag.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 23:12:31 by aoesterl          #+#    #+#             */
/*   Updated: 2025/10/24 19:26:50 by aoesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static void flag_word(t_flag *flag, char *str)
// {
// 	int i;

// 	i = 0;
// 	while(str[i] != '\0')
// 	{
// 		if(str[i] == '\"' || str[i] == '\'')
// 			flag->quote = QUOTE;
// 		if(str[i] ==  '$')
// 				flag->dollar = DOLLAR;
// 		i++;
// 	}
// }

// static void flag_meta(t_flag *flag, char *str)
// {
// 	int  i;

// 	i = 0;
// 	while(str[i] != '\0')
// 	{
// 		if(str[i] == '<' || str[i] == '>')
// 			flag->redir = REDIR;
// 		if(str[i] == '|')
// 			flag->pipe = PIPE;
// 		i++;
// 	}
// }

// static void flag_pipe_or_brakcet(t_list * lst)
// {
	
// 	while(lst != NULL)
// 	{ 
// 		if(lst->flag.type == META)
// 			flag_meta(&lst->flag, lst->content);
// 		lst = lst->next;
// 	}
// }

// static void flag_file(t_list *lst)
// {
// 	t_list *tmp;

// 	tmp = lst;
// 	while(lst != NULL)
// 	{ 
// 		if(lst->flag.type == REDIR)
// 		{ 
// 			if(tmp)

// 		}
// 		lst = lst->next;
// 		tmp = lst;
// 	}


	
// }

// static void flag_cmd_or_file(t_list *lst)
// { 
// 	flag_file(lst);



	
// }





void put_flags(t_list *lst)
{
	t_list *tmp;

	tmp = lst;
	if(lst == NULL)
		return;
	//meta_pipe_or_brakcet(lst);
	
}
