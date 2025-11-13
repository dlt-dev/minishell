/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 16:55:18 by aoesterl          #+#    #+#             */
/*   Updated: 2025/11/13 20:42:33 by aoesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



int builtin_echo(char **args, int fd_out)
{ 
	int i;
	int flag_n;

	flag_n = 0;
	i = 1;
	if(args[1] == NULL)		
		return(write(fd_out, "\n", 1), 0);
	while(args[i] != NULL && ft_strcmp(args[i], "-n") == 0)
	{
		flag_n = 1;
		i++;
	}
	while(args[i] != NULL)
	{ 
		write(fd_out , args[i], ft_strlen(args[i]));
		write(fd_out , " ", 1);
		i++; 
	}
	if(flag_n == 0)
		write(fd_out, "\n", 1);
	return(0);
}
