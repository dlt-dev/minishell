/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_sig.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 03:04:12 by aoesterl          #+#    #+#             */
/*   Updated: 2025/12/02 03:07:31 by aoesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_sigint_heredoc(int sig)
{
	flag_signal = sig + 128;
	close(STDIN_FILENO);
}

void	set_heredoc_sig(t_shell *shell)
{
	shell->sigint.sa_handler = handle_sigint_heredoc;
	shell->sigquit.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &shell->sigquit, NULL);
	sigaction(SIGINT, &shell->sigint, NULL);
}