/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Part0_init_var.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 00:00:39 by aoesterl          #+#    #+#             */
/*   Updated: 2025/10/21 19:28:15 by aoesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void bzero_shell(t_shell *shell)
{ 
	*shell = (t_shell){0};
	shell->invite.color_user = YELL_PS;
	shell->invite.color_cwd = BLUE_PS;
	shell->invite.color_reset = RESET;
}

static int init_env_lst(t_valist **env, char *envp)
{
	int len_name;
    int len_value;
	char *name;
	char *value;
	
	len_name = length_name(envp);
    name = ft_strndup(envp, len_name);
	if(name == NULL)
		return(ERROR);
	len_value = ft_strlen(envp) - (len_name + 1); 
	value = ft_strndup(&envp[len_name + 1], len_value);
	if(value == NULL)
		return(free(name), ERROR);
	if(var_in_lst(env, name, value) == ERROR)
		return(free(name), free(value), ERROR);
	return(0);
}

static int init_local_lst(t_valist **local)
{ 	
	char *name;
	char *value;

	name = ft_strdup("IFS");
	if(name == NULL)
		return(ERROR);
	value = ft_strdup(" \t\n");
	if(value == NULL)
		return(free(name), ERROR);
	if(var_in_lst(local, name, value) == ERROR)
		return(free(name), free(value), ERROR);
	return(0);
}

int init_variable(t_shell *shell, int argc, char **argv, char **envp)
{
	int i;
	(void)argc;
	(void)argv;
	
	i = 0;
	bzero_shell(shell);
	while(envp[i] != NULL)	
	{
		if(init_env_lst (&shell->var.env, envp[i]) == ERROR)
			return(ERROR);
		i++;
	}
		if(init_local_lst(&shell->var.local) == ERROR)
			return(ERROR);
	return(0);
}
