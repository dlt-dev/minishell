/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelattr <jdelattr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 14:04:25 by aoesterl          #+#    #+#             */
/*   Updated: 2025/12/02 12:55:39 by jdelattr         ###   ########.fr       */
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

volatile sig_atomic_t	g_flag_signal = 0;

int	shell_mode(t_shell *shell)
{
	if (isatty(0) == 0)
	{
		if (non_interactive_shell(shell) == ERROR)
			return (ERROR);
	}
	else
		interactive_shell(shell);
	return (0);
}

int	command_line_processing(t_shell *shell)
{
	if (lexing(shell->rd_line, &shell->lst) == ERROR)
		return (ERROR);
	put_flags(shell->lst);
	if (main_expand(shell, shell->lst) == ERROR)
		return (ERROR);
	if (split_param(shell, shell->lst, NULL) == ERROR)
		return (ERROR);
	if (delete_quotes(shell, shell->lst) == ERROR)
		return (ERROR);
	return (0);
}

int	execution(t_shell *shell)
{
	if (logical_struct(shell, NULL, shell->lst) == ERROR)
		return (ERROR);
	if (check_all_redir(shell) == ERROR)
		free_all(shell);
	else
		manage_execution(shell, shell->env);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	printbanner();
	if (init_variable(&shell, argc, argv, envp) == ERROR)
		free_exit(&shell, GEN_ERRNO, NULL);
	handle_shell_sig(&shell);
	while (1)
	{
		if (shell_mode(&shell) == ERROR)
			free_exit(&shell, GEN_ERRNO, NULL);
		if (command_line_processing(&shell) == ERROR)
			free_exit(&shell, GEN_ERRNO, NULL);
		execution(&shell);
		free_all(&shell);
	}
}

// if (isatty(0) == 0)
// {
// 	if (non_interactive_shell(&shell) == ERROR)
// 		free_exit(&shell, shell.exit_status, NULL);
// }
// else
// 	interactive_mode(&shell);
// if (lexing(shell.rd_line, &shell.lst) == ERROR)
// 	free_exit(&shell, GEN_ERRNO, NULL);
// put_flags(shell.lst);
// if (main_expand(&shell, shell.lst) == ERROR)
// 	free_exit(&shell, GEN_ERRNO, NULL);
// if (split_param(&shell, shell.lst, NULL) == ERROR)
// 	free_exit(&shell, GEN_ERRNO, NULL);
// if (delete_quotes(&shell, shell.lst) == ERROR)
// free_exit(&shell, GEN_ERRNO, NULL);
// if (logical_struct(&shell, NULL, shell.lst) == ERROR)
// 	free_exit(&shell, GEN_ERRNO, NULL);
// if (check_all_redir(&shell) == ERROR)
// 	free_all(&shell);
// else
// 	manage_execution(&shell, shell.env);

// si stdin n'est pas in tty le shell doit :
/**
 * @brief ne aps afficher de prompt, ne pas utiliser readline,
	utiliser get_nextline, executer chaque ligne
 * s'arrtertetr quand il n'y a plus de ligne,
	quitter avec le statu du dernier pipeline
 *
 * si stdout n'(est pas un tty,
	le minioshell doit afficher un prompt car stdin est un tty
 * mais en pas envoyer de couleur ou de trucs interactif,
	toute la sortie part dans le fichier, readline
 * fonctionne normalement et les signaux aussi
 *
 * cas : not a tty stdin et stdout ( ex: pipe). dans le premier
 *
 */