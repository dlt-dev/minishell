/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   retry_cmd_struc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 14:40:34 by aoesterl          #+#    #+#             */
/*   Updated: 2025/11/13 15:57:51 by aoesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int add_last_command(t_exec *current, char** new_args, char *cmd, int i)
{ 
	new_args[i] = ft_strdup(cmd);
	if(new_args[i] == NULL)
		return(ERROR);
	new_args[i + 1] = NULL;
	free(current->cmds);
	current->cmds = new_args;
	return(0);
}

int	add_arg_command(t_exec *current, char *cmd)
{
	int		i;
	int		j;
	char	**new_args;

	i = 0;
	j = 0; 
	if (current->cmds != NULL)
	{ 
		while (current->cmds[i] != NULL)
			i++;
	}
	new_args = malloc(sizeof(char *) * (i + 2));
	if (new_args == NULL)
		return (ERROR);
	while (j < i)
	{
		new_args[j] = current->cmds[j];
		j++;
	}
	if(add_last_command(current, new_args, cmd, i) == ERROR)
		return(ft_free_split(&new_args), ERROR);
	return (0);
}
