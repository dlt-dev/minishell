/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 16:55:18 by aoesterl          #+#    #+#             */
/*   Updated: 2025/11/14 15:19:26 by aoesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_option_n(char *str)
{ 
	int i;

	i = 1;
	while(str[i] != '\0')
	{ 
		if(i == 0)
		{ 
			if(str[0] != '-')
				return(ERROR);		
		}
		else
		{ 
			if(str[i] != 'n')
				return(ERROR);
		}
		i++;
	}
	return(0);
}


int builtin_echo(char **args, int fd_out)
{ 
	int i;
	int opt_n;

	opt_n = 0;
	i = 1;
	if(args[1] == NULL)		
		return(write(fd_out, "\n", 1), 0);
	while(args[i] != NULL && is_option_n(args[i]) == 0)
	{
		opt_n = 1;
		i++;
	}
	while(args[i] != NULL)
	{ 
		write(fd_out , args[i], ft_strlen(args[i]));
		write(fd_out , " ", 1);
		i++; 
	}
	if(opt_n == 0)
		write(fd_out, "\n", 1);
	return(0);
}



// all test good