/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 19:18:46 by jdelattr          #+#    #+#             */
/*   Updated: 2025/12/02 20:10:36 by aoesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_not_a_dir(t_redir *redir)
{
	struct stat	st;

	st = (struct stat){0};
	stat(redir->filename, &st);
	if (S_ISDIR(st.st_mode) != 0)
	{
		write_str_fd("minishell: ", 2);
		write_str_fd(redir->filename, 2);
		write_str_fd(": Is a directory\n", 2);
		return (ERROR);
	}
	return (0);
}

void	routine_child_heredoc(t_shell *shell, char *delimit, int pipefd[2])
{
	int	check;

	close (pipefd[0]);
	if (delimit[0] == '"' || delimit[0] == '\'')
		check = here_doc_no_expand(delimit, pipefd);
	else
		check = here_doc_expand(shell, delimit, pipefd);
	close (pipefd[1]);
	free_exit (shell, check, NULL);
}

int	routine_parent_heredoc(t_shell *shell, pid_t pid_heredoc, int pipefd[2])
{
	set_ignore_sig(shell);
	close (pipefd[1]);
	wait_and_status(shell, pid_heredoc);
	if (shell->exit_status != 0)
		return (close(pipefd[0]), ERROR);
	return (0);
}

int	handle_heredoc(t_shell *shell, char *delimit)
{
	int		pipefd[2];
	pid_t	pid_heredoc;

	if (pipe(pipefd) == -1)
	{
		shell->exit_status = GEN_ERRNO;
		return (ERROR);
	}
	pid_heredoc = fork();
	if (pid_heredoc == ERROR)
	{
		shell->exit_status = GEN_ERRNO;
		return (close(pipefd[1]), close(pipefd[0]), ERROR);
	}
	if (pid_heredoc == 0)
	{
		set_heredoc_sig(shell);
		routine_child_heredoc(shell, delimit, pipefd);
	}
	if (pid_heredoc > 0)
	{
		if (routine_parent_heredoc(shell, pid_heredoc, pipefd) == ERROR)
			return (ERROR);
	}
	return (pipefd[0]);
}
