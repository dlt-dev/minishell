/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 19:18:46 by jdelattr          #+#    #+#             */
/*   Updated: 2025/11/27 13:02:59 by aoesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	routine_heredoc(t_shell *shell, char *delimit, int pipefd[2])
{
	int	check;

	close(pipefd[0]);
	if (delimit[0] == '"' || delimit[0] == '\'')
		check = here_doc_no_expand(delimit, pipefd);
	else
		check = here_doc_expand(shell, delimit, pipefd);
	close(pipefd[1]);
	free_exit(shell, check, NULL);
}

int	handle_heredoc(t_shell *shell, char *delimit)
{
	int		pipefd[2];
	pid_t	pid_heredoc;

	if (pipe(pipefd) == -1)
		return (ERROR);
	pid_heredoc = fork();
	if (pid_heredoc == ERROR)
		return (close(pipefd[1]), close(pipefd[0]), GEN_ERRNO);
	if (pid_heredoc == 0)
	{
		routine_heredoc(shell, delimit, pipefd);
	}
	if (pid_heredoc > 0)
	{
		close(pipefd[1]);
		wait_and_status(shell, pid_heredoc);
	}
	return (pipefd[0]);
}

// clean maintenant
