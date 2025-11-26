/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Part1_open_redir.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 15:02:44 by jdelattr          #+#    #+#             */
/*   Updated: 2025/11/26 21:02:22 by aoesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_infile(t_exec *current, t_redir *redir)
{
	int	fd_in;

	fd_in = open(redir->filename, O_RDONLY);
	if (fd_in == ERROR)
		return (print_error_message(NULL, redir->filename), GEN_ERRNO);
	if (current->fd_in != STDIN_FILENO)
		close(current->fd_in);
	current->fd_in = fd_in;
	return (0);
}

int	open_outfile(t_exec *current, t_redir *redir, int redir_type)
{
	int	fd_out;

	if (redir_type == OUTFILE)
		fd_out = open(redir->filename, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (redir_type == OUTFILE_APPEND)
		fd_out = open(redir->filename, O_WRONLY | O_CREAT | O_APPEND, 0664);
	if (fd_out == ERROR)
		return (print_error_message(NULL, redir->filename), GEN_ERRNO);
	if (current->fd_out != STDOUT_FILENO)
		close(current->fd_out);
	current->fd_out = fd_out;
	return (0);
}

int	open_heredoc(t_shell *shell, t_exec *current, t_redir *redir)
{
	int	fd_in;

	fd_in = handle_heredoc(shell, redir->filename);
	if (fd_in == ERROR)
		return (print_error_message("heredoc", NULL), GEN_ERRNO);
	if (current->fd_in != STDIN_FILENO)
		close(current->fd_in);
	current->fd_in = fd_in;
	return (0);
}

int	check_cmd_redir(t_shell *shell, t_exec *current, t_redir *redir)
{
	while (redir != NULL)
	{
		if (redir->redir_type == INFILE)
			if (open_infile(current, redir) == GEN_ERRNO)
				return (GEN_ERRNO);
		if (redir->redir_type == OUTFILE)
			if (open_outfile(current, redir, OUTFILE) == GEN_ERRNO)
				return (GEN_ERRNO);
		if (redir->redir_type == HEREDOC)
			if (open_heredoc(shell, current, redir) == GEN_ERRNO)
				return (GEN_ERRNO);
		if (redir->redir_type == OUTFILE_APPEND)
			if (open_outfile(current, redir, OUTFILE_APPEND) == GEN_ERRNO)
				return (GEN_ERRNO);
		redir = redir->next;
	}
	return (0);
}

int	check_all_redir(t_shell *shell) // pour chaques nodes cmd, je check toutes les redirs et trouve in et out
{
	t_exec *current;
	current = shell->cmd_lst;
	while (current != NULL)
	{
		if(check_cmd_redir(shell, current, current->redir) == GEN_ERRNO)
		{ 
			shell->exit_status = GEN_ERRNO; 
			return(ERROR);
		}
		current = current->next;
	}
	return (0);
}
