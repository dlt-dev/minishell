/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 15:40:27 by aoesterl          #+#    #+#             */
/*   Updated: 2025/11/27 12:51:33 by aoesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "Header/minishell.h"
// #include <unistd.h>
// #include <stdlib.h>
// #include <stdio.h>
// #include <errno.h>
// #include <readline/readline.h>
// #include <readline/history.h>
// #include <sys/types.h>
// #include <sys/stat.h>
// #include <fcntl.h>
// #include <sys/wait.h>

// #include "minishell.h"
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