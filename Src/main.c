/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 14:04:25 by aoesterl          #+#    #+#             */
/*   Updated: 2025/12/01 13:46:37 by aoesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"



void	printbanner(void)
{
	write_str_fd("\033[1;33m        \\   |   /        \n"
		"\033[1;33m          .-*-.\n"
		"\033[1;33m     ☼  (  SUN  )  ☼    \033[95mWELCOME :)\n"
		"\033[1;33m          `-*-´         \033[95mdans le ...\n"
		"\033[1;37m    ´   .   ´   .   ´   .\n"
		"\033[1;37m  .   ´    `   .   ´    `\n"
		"\033[1;34m~~~~><(((º>~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
		"\033[1;34m~~~~~~~~~~~~~    ⛵    ~~~~~><(((º>~~~~~~~\n"
		"\033[1;34m~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
		"\033[1;93m######### 🐚 ###############*##########*###\n"
		"\033[1;93m######*############### 🐚 #####*###########\n"
		"\033[1;95m       minishell de Arthur & Jeanne \n"
		"\033[36m\n"
		"\033[0m\n",
		1);
}


volatile sig_atomic_t flag_signal = 0;

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;
	// printbanner();

	if (init_variable(&shell, argc, argv, envp) == ERROR)
		free_exit(&shell, GEN_ERRNO, NULL);
	handle_shell_sig (&shell);
	while (1)
	{
		if(isatty(0) == 0)
		{
			if(non_interactive_shell(&shell) == ERROR)
				free_exit(&shell, shell.exit_status, NULL);
		}
		else 
		{
			interactive_mode(&shell);
		// if (get_prompt(&shell, shell.env, &shell.invite) == ERROR)
		// 	free_exit(&shell, GEN_ERRNO, NULL);
		// shell.rd_line = readline(shell.invite.prompt);
		// sig_update_exit_status(&shell);
		// if (shell.rd_line == NULL)
		// 	free_exit(&shell, shell.exit_status, NULL);
		// if (*shell.rd_line != '\0')
		// 	add_history(shell.rd_line);
		}
		if (lexing(shell.rd_line, &shell.lst) == ERROR)
			free_exit(&shell, GEN_ERRNO, NULL);
		put_flags(shell.lst);

		if (main_expand(&shell, shell.lst) == ERROR)// appeler main_expand()
			free_exit(&shell, GEN_ERRNO, NULL);

		if (split_param(&shell, shell.lst, NULL) == ERROR)
			free_exit(&shell, GEN_ERRNO, NULL);
		if (delete_quotes(&shell, shell.lst) == ERROR)
			free_exit(&shell, GEN_ERRNO, NULL);
		if (logical_struct(&shell, NULL, shell.lst) == ERROR)
			free_exit(&shell, GEN_ERRNO, NULL);
		//if (shell.cmd_lst)
			//print_cmd_list(shell.cmd_lst);
		if (check_all_redir(&shell) == ERROR)
			free_all(&shell);
		else
			manage_execution(&shell, shell.env);
		free_all(&shell);
	}
}


// si stdin n'est pas in tty le shell doit : 
/**
 * @brief ne aps afficher de prompt, ne pas utiliser readline, utiliser get_nextline, executer chaque ligne
 * s'arrtertetr quand il n'y a plus de ligne, quitter avec le statu du dernier pipeline 
 * 
 * si stdout n'(est pas un tty, le minioshell doit afficher un prompt car stdin est un tty
 * mais en pas envoyer de couleur ou de trucs interactif, toute la sortie part dans le fichier, readline
 * fonctionne normalement et les signaux aussi
 * 
 * cas : not a tty stdin et stdout ( ex: pipe). dans le premier 
 * 
 */