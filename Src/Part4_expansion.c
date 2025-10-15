/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Part4_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 15:15:26 by aoesterl          #+#    #+#             */
/*   Updated: 2025/10/15 19:12:57 by aoesterl         ###   ########.fr       */
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
int search_var(t_list *env, t_list* local, char *name)
{
	int i;
	int len;
	char *env;

	i = 0;
	len = len_name(name);
	if(len == 0)
		return(len);
	while(env != NULL)
	{ 
		if(ft_strncmp(name, env->content, len) == 0)
		{
			env = env->content;
			while(env->content[i] != '\0')
			{
				while()


			}
		}
		env = env->next;
	}
	
	
		


}


int count_single(char *str)
{ 
	int i;
	
	i = 1;
	while(str[i] != '\0' && str[i] != "\'")
		i++;
	return(i);
}

int count_double(t_shell *shell, char *str)
{ 
	int i;
	
	i = 1;
	while(str[i] != '\0' && str[i] != "\"")
	{ 
		if(str[i] == "$")
		{ 
			i++;
			search_var(shell->var.env, shell->var.local, str);
		}
	} 
}


char *count_expansion(char *str)
{ 
	int i;
	int mode;
	
	i = 0;
	mode = 0;
	while(str[i] != '\0')
	{ 
		if(str[i] == "\'")
			i+= count_single(&str[i]);
		if(str[i] == "\"")
		{ 
			mode = DOUBLE;	
			while(str[i] != '\0' && str[i] != "\"")
			{
				if(str[i] == "$")
					search_var(shell->var);
				i++;
			}	
		}	
		
		
	}	
}


int expand_param(t_shell *shell, t_list *lst)
{
	if(lst == NULL)
		return;
	while(lst != NULL)
	{ 
		if(lst->flag.dollar = DOLLAR)
			count_expansion(lst->content);
		lst = lst->next;
	}	
}