/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 16:55:18 by aoesterl          #+#    #+#             */
/*   Updated: 2025/11/10 17:00:50 by aoesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_echo(char **args)
{ 
	int i;
	int flag_n;

	flag_n = 0;
	i = 1;
	while(ft_strcmp(args[i], "-n") == 0)
	{
		flag_n = 1;
		i++;
	}
	while(args[i] != NULL)
	{ 
		write(1 , args[i], ft_strlen(args[i]));
		write(1 , " ", 1);
		i++; 
	}
	if(flag_n == 0)
		write(1, "\n", 1);
}