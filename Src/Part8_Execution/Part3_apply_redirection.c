/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Part3_apply_redirection.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 21:23:53 by jdelattr          #+#    #+#             */
/*   Updated: 2025/11/26 20:48:14 by aoesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redir_in_pipe(t_shell *shell, t_exec *current)
{
	int	prev_fd;

	prev_fd = shell->prev_fd;
	if (current->fd_in != STDIN_FILENO)
	{
		if (dup2(current->fd_in, STDIN_FILENO) == ERROR)
			return (GEN_ERRNO);
		close(current->fd_in);
	}
	else if (prev_fd != -1)
	{
		if (dup2(prev_fd, STDIN_FILENO) == ERROR)
			return (GEN_ERRNO);
		close(prev_fd);
	}
	return (0);
}

int	redir_out_pipe(t_exec *current, int pipe_fd[2])
{
	if (current->fd_out != STDOUT_FILENO)
	{
		if (dup2(current->fd_out, STDOUT_FILENO) == ERROR)
			return (GEN_ERRNO);
		close(current->fd_out);
	}
	else if (current->next)
	{
		if (dup2(pipe_fd[1], STDOUT_FILENO) == ERROR)
			return (GEN_ERRNO);
	}
	return (0);
}

int	apply_redir_pipe(t_shell *shell, t_exec *current, int pipe_fd[2])
{
	if (redir_in_pipe(shell, current) == ERROR)
		return (close(pipe_fd[0]), close(pipe_fd[1]), GEN_ERRNO);
	if (redir_out_pipe(current, pipe_fd) == ERROR)
		return (close(pipe_fd[0]), close(pipe_fd[1]), GEN_ERRNO);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	return (0);
}
