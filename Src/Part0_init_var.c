/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Part0_init_var.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 00:00:39 by aoesterl          #+#    #+#             */
/*   Updated: 2025/10/16 00:28:18 by aoesterl         ###   ########.fr       */
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

void bzero_shell(t_shell *shell)
{ 
	*shell = (t_shell){0};
	shell->invite.color_user = YELL_PS;
	shell->invite.color_cwd = BLUE_PS;
	shell->invite.color_reset = RESET;
}

int init_env_lst(t_valist **env, char *envp)
{ 
	int i;
	int size_name;
    int size_value;
	char *name;
	char *value;
	
	size_name = len_name(envp);
    name = ft_strndup(envp, size_name);
	i = size_name;
    i++;
	if(name == NULL)
		return(ERROR);
	size_value = ft_strlen(envp) - i; 
	value = ft_strndup(&envp[i], size_value);
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
		if(init_env_lst (&shell->var.env, envp[i]) == ERROR)
			ft_free_var(&shell->var.env);
		i++;
	}
	return(0);
}
