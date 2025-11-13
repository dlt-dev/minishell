/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Part8_built_in.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 19:54:50 by jdelattr          #+#    #+#             */
/*   Updated: 2025/11/13 18:28:35 by aoesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/////////////////////////////////////
/// @fonctions built_in.c ///
////////////////////////////////////

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
	if (ft_strncmp(cmd, "echo", ft_strlen("echo")) == 0)
		return (ECHO);
	if (ft_strncmp(cmd, "cd", ft_strlen("cd")) == 0)
		return (CD);
	if (ft_strncmp(cmd, "pwd", ft_strlen("pwd")) == 0)
		return (PWD);
	if (ft_strncmp(cmd, "export", ft_strlen("export")) == 0)
		return (EXPORT);
	if (ft_strncmp(cmd, "unset", ft_strlen("unset")) == 0)
		return (UNSET);
	if (ft_strncmp(cmd, "env", ft_strlen("env")) == 0)
		return (ENV);
	if (ft_strncmp(cmd, "exit", ft_strlen("exit")) == 0)
		return (EXIT);
	else
		return (NO_BUILT_IN);
}

int	execute_built_in(t_shell *shell, int type, char **args, t_valist *env)
{
	int fd_out = shell->cmd_lst->fd_out;
	
	if (type == ECHO) // echo with option -n
		builtin_echo(args, fd_out);
	if (type == CD) // with only a relative or absolute path
		builtin_cd(args);
	if (type == PWD) // no opt
		builtin_pwd(fd_out);
	if (type == EXPORT) // no opt mais plusieurs args
		builtin_export(shell, env, args);
	if (type == UNSET) // no opt
		builtin_unset(shell, env, args); //ft_unset(shell, env, args);
	if (type == ENV) // no opt
		builtin_env(env, fd_out);
	if (type == EXIT) // no opt
		builtin_exit(shell); //(args) si args est ce que j'execute qm ???
	//else
	return (1);
	
}
