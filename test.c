/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelattr <jdelattr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 15:40:27 by aoesterl          #+#    #+#             */
/*   Updated: 2025/11/20 14:59:45 by jdelattr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Header/minishell.h"
#include <unistd.h> 
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>

int main()
{
	pid_t pid;
	pid = fork();

	if (pid > 0)
	{
		printf("je suis le pere\n");
	}
}

int waitpid_verify_status (pid_t pid)
{ 
	int status;
		
	waitpid(pid, &status, 0);
	if(WIFEXITED(status) != 0)
		return(WEXITSTATUS(status));
	if(WIFSIGNALED(status) != 0)
		return(WTERMSIG(status) + 128);
	return(0);
}

int	wait_and_status(pid_t last_pid)
{
	int status;
	pid_t pid_childs;
	pid_t last_pid;

	waitpid(last_pid, &status, 0);
	shel

	while ( waitpid(-1, 0, 0) != ERROR)
		continue ;
	return (status);
}