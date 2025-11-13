/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Part8_open_redir.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 15:02:44 by jdelattr          #+#    #+#             */
/*   Updated: 2025/11/13 18:35:17 by aoesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/////////////////////////////////////
/// @fonctions open_and_find_redir.c ///
////////////////////////////////////

int	open_infile(t_exec *current, t_redir *redir)
{
	int	fd_in;

	fd_in = open(redir->filename, O_RDONLY);
	if (fd_in < 0)
	{
		printf("%s : no such file or directory\n", redir->filename);
		return (ERROR);
	}
	if (current->fd_in != STDIN_FILENO)
		close(current->fd_in);
	current->fd_in = fd_in;
	return (0);
}

int	open_outfile(t_exec *current, t_redir *redir, int redir_type)
{
	int	fd_out;

	if (redir_type == OUTFILE)
		fd_out = open(redir->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (redir_type == OUTFILE_APPEND)
		fd_out = open(redir->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd_out < 0)
	{
		printf("%s : impossible to access\n", redir->filename);
		return (ERROR);
	}
	if (current->fd_out != STDOUT_FILENO)
		close(current->fd_out);
	current->fd_out = fd_out;
	return (0);
}

int	open_heredoc(t_exec *current, t_redir *redir)
{
	int	fd_in;

	fd_in = handle_heredoc(redir->filename);
	if (fd_in < 0)
	{
		printf("error : impossible to find your heredoc\n");
		return (ERROR);
	}
	if (current->fd_in != STDIN_FILENO)
		close(current->fd_in);
	current->fd_in = fd_in;
	return (0);
}

int	check_cmd_redir(t_exec *current, t_redir *redir)
{
	while (redir != NULL)
	{
		if (redir->redir_type == INFILE)
			if (open_infile(current, redir) == ERROR)
				return (ERROR);
		if (redir->redir_type == OUTFILE)
			if (open_outfile(current, redir, OUTFILE) == ERROR)
				return (ERROR);
		if (redir->redir_type == HEREDOC)
			if (open_heredoc(current, redir) == ERROR)
				return (ERROR);
		if (redir->redir_type == OUTFILE_APPEND)
			if (open_outfile(current, redir, OUTFILE_APPEND) == ERROR)
				return (ERROR);
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
		check_cmd_redir(current, current->redir);
		current = current->next;
	}
	return (0);
}
