/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 14:04:25 by aoesterl          #+#    #+#             */
/*   Updated: 2025/11/07 19:57:52 by aoesterl         ###   ########.fr       */
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

void ft_env(t_valist *env)
{	
	while(env != NULL)
	{ 	
		write(1, env->name, ft_strlen(env->name));
		write(1, "=", 1);
		write(1 , env->value, ft_strlen(env->value));
		write(1, "\n", 1);
		env = env->next;
	}
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
		put_flags(shell.lst);
		// print_str_lst(shell.lst);
		if(expand_shell_param(&shell, shell.lst) == ERROR)
			free_exit(&shell, GEN_ERRNO, NULL);
		if(split_param(&shell, shell.lst, NULL) == ERROR)
			free_exit(&shell, GEN_ERRNO, NULL);
		if(delete_quotes(&shell, shell.lst) == ERROR)
			free_exit(&shell, GEN_ERRNO, NULL);
		ft_env(shell.env);
		// print_str_lst(shell.lst);
		// logical_struct(&shell, shell.lst);
		// if (shell.cmd_lst)
		// 	print_cmd_list(shell.cmd_lst);
		// else
		// 	printf("une syntaxe error a ete detecte et la liste a ete free\n");

		// execution

		// manage_execution(&shell, shell.env);





		free_all(&shell);
	}
}

/* 		if(logical_struct(&shell, shell.lst) == ERROR)
			free_exit(&shell, GEN_ERRNO, NULL); */