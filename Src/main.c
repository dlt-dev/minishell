/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 14:04:25 by aoesterl          #+#    #+#             */
/*   Updated: 2025/11/27 21:03:18 by aoesterl         ###   ########.fr       */
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

void handle_sigint(int sig)
{
	flag_signal = sig + 128;
}
static void handle_pending_signal_in_prompt(t_shell *shell)
{
    if (flag_signal == 0)
        return;
    if (flag_signal == SIGINT)
    {
        shell->exit_status = 130;
    }
    else if (flag_signal == SIGQUIT)
    {
        shell->exit_status = 131;
    }
    flag_signal = 0;
    /* regénérer le prompt avec le nouvel exit_status */
    if (get_prompt(shell, shell->env, &shell->invite) == ERROR)
        return;
    /* réafficher la nouvelle ligne avec le bon prompt */
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}
int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;
	
	struct sigaction sigint;
	struct sigaction sigquit;
	
	sigint = (struct sigaction){0};
	sigquit = (struct sigaction){0};

	sigint.sa_handler = handle_sigint;
	sigquit.sa_handler = SIG_IGN;

	sigaction(SIGQUIT, &sigquit, NULL);
	sigaction(SIGINT, &sigint, NULL);

	printbanner();
	if (init_variable(&shell, argc, argv, envp) == ERROR)
		free_exit(&shell, GEN_ERRNO, NULL);
	while (1)
	{	
		get
		while(flag_signal != 0)
		{ 
			if (get_prompt(&shell, shell.env, &shell.invite) == ERROR)
			free_exit(&shell, GEN_ERRNO, NULL);
			shell.rd_line = readline(shell.invite.prompt);
			
		}
		if (get_prompt(&shell, shell.env, &shell.invite) == ERROR)
			free_exit(&shell, GEN_ERRNO, NULL);
		shell.rd_line = readline(shell.invite.prompt);
        if (flag_signal != 0)
        {
            handle_pending_signal_in_prompt(&shell);
            if (shell.rd_line)
            {
                free(shell.rd_line);
                shell.rd_line = NULL;
            }
            continue;
        }
		if (shell.rd_line == NULL)
			free_exit(&shell, GEN_ERRNO, NULL);
		if (*shell.rd_line != '\0')
			add_history(shell.rd_line);
		if (lexing(shell.rd_line, &shell.lst) == ERROR)
			free_exit(&shell, GEN_ERRNO, NULL);
		put_flags(shell.lst);
		if (expand_shell_param(&shell, shell.lst) == ERROR)
			free_exit(&shell, GEN_ERRNO, NULL);
		if (split_param(&shell, shell.lst, NULL) == ERROR)
			free_exit(&shell, GEN_ERRNO, NULL);
		if (delete_quotes(&shell, shell.lst) == ERROR)
			free_exit(&shell, GEN_ERRNO, NULL);
		if (logical_struct(&shell, NULL, shell.lst) == ERROR)
			free_exit(&shell, GEN_ERRNO, NULL);c
		if (shell.cmd_lst)
			print_cmd_list(shell.cmd_lst);
		if (check_all_redir(&shell) == ERROR)
			free_all(&shell);
		else
			manage_execution(&shell, shell.env);
		free_all(&shell);
	}
}
