/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Part1_exec_main.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 19:45:02 by aoesterl          #+#    #+#             */
/*   Updated: 2025/11/26 19:45:10 by aoesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int waitpid_verify_status (pid_t pid)
{ 
	int status;
		
	waitpid(pid, &status, 0);
	if(WIFEXITED(status) != 0)
		return(WEXITSTATUS(status));
	if(WIFSIGNALED(status) != 0)
		return(WTERMSIG(status) + 128);
	return(0);
}

int	wait_and_status(t_shell *shell, pid_t last_pid)
{
	shell->exit_status = waitpid_verify_status(last_pid);
	while (waitpid(-1, 0, 0) != ERROR)
		continue ;
	return (0);
}

int	handle_simple_command(t_shell *shell, t_exec *cmd_lst, t_valist *env) // CAS DE LA COMMANDE UNIQUE
{
	if (cmd_lst->cmds[0] && (is_built_in(cmd_lst->cmds[0]) != 0))
	{
		if (execute_built_in(shell, is_built_in(cmd_lst->cmds[0]), cmd_lst->cmds, env) == ERROR)
			return (ERROR);
	}
	else if (cmd_lst->cmds[0] && (is_built_in(cmd_lst->cmds[0]) == 0))
	{
		if (exec_fork_one(shell, cmd_lst->cmds, env) == ERROR)
			return (ERROR);
	}
	return (0);
}

int	handle_pipe_command(t_shell *shell, t_exec *current, t_valist *env)
{
	int pipe_fd[2];
	pid_t pid;

	while (current)
	{
		if (pipe(pipe_fd) == ERROR)
		{
			if(shell->prev_fd != -1)
				close(shell->prev_fd);
			return (ERROR);
		}
		pid = exec_fork_pipe(shell, current, current->cmds, env, pipe_fd);
		if (pid == ERROR)
			return (close(pipe_fd[0]), close(pipe_fd[1]), ERROR);
		current = current->next;
	}
	wait_and_status(shell, pid);
	close(pipe_fd[0]);
	return (0);
}

int	manage_execution(t_shell *shell, t_valist *env)
{
	int command_nb;
	command_nb = ft_lstexec_size(shell->cmd_lst);

	if (!shell->cmd_lst || !shell->cmd_lst->cmds) 
		return (0);
	if (command_nb == 1)
	{
		if(handle_simple_command(shell, shell->cmd_lst, env) == ERROR)
			return(ERROR);
	}
	else if (command_nb > 1)
	{
		if(handle_pipe_command(shell, shell->cmd_lst, env) == ERROR)
			return(ERROR);
	}
	return (0);
}
