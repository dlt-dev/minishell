/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_unset.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 18:09:58 by aoesterl          #+#    #+#             */
/*   Updated: 2025/11/14 17:15:25 by aoesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void find_env_to_unset(t_shell *shell, t_valist *env, char *name)
{ 
	t_valist *prev_node;

	prev_node = NULL;
	while(env != NULL)
	{ 
		if(ft_strcmp(name, env->name) == 0)
		{ 
			del_one_valist(&shell->env, env, prev_node);
			return;
		}
		prev_node = env;
		env = env->next;
	}
}


int builtin_unset(t_shell *shell, t_valist *env, char **args)
{
	int i;

	i = 1;
	if(env == NULL)
		return(0);
	while(args[i] != NULL)
	{
		find_env_to_unset(shell, env, args[i]);
		i++;
	}
	return(0);
}
