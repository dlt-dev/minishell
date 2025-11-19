/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 15:40:27 by aoesterl          #+#    #+#             */
/*   Updated: 2025/11/19 15:32:32 by aoesterl         ###   ########.fr       */
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


#include "minishell.h"
#define SIGNAL -2
volatile sig_atomic_t flag_signal = 0;

void handle_sig_int(int sig)
{
	(void)sig; 
	flag_signal = 1;
	write(1, "\n", 1);
	rl_replace_line("", 0); // vide la ligne en cours
    rl_on_new_line();       // force readline à passer à une nouvelle ligne
    rl_redisplay(); // reaffiche le prompt 
}

void init_signal(t_signal *signal)
{ 
	*signal = (t_signal) {0};
	signal->sig_int.sa_handler = handle_sig_int;
	sigemptyset(&signal->sig_int.sa_mask);
	sigaction(SIGINT, &signal->sig_int, NULL);
}


int routine_heredoc(char *delimit, int pipefd[2])
{ 
	char *str;
	
	while(1)
	{
		str = readline(">");
		if(str == NULL)
		{ 
			if()

		}
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
 
int handle_heredoc(char *delimit, t_signal *signal)
{	
	int pipefd[2];
	int exit;

	pipe(pipefd);
	if (pipe(pipefd) == -1)
		return (perror("error pipe"), ERROR);

	pid_t pid;
	
	// if(flag_signal == 1)
	// 	return(ERROR);
	pid = fork();
	if(pid == ERROR)
		return(ERROR);
	if(pid == 0)
	{
		signal->sig_int.sa_handler = SIG_DFL;
		close(pipefd[0]);
		routine_heredoc(delimit, pipefd);
	}
	close(pipefd[1]);
	exit = waitpid_verify_status(pid);
	if(exit > 128)
	{
		close(pipefd[0]);
		return(exit);
	}
	// waitpid(pid, NULL, 0);
	close(pipefd[1]);
	return(pipefd[0]);
}


int main(int argc, char **argv)
{
	int retour;
	retour = 800;
	t_signal signal;
	init_signal(&signal);
	retour = handle_heredoc(argv[1], &signal);
	printf("l'exit est  : %d", retour);
}
