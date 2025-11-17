/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_manage_valist.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 17:52:37 by aoesterl          #+#    #+#             */
/*   Updated: 2025/11/17 18:01:37 by aoesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char* getenv_intern(t_valist* env, char *name)
{
	while(env != NULL)
	{ 
		if(strcmp(env->name, name) == 0)
			return(env->value);
		env = env->next;
	}
	return(NULL);
}

int set_env_intern(t_shell *shell, char *name, char *value)
{
	char *new_value;
	t_valist *tmp;
	t_valist *env;
	
	new_value = ft_strdup(value);
	if(new_value == NULL)
		return(ERROR);
	env = shell->env;
	while(env != NULL)
	{ 
		if(strcmp(name, env->name) == 0)
		{ 
			free(env->value);
				env->value = new_value;
			return(0);
		}
		env = env->next;
	}
	tmp = var_new(name, new_value);
	if(tmp == NULL)	
		return(free(new_value), ERROR);
	var_addback(&shell->env, tmp);
	return(0);
}