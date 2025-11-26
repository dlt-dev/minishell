/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Part2_C_routine_pipe.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 15:47:46 by aoesterl          #+#    #+#             */
/*   Updated: 2025/11/26 20:58:11 by aoesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	routine_builtin_pipe(t_shell *shell, t_exec *current, char **cmd, int pipe_fd[2])
{
	if(apply_redir_pipe(shell, current, pipe_fd) == GEN_ERRNO)
		free_exit(shell, GEN_ERRNO, cmd[0]);
	if(execute_built_in(shell, is_built_in(cmd[0]), cmd , 1) == ERROR)
		free_exit(shell, GEN_ERRNO, cmd[0]);
	printf("j'ai execute mon builtin\n");
	free_exit(shell, shell->exit_status, NULL);
}

void routine_pipe(t_shell *shell,t_exec *current, char **cmd, int pipe_fd[2])
{
	int exit_status;
	
	if(apply_redir_pipe(shell, current, pipe_fd) == GEN_ERRNO)
		free_exit(shell, GEN_ERRNO, cmd[0]);
	exit_status = do_execve(cmd, shell->env);
	free_exit(shell, exit_status, cmd[0]);
}

int exec_fork_pipe(t_shell *shell,t_exec *current, char **cmd, int pipe_fd[2])
{
	pid_t child;

	child = fork();
	if (child == ERROR)
		return (ERROR);
	if(child > 0)
	{ 
		if(shell->prev_fd != -1)
			close(shell->prev_fd);
		close(pipe_fd[1]);
		shell->prev_fd = pipe_fd[0];
		return(child);
	}
	if (child == 0)
	{
		if (is_built_in(current->cmds[0]) != 0)
		{
			printf("fork builtin routine\n");
			routine_builtin_pipe(shell, current, cmd, pipe_fd);
		}
		routine_pipe(shell, current, cmd, pipe_fd); 
	}
	return(0);
}
