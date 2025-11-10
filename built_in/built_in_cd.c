/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 16:56:31 by aoesterl          #+#    #+#             */
/*   Updated: 2025/11/10 17:01:25 by aoesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_cd(char **argv)
{
	int i;
	char *path;
	char *message;

	message = "too many arguments";
	i = 1;
	while(argv[i] != NULL)
		i++;
	if(i > 2)
	{ 
		write(1, message, ft_strlen(message));
		message = "too many arguments";
		return(GEN_ERRNO);
	}	
	if(chdir(argv[1]) == ERROR)
	{ 
		perror(argv[1]);	
		return(GEN_ERRNO);
	}
	else
		printf("%s\n", getcwd(NULL, 0));
	return(0);
}