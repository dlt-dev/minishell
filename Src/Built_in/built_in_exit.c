/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 16:57:16 by aoesterl          #+#    #+#             */
/*   Updated: 2025/11/25 17:48:36 by aoesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int check_number(char *str)
{ 
	int i;

	i = 0;
	if (str[0] == '\0')
		return(ERROR);

	if(str[0] == '-' || str[0] == '+')
	{
		i++;
		if(str[i] == '\0')
			return(ERROR);
	}
	while(str[i] != '\0')
	{
		if(str[i] < '0' || str[i] > '9')
			return(ERROR);
		i++;
	}
	return(0);
}

void builtin_exit(t_shell *shell, char **args)
{
	int i;

	i = 0;

	while(args[i] != NULL)
		i++;


	if (i == 1)
		free_exit(shell, shell->exit_status, "exit");	
	if(check_number(args[1]) == ERROR)
	{ 
		write_str_fd("minishell: exit: numeric argument required\n", 2);
		free_exit(shell, 2 , NULL);
	}
	else
	{
		shell->exit_status = (ft_atoi(args[1]));
		write_str_fd("exit\n", 2);
		free_exit(shell, shell->exit_status, NULL);
	}

	if (i > 2)
	{ 
		write_str_fd("minishell: exit: too many arguments", 2);
		shell->exit_status = GEN_ERRNO;
		
	}

}