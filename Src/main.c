/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 14:04:25 by aoesterl          #+#    #+#             */
/*   Updated: 2025/11/18 18:58:37 by aoesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
 
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
// 	if(init_variable(&shell, argc, argv, envp) == ERROR)
// 		free_exit(&shell, GEN_ERRNO, NULL);
// 	while(1)
// 	{
// 		if(get_prompt(&shell, shell.env, &shell.invite) == ERROR)
// 			free_exit(&shell, GEN_ERRNO, NULL);
// 		shell.rd_line = readline(shell.invite.prompt);
// 		if(shell.rd_line == NULL)
// 			free_exit(&shell, GEN_ERRNO, NULL);
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


// 		//printf("variable path")
// 		//else
// 			//printf("une syntaxe error a ete detecte et la liste a ete free\n");

// 		// execution
		
// 		manage_execution(&shell, shell.env);


// 		free_all(&shell);
// 	}
// }

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


void printbanner(void)
{
	write_str(
		"					\033[1;33m        \\   |   /        \n"
		"					\033[1;33m          .-*-.\n"
		"					\033[1;33m     ☼  (  SUN  )  ☼    \033[95mWELCOME :)\n"
		"					\033[1;33m          `-*-´         \033[95mdans le ...\n"
		"					\033[1;37m    ´   .   ´   .   ´   .\n"
		"					\033[1;37m  .   ´    `   .   ´    `\n"
		"					\033[1;34m~~~~><(((º>~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
		"					\033[1;34m~~~~~~~~~~~~~    ⛵    ~~~~~><(((º>~~~~~~~\n"
		"					\033[1;34m~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
		"					\033[1;93m######### 🐚 ###############*##########*###\n"
		"					\033[1;93m######*############### 🐚 #####*###########\n"
		"					\033[1;95m       minishell de Arthur & Jeanne \n"
		"					\033[36m\n"
		"					\033[0m\n");
}

int main(int argc, char **argv, char **envp)
{ 
	t_shell shell;
	
	printbanner();
	init_signal(&shell.signal);
	if(init_variable(&shell, argc, argv, envp) == ERROR)
		free_exit(&shell, GEN_ERRNO, NULL);
	while(1)
	{
		if(get_prompt(&shell, shell.env, &shell.invite) == ERROR)
			free_exit(&shell, GEN_ERRNO, NULL);
		if(flag_signal == 0)	
			shell.rd_line = readline(shell.invite.prompt);
		if(shell.rd_line == NULL)
			free_exit(&shell, GEN_ERRNO, NULL);
		if(flag_signal != 0)
			flag_signal = 0;
		if(*shell.rd_line != '\0')
			add_history(shell.rd_line);
		if(lexing(shell.rd_line, &shell.lst) == ERROR)
			free_exit(&shell, GEN_ERRNO, NULL);
		put_flags(shell.lst);
		if(expand_shell_param(&shell, shell.lst) == ERROR)
			free_exit(&shell, GEN_ERRNO, NULL);
		if(split_param(&shell, shell.lst, NULL) == ERROR)
			free_exit(&shell, GEN_ERRNO, NULL);
		if(delete_quotes(&shell, shell.lst) == ERROR)
			free_exit(&shell, GEN_ERRNO, NULL);
		if(logical_struct(&shell, NULL, shell.lst) == ERROR)
			free_exit(&shell, GEN_ERRNO, NULL);
		if (shell.cmd_lst)
			print_cmd_list(shell.cmd_lst);
		manage_execution(&shell, shell.env);
		free_all(&shell);
	}
}
