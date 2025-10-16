/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Part4_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 15:15:26 by aoesterl          #+#    #+#             */
/*   Updated: 2025/10/16 11:00:35 by aoesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int len_name(char *name)
{ 
	int i;

	i = 0;
	if((name[0] < 'A' || name[0] > 'Z') && 
		(name[0] < 'a' || name[0] > 'z') && (name[0] != '_'))
			return(0);
	while(name[i] != '\0')
	{
		if((name[i] < '0' || name[i] > '9') &&
		(name[i] < 'A' || name[i] > 'Z') && 
		(name[i] < 'a' || name[i] > 'z') && (name[i] != '_'))
			break;
		i++;
	} 
	return(i);
}

int search_count_var(t_valist *env, t_valist* local, char *name)
{
	int i;
	int len;
	char *env;

	i = 0;
	len = len_name(name);
	if(len == 0)
		return(0);
	while(env != NULL)
	{ 
		if(ft_strncmp(name, env->name, len) == 0)
		{
			i = ft_strlen(env->value);
			break;
		}
		env = env->next;
	}
	return(i);
}

int count_single(char *str)
{ 
	int i;
	
	i = 1;
	while(str[i] != '\0' && str[i] != "\'")
		i++;
	return(i);
}


int count_expansion(t_shell *shell, char *str)
{ 
	int i;
	
	i = 0;
	while(str[i] != '\0')
	{ 
		if(str[i] == "\'")
			i+= count_single(&str[i]);
		if(str[i] == "$")
			i+= search_count_var(shell->var.env, shell->var.local, &str[i]);
		if(str[i] != '\0')
			i++;
	}
	return(i);
}


int expand_param(t_shell *shell, t_list *lst)
{
	if(lst == NULL)
		return;
	while(lst != NULL)
	{ 
		if(lst->flag.dollar = DOLLAR)
			count_expansion(shell, lst->content);
		lst = lst->next;
	}	
}