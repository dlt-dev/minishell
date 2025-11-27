/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelattr <jdelattr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 15:40:27 by aoesterl          #+#    #+#             */
/*   Updated: 2025/11/27 18:22:23 by jdelattr         ###   ########.fr       */
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
#include <signal.h>

// #define SIGNAL -2
// volatile sig_atomic_t flag_signal = 0;

// void handle_sig_int(int sig)
// {
// 	(void)sig;
// 	flag_signal = 1;
// 	write(1, "\n", 1);
// 	rl_replace_line("", 0); // vide la ligne en cours
//     rl_on_new_line();       // force readline à passer à une nouvelle ligne
//     rl_redisplay(); // reaffiche le prompt
// }

// void init_signal(t_signal *signal)
// {
// 	*signal = (t_signal) {0};
// 	signal->sig_int.sa_handler = handle_sig_int;
// 	sigemptyset(&signal->sig_int.sa_mask);
// 	sigaction(SIGINT, &signal->sig_int, NULL);
// }
/* 
	(void) sig;
	flag_signal = 1;
	write(1 , "\n", 1); 
	rl_replace_line("", 0);
	rl_on_new_line(); 
	rl_redisplay(); */

// volatile sig_atomic_t flag_signal = 0;

// void handle_signal(int sig)
// {
// 	flag_signal = 1;
// 	printf("je suis le signal bouuuuuuuuuuuh *_*\n");

// 	(void) sig;

// 	write(1 , "\n", 1); 
// 	rl_replace_line("", 0);
// 	rl_on_new_line(); 
// 	rl_redisplay();

// }


// int main()
// {
// 	char *str;
// 	struct sigaction sigint;
// 	sigint = (struct sigaction){0};

// 	sigint.sa_handler = handle_signal;
// 	sigaction(SIGINT, &sigint, NULL );
	
// 	printf("le programme commence\n");
// 	while (1)
// 	{ 
// 		flag_signal = 0;
// 		printf("new_readline\n");
// 		str = readline("prout\n");
// 		if(flag_signal == 1)
// 			printf("j'ai la fibre\n");
// 		if(str == NULL)
// 			printf("mega prout\n");
// 	}

// 	return (0);
// }

#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <unistd.h>
#include <stdio.h>

volatile sig_atomic_t g_sig = 0;

void handle_sigint(int sig)
{
    g_sig = 128 + sig;
}

char *ms_readline(char *prompt)
{
	char *line = readline(prompt);
	printf("Hello\n");
	while (g_sig == SIGINT + 128)
	{
		g_sig = 0;
		free(line);
		rl_pending_input = '\n';
		line = readline(NULL);
		free(line);
		line = readline(prompt);
	}
	return (line);
}

int main()
{
	signal(SIGINT, &handle_sigint);
	rl_getc_function = getc;
    char *line = ms_readline("line>");
	while (line)
	{
		write(STDOUT_FILENO, line, strlen(line));
		write(STDOUT_FILENO, "\n", 1);
		free(line);
		line = ms_readline("line>");
	}
	return (0);
}


