/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_open_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 15:02:44 by jdelattr          #+#    #+#             */
/*   Updated: 2025/12/03 14:16:09 by aoesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	test_print_fd(t_exec *cmd_list) // TEST
// {
// 	int	i;

// 	i = 0;
// 	while (cmd_list != NULL)
// 	{
// 		printf("cmd[%d] ->> cmd fd_in = %d | fd_out = %d\n", i, cmd_list->fd_in,
// 			cmd_list->fd_out);
// 		i++;
// 		cmd_list = cmd_list->next;
// 	}
// }

int	open_infile(t_shell *shell, t_exec *current, t_redir *redir)
{
	int	fd_in;

	if (is_not_a_dir(redir) == ERROR)
	{
		shell->exit_status = GEN_ERRNO;
		return (ERROR);
	}
	fd_in = open(redir->filename, O_RDONLY);
	if (fd_in == ERROR)
	{
		shell->exit_status = GEN_ERRNO;
		return (print_error_message(NULL, redir->filename), ERROR);
	}
	if (current->fd_in != STDIN_FILENO)
		close(current->fd_in);
	current->fd_in = fd_in;
	return (0);
}

int	open_outfile(t_shell *shell, t_exec *current,
	t_redir *redir, int redir_type)
{
	int	fd_out;

	if (is_not_a_dir(redir) == ERROR)
	{
		shell->exit_status = GEN_ERRNO;
		return (ERROR);
	}
	if (redir_type == OUTFILE)
		fd_out = open(redir->filename, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (redir_type == OUTFILE_APPEND)
		fd_out = open(redir->filename, O_WRONLY | O_CREAT | O_APPEND, 0664);
	if (fd_out == ERROR)
	{
		shell->exit_status = GEN_ERRNO;
		return (print_error_message(NULL, redir->filename), ERROR);
	}
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
		return (ERROR);
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
			if (open_infile(shell, current, redir) == ERROR)
				return (ERROR);
		if (redir->redir_type == OUTFILE)
			if (open_outfile(shell, current, redir, OUTFILE) == ERROR)
				return (ERROR);
		if (redir->redir_type == HEREDOC)
			if (open_heredoc(shell, current, redir) == ERROR)
				return (ERROR);
		if (redir->redir_type == OUTFILE_APPEND)
			if (open_outfile(shell, current, redir, OUTFILE_APPEND) == ERROR)
				return (ERROR);
		redir = redir->next;
	}
	return (0);
}

int	check_all_redir(t_shell *shell)
{
	t_exec	*current;

	current = shell->cmd_lst;
	while (current != NULL)
	{
		if (check_cmd_redir(shell, current, current->redir) == ERROR)
			return (ERROR);
		else
			shell->exit_status = 0;
		current = current->next;
	}
	return (0);
}
