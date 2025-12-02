/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signaux.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelattr <jdelattr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 17:42:35 by aoesterl          #+#    #+#             */
/*   Updated: 2025/12/02 12:58:34 by jdelattr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_ignore_sig(t_shell *shell)
{
	shell->sigint.sa_handler = SIG_IGN;
	shell->sigquit.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &shell->sigquit, NULL);
	sigaction(SIGINT, &shell->sigint, NULL);
}

void	set_default_sig(t_shell *shell)
{
	shell->sigint.sa_handler = SIG_DFL;
	shell->sigquit.sa_handler = SIG_DFL;
	sigaction(SIGQUIT, &shell->sigquit, NULL);
	sigaction(SIGINT, &shell->sigint, NULL);
}

void	handle_sigint(int sig)
{
	g_flag_signal = sig + 128;
	write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	handle_shell_sig(t_shell *shell)
{
	shell->sigint.sa_handler = handle_sigint;
	shell->sigquit.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &shell->sigquit, NULL);
	sigaction(SIGINT, &shell->sigint, NULL);
}

void	sig_update_exit_status(t_shell *shell)
{
	if (g_flag_signal != 0)
	{
		shell->exit_status = g_flag_signal;
		g_flag_signal = 0;
	}
}
