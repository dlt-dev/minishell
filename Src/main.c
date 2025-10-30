/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelattr <jdelattr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 14:04:25 by aoesterl          #+#    #+#             */
/*   Updated: 2025/10/29 11:09:09 by jdelattr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
 
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
	if(init_variable(&shell, argc, argv, envp) == ERROR)
		free_exit(&shell, GEN_ERRNO, NULL);
	while(1)
	{
		if(get_prompt(&shell.invite) == ERROR)
			free_exit(&shell, GEN_ERRNO, NULL);
		shell.rd_line = readline(shell.invite.prompt);
		if(shell.rd_line == NULL)
			free_exit(&shell, GEN_ERRNO, NULL);
		if(*shell.rd_line != '\0')
			add_history(shell.rd_line);
		if(lexing(shell.rd_line, &shell.lst) == ERROR)
			free_exit(&shell, GEN_ERRNO, NULL);
		// print_str_lst(shell.lst);
		put_flags(shell.lst);
		// print_str_lst(shell.lst);
		if(expand_shell_param(&shell, shell.lst) == ERROR)
			free_exit(&shell, GEN_ERRNO, NULL);
		print_str_lst(shell.lst);



/* 		if(logical_struct(shell.lst) == ERROR)
			free_exit(est ce que juste lst ou exec aussi ?) */



		// print_var_lst(shell.var.local);
		free_all(&shell);
		// free_exit(&shell, GEN_ERRNO, NULL);
	}
}

