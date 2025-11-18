/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Part0_init_var.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelattr <jdelattr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 00:00:39 by aoesterl          #+#    #+#             */
/*   Updated: 2025/11/18 13:31:13 by jdelattr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void bzero_shell(t_shell *shell)
{ 
	*shell = (t_shell){0};
	shell->invite.color_user = YELL_PS;
	shell->invite.color_cwd = BLUE_PS;
	shell->invite.color_reset = RESET;
	shell->prev_fd = -1;
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

int init_variable(t_shell *shell, int argc, char **argv, char **envp)
{
	int i;
	(void)argc;
	(void)argv;
	
	i = 0;
	bzero_shell(shell);
	while(envp[i] != NULL)	
	{
		if(init_env_lst (&shell->env, envp[i]) == ERROR)
			return(ERROR);
		i++;
	}
	return(0);
}
