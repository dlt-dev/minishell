/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 14:04:25 by aoesterl          #+#    #+#             */
/*   Updated: 2025/10/15 20:05:28 by aoesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void printbanner(void)
{
	write_str(
		"\033[33m        \\   |   /        \n"
		"\033[33m          .-*-.\n"
		"\033[33m     ☼  (  SUN  )  ☼    \033[95mWELCOME :)\n"
		"\033[33m          `-*-´         \033[95mdans le ...\n"
		"\033[37m    ´   .   ´   .   ´   .\n"
		"\033[37m  .   ´    `   .   ´    `\n"
		"\033[34m~~~~><(((º>~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
		"\033[34m~~~~~~~~~~~~~    ⛵    ~~~~~><(((º>~~~~~~~\n"
		"\033[34m~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
		"\033[93m######### 🐚 ###############*##########*###\n"
		"\033[93m######*############### 🐚 #####*###########\n"
		"\033[1;95m       minishell de Arthur & Jeanne \n"
		"\033[36m\n"
		"\033[0m\n");
}

void bzero_shell(t_shell *shell)
{ 
	*shell = (t_shell){0};
	shell->invite.color_user = YELL_PS;
	shell->invite.color_cwd = BLUE_PS;
	shell->invite.color_reset = RESET;
}

int create_var_lst(t_valist *env, char *envp)
{ 
	int i;
	int len;
	char *name;
	char *value;
	
	len = len_name(envp);
	i = len + 1;
	name = ft_strndup(envp, len);
	if(name == NULL)
		return(ERROR);
	len = ft_strlen(envp) - i; 
	value = ft_strndup(&envp[i], len);
	if(value == NULL)
		return(free(name), NULL);
	var_in_lst()
	
}


int init_shell(t_shell *shell, int argc, char **argv, char **envp)
{
	char *tmp;
	int i;
	(void)argc;
	(void)argv;
	
	i = 0;
	bzero_shell(shell);
	while(envp[i] != NULL)	
	{
		create_var_lst (shell->var.env, envp[i]);
	}
	return(0);
}

 
int main(int argc, char **argv, char **envp)
{ 
	t_shell shell;
	
	printbanner();
	if(init_shell(&shell, argc, argv, envp) == ERROR)
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
		print_str_lst(shell.var.env);
		free_all(&shell);
	}
}

