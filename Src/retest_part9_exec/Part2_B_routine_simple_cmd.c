/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Part2_B_routine_simple_cmd.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelattr <jdelattr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 13:21:20 by aoesterl          #+#    #+#             */
/*   Updated: 2025/11/24 16:32:32 by jdelattr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int redir_one_command(t_shell *shell)
{
	int		fd_in;
	int		fd_out;

	fd_in = shell->cmd_lst->fd_in;
	fd_out = shell->cmd_lst->fd_out;
	if (fd_in != STDIN_FILENO)
	{
		if(dup2(fd_in, STDIN_FILENO) == ERROR)
			return(GEN_ERRNO);
		close(fd_in);
	}
	if (fd_out != STDOUT_FILENO)
	{
		if(dup2(fd_out, STDOUT_FILENO) == ERROR)
			return(GEN_ERRNO);
		close(fd_out);	
	}
	return(0); 
}



int	routine_child(t_shell *shell, char **cmd, t_valist *env)
{	
	int exit_status;
	//print_char_tab(env_tab_exe); TEST PRINT
	//print_char_tab(cmd); TEST PRINT
	if(redir_one_command(shell) == GEN_ERRNO)
		free_exit(shell, GEN_ERRNO, cmd[0]);
	exit_status = do_execve(shell, cmd, env);
	free_exit(shell, exit_status,  cmd[0]);
	return (0);
}

int	exec_fork_one(t_shell *shell, char **cmd, t_valist *env)
{
	pid_t	child;

	child = fork();
	if (child == ERROR)
		return(ERROR);
	if (child == 0)
	{
		routine_child(shell, cmd, env);
	}
	//int status = 0;
	wait_and_status(shell, child);//&status, 0);
	return (0);
}