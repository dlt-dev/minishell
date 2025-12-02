/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interactive.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 01:26:48 by aoesterl          #+#    #+#             */
/*   Updated: 2025/12/02 04:08:49 by aoesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	interactive_shell(t_shell *shell)
{
	if (get_prompt(shell, shell->env, &shell->invite) == ERROR)
		free_exit(shell, GEN_ERRNO, NULL);
	if (isatty(0) == 1 && isatty(1) == 1)
		shell->rd_line = readline(shell->invite.prompt);
	else
	{
		shell->rd_line = get_next_line(STDIN_FILENO);
	}
	sig_update_exit_status(shell);
	if (shell->rd_line == NULL)
		free_exit(shell, shell->exit_status, NULL);
	if (*(shell->rd_line) != '\0')
		add_history(shell->rd_line);
}
