/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Part8_exec_fork_one.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelattr <jdelattr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 17:59:57 by jdelattr          #+#    #+#             */
/*   Updated: 2025/11/20 16:59:47 by jdelattr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_tab(char **tab)
{
	int	i;

	if (tab)
	{
		i = 0;
		while (tab[i])
		{
			free(tab[i]);
			i++;
		}
	}
	free(tab);
}

int	routine_child(t_shell *shell, char **cmd, t_valist *env)
{
	int		fd_in;
	int		fd_out;
	char	*my_cmd_path;
	char	**env_tab_exe;
	
	//print_char_tab(env_tab_exe); TEST PRINT

	fd_in = shell->cmd_lst->fd_in;
	fd_out = shell->cmd_lst->fd_out;
	env_tab_exe = env_list_to_envp(env);

	//print_char_tab(cmd); TEST PRINT

 	if (access(cmd[0], X_OK) == 0)
		execve(cmd[0], cmd, env_tab_exe);
	
	my_cmd_path = find_my_cmd_path(cmd[0], env_tab_exe);
	
	if (!my_cmd_path || my_cmd_path[0] == '\0')
	{
		ft_free_tab(env_tab_exe);
		close(fd_out);
		close(fd_in);
		path_not_found();
	}
	if (fd_in != STDIN_FILENO)
	{
		dup2(fd_in, STDIN_FILENO);
		close(fd_in);
	}
	if (fd_out != STDOUT_FILENO)
	{
		dup2(fd_out, STDOUT_FILENO);
		close(fd_out);
	}
	execve(my_cmd_path, cmd, env_tab_exe);
	perror("execve");
	exit(1);
}

int	exec_fork_one(t_shell *shell, char **cmd, t_valist *env)
{
	pid_t	child;

	child = fork();
	if (child < 0)
		return(perror("fork: "), ERROR);
	if (child == 0)
	{
		routine_child(shell, cmd, env);
	}
	wait_and_status(shell, child);
	return (0);
}
