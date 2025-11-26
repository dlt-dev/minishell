/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Part2_A_exec_built_in.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 19:54:50 by jdelattr          #+#    #+#             */
/*   Updated: 2025/11/26 20:19:16 by aoesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

enum	e_builtin_type
{
	NO_BUILT_IN,
	ECHO,
	CD,
	PWD,
	EXPORT,
	UNSET,
	ENV,
	EXIT,
};

int	is_built_in(char *cmd) // return l'enum du builtin
{
	if (ft_strcmp(cmd, "echo") == 0)
		return (ECHO);
	if (ft_strcmp(cmd, "cd") == 0)
		return (CD);
	if (ft_strcmp(cmd, "pwd") == 0)
		return (PWD);
	if (ft_strcmp(cmd, "export") == 0)
		return (EXPORT);
	if (ft_strcmp(cmd, "unset") == 0)
		return (UNSET);
	if (ft_strcmp(cmd, "env") == 0)
		return (ENV);
	if (ft_strcmp(cmd, "exit") == 0)
		return (EXIT);
	else
		return (NO_BUILT_IN);
}

int	execute_built_in(t_shell *shell, int type, char **args, int print_flag)
{
	int	fd_out;

	fd_out = shell->cmd_lst->fd_out;
	if (type == ECHO)
		shell->exit_status = builtin_echo(args, fd_out);
	if (type == CD)
		shell->exit_status = builtin_cd(shell, args);
	if (type == PWD)
		shell->exit_status = builtin_pwd(fd_out);
	if (type == EXPORT)
		shell->exit_status = builtin_export(shell, shell->env, args);
	if (type == UNSET)
		shell->exit_status = builtin_unset(shell, shell->env, args);
	if (type == ENV)
		shell->exit_status = builtin_env(shell->env, fd_out, 0);
	if (type == EXIT)
		builtin_exit(shell, args, print_flag);
	return (1);
}
