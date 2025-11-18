/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 15:40:27 by aoesterl          #+#    #+#             */
/*   Updated: 2025/11/18 18:34:40 by aoesterl         ###   ########.fr       */
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

// volatile sig_atomic_t flag_signal = 0;



// void handle_sig_int(int sig)
// { 
// 	flag_signal = 1;
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


// void printbanner(void)
// {
// 	write_str(
// 		"					\033[1;33m        \\   |   /        \n"
// 		"					\033[1;33m          .-*-.\n"
// 		"					\033[1;33m     ☼  (  SUN  )  ☼    \033[95mWELCOME :)\n"
// 		"					\033[1;33m          `-*-´         \033[95mdans le ...\n"
// 		"					\033[1;37m    ´   .   ´   .   ´   .\n"
// 		"					\033[1;37m  .   ´    `   .   ´    `\n"
// 		"					\033[1;34m~~~~><(((º>~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
// 		"					\033[1;34m~~~~~~~~~~~~~    ⛵    ~~~~~><(((º>~~~~~~~\n"
// 		"					\033[1;34m~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
// 		"					\033[1;93m######### 🐚 ###############*##########*###\n"
// 		"					\033[1;93m######*############### 🐚 #####*###########\n"
// 		"					\033[1;95m       minishell de Arthur & Jeanne \n"
// 		"					\033[36m\n"
// 		"					\033[0m\n");
// }

// int main(int argc, char **argv, char **envp)
// { 
// 	t_shell shell;
	
// 	printbanner();
// 	init_signal(&shell.signal);
// 	if(init_variable(&shell, argc, argv, envp) == ERROR)
// 		free_exit(&shell, GEN_ERRNO, NULL);
// 	while(1)
// 	{
// 		flag_signal = 0;
// 		if(get_prompt(&shell, shell.env, &shell.invite) == ERROR)
// 			free_exit(&shell, GEN_ERRNO, NULL);
// 		shell.rd_line = readline(shell.invite.prompt);
// 		if(shell.rd_line == NULL)
// 			free_exit(&shell, GEN_ERRNO, NULL);
// 		if(flag_signal != 0)
// 			continue;
// 		if(*shell.rd_line != '\0')
// 			add_history(shell.rd_line);
// 		if(lexing(shell.rd_line, &shell.lst) == ERROR)
// 			free_exit(&shell, GEN_ERRNO, NULL);
// 		put_flags(shell.lst);
// 		if(expand_shell_param(&shell, shell.lst) == ERROR)
// 			free_exit(&shell, GEN_ERRNO, NULL);
// 		if(split_param(&shell, shell.lst, NULL) == ERROR)
// 			free_exit(&shell, GEN_ERRNO, NULL);
// 		if(delete_quotes(&shell, shell.lst) == ERROR)
// 			free_exit(&shell, GEN_ERRNO, NULL);
// 		if(logical_struct(&shell, NULL, shell.lst) == ERROR)
// 			free_exit(&shell, GEN_ERRNO, NULL);
// 		if (shell.cmd_lst)
// 			print_cmd_list(shell.cmd_lst);
// 		manage_execution(&shell, shell.env);


// 		free_all(&shell);
// 	}
// }



// // int main()
// // { 
// // 	while(1)
// // 	{ 
// // 			char *str;
// // 	str = "prout>";
// // 	readline(str);
// // 	rl_replace_line("", 0); // vide la ligne en cours
// //     rl_on_new_line();       // force readline à passer à une nouvelle ligne
// //     rl_redisplay();
// // 	write(1, "end", 3);
// // 	}

	
// // }

// #include <stdio.h>
// #include <stdlib.h>
// #include <signal.h>
// #include <readline/readline.h>
// #include <readline/history.h>
// #include <unistd.h>

// volatile sig_atomic_t flag_signal = 0;

// void handle_sigint(int sig)
// {
//     (void)sig;
//     flag_signal = 1;
//     write(1, "\n", 1);        // <- force nouvelle ligne
//     rl_replace_line("", 0);  // vide la ligne courante
//     rl_on_new_line();        // prépare readline pour la nouvelle ligne
//     rl_redisplay();          // réaffiche le prompt
// }

// int main(void)
// {
//     char *line;

//     signal(SIGINT, handle_sigint);

//     while (1)
//     {
//         flag_signal = 0;
//         line = readline("myshell> ");
//         if (!line) // Ctrl+D
//             break;
//         if (*line != '\0')
//             add_history(line);

//         if (flag_signal)
//         {
//             free(line);
//             continue; // signal reçu, ignore la ligne
//         }

//         printf("Vous avez tapé: %s\n", line);
//         free(line);
//     }

//     printf("Bye!\n");
//     return 0;
// }

