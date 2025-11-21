/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Part8_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelattr <jdelattr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 19:18:46 by jdelattr          #+#    #+#             */
/*   Updated: 2025/11/21 14:28:05 by jdelattr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int routine_heredoc(char *delimit, int pipefd[2])
{ 
	char *str;
	
	close(pipefd[0]);
	while(1)
	{
		str = readline(">");
		if(str == NULL)
			break;
		if(ft_strlen(str) == ft_strlen(delimit) && ft_strcmp(str, delimit) == 0)
		{
			free(str);
			break;	
		}
		write(pipefd[1], str, ft_strlen(str));
		write(pipefd[1], "\n", 1);
		free(str);
	}
	close(pipefd[1]);
	exit(0);
}

int handle_heredoc(char *delimit)
{	
	int pipefd[2];

	pipe(pipefd);
	if (pipe(pipefd) == -1)
		return (perror("error pipe"), ERROR);

	pid_t pid_heredoc;
	pid_heredoc = fork();
	
	if(pid_heredoc == ERROR)
		return(ERROR);
	if(pid_heredoc == 0)
	{ 
		routine_heredoc(delimit, pipefd);
	}
	waitpid(pid_heredoc, NULL, 0);
	close(pipefd[1]);
	return(pipefd[0]);
}
