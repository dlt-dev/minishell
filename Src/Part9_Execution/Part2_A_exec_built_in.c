/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Part2_A_exec_built_in.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 19:54:50 by jdelattr          #+#    #+#             */
/*   Updated: 2025/12/03 15:12:07 by aoesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_built_in(char **cmd)
{
	if(cmd == NULL)
		return (NO_BUILT_IN);
		
	if (ft_strcmp(cmd[0], "echo") == 0)
		return (ECHO);
	if (ft_strcmp(cmd[0], "cd") == 0)
		return (CD);
	if (ft_strcmp(cmd[0], "pwd") == 0)
		return (PWD);
	if (ft_strcmp(cmd[0], "export") == 0)
		return (EXPORT);
	if (ft_strcmp(cmd[0], "unset") == 0)
		return (UNSET);
	if (ft_strcmp(cmd[0], "env") == 0)
		return (ENV);
	if (ft_strcmp(cmd[0], "exit") == 0)
		return (EXIT);
	else
		return (NO_BUILT_IN);
}

int	execute_built_in(t_shell *shell, int type, char **args, int print_flag)
{
	int	fd_out;

	
	fd_out = shell->cmd_lst->fd_out;

	if (ft_lstexec_size(shell->cmd_lst) > 1)
		fd_out = STDOUT_FILENO;
	
	if (type == ECHO)
		shell->exit_status = builtin_echo(args, fd_out);
	if (type == CD)
		shell->exit_status = builtin_cd(shell, args, fd_out);
	if (type == PWD)
		shell->exit_status = builtin_pwd(fd_out);
	if (type == EXPORT)
		shell->exit_status = builtin_export(shell, shell->env, args, fd_out);
	if (type == UNSET)
		shell->exit_status = builtin_unset(shell, shell->env, args);
	if (type == ENV)
		shell->exit_status = builtin_env(shell->env, fd_out, 0);
	if (type == EXIT)
		builtin_exit(shell, args, print_flag);
	return (1);
}
