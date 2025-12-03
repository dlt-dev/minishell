/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Part2_B_routine_simple_cmd.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 13:21:20 by aoesterl          #+#    #+#             */
/*   Updated: 2025/12/03 15:47:21 by aoesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redir_one_command(t_shell *shell)
{
	int	fd_in;
	int	fd_out;

	fd_in = shell->cmd_lst->fd_in;
	fd_out = shell->cmd_lst->fd_out;
	if (fd_in != STDIN_FILENO)
	{
		if (dup2(fd_in, STDIN_FILENO) == ERROR)
			return (GEN_ERRNO);
		close(fd_in);
	}
	if (fd_out != STDOUT_FILENO)
	{
		if (dup2(fd_out, STDOUT_FILENO) == ERROR)
			return (GEN_ERRNO);
		close(fd_out);
	}
	return (0);
}

void	routine_child(t_shell *shell, char **cmd, t_valist *env)
{
	int	exit_status;
	
	if(check_cmd_redir(shell, shell->cmd_lst, shell->cmd_lst->redir) == ERROR)
		free_exit(shell, shell->exit_status, NULL);
	shell->exit_status = 0;
	if (redir_one_command(shell) == GEN_ERRNO)
		free_exit(shell, GEN_ERRNO, NULL);
	exit_status = do_execve(cmd, env);
	free_exit(shell, exit_status, NULL);
}

int	exec_fork_one(t_shell *shell, char **cmd, t_valist *env)
{
	pid_t	child;

	child = fork();
	if (child == ERROR)
		return (ERROR);
	if (child == 0)
	{
		set_default_sig(shell);
		routine_child(shell, cmd, env);
	}
	set_ignore_sig(shell);
	wait_and_status(shell, child);
	return (0);
}
// print_char_tab(env_tab_exe); TEST PRINT
// print_char_tab(cmd); TEST PRINT