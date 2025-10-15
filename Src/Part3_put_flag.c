/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Part3_put_flag.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 23:12:31 by aoesterl          #+#    #+#             */
/*   Updated: 2025/10/15 19:10:29 by aoesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


// int check_close_quote(char *str)
// {
// 	int i;
// 	char c;
	
// 	i = 0;
// 	c = 0;
// 	while(str[i] != '\0')
// 	{
// 		if(str[i] == '\'' || str[i] == '\"')
// 		{ 
// 			c = str[i];
// 			while(str[i] != '\0' && str[i] != c)
// 				i++;
// 			if(str[i] == '\0')
// 				return(ERROR);
// 		}
// 		i++;
// 	}
// 	return(0);
// }



void content_flag(t_flag* flag, const char *str)
{ 
	int i;
	
	i = 0;
	while(str[i] != '\0')
	{
		if(flag->type == WORD)
		{ 
			if(str[i] == '=')
				flag->affec_var = AFFEC_VAR;
			if(str[i] == '\"' || str[i] == '\'')
				flag->quote = QUOTE;
			if(str[i] ==  '$')
				flag->dollar = DOLLAR;
		}
		if(flag->type == META)
		{ 
			if(str[i] == '<' || str[i] == '>')
				flag->redir = REDIR;
			if(str[i] == '|')
				flag->pipe = PIPE;
		}
		i++;
	}
}

void put_flags (t_list *lst)
{ 
	if(lst == NULL)
		return;
	while(lst != NULL)
	{ 
		content_flag(&lst->flag, lst->content);
		lst = lst->next;
	}
}