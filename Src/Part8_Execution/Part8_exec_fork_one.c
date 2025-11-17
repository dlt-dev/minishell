/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Part8_exec_fork_one.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelattr <jdelattr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 17:59:57 by jdelattr          #+#    #+#             */
/*   Updated: 2025/11/17 19:47:48 by jdelattr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	routine_child(t_shell *shell, char **cmd, char **env_tab)
{
	int		fd_in;
	int		fd_out;
	char	*my_cmd_path;
	
	//print_char_tab(env_tab_exe);


	//fd in et out
	printf("je suis la 3\n");
	fd_in = shell->cmd_lst->fd_in; //open(shell.cmd_lst->fd_in, O_RDONLY);
	fd_out = shell->cmd_lst->fd_out;
	//check_error_one(fd1, cmd1, av, fd_pipe); NORMALEMENT DEJA CHECK avant
	printf("je suis la 4\n");
	//print_char_tab(cmd);
	my_cmd_path = find_my_cmd_path(cmd[0], env_tab);
	
	printf("my cmd path = %s\n", my_cmd_path);

	printf("je suis la 5\n");
	if (!my_cmd_path || my_cmd_path[0] == '\0')
	{
		//ft_free_tab(cmd1);
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
	// if(exec faled) -> free tout
	execve(my_cmd_path, cmd, env_tab);
	perror("execve");

	// free la memoire ??
	exit(1);
	//return (0);
}

int	exec_fork_one(t_shell *shell, char **cmd, t_valist *env, int count)
{
	pid_t	child;
	char	**env_tab;

	env_tab = env_list_to_envp(env, count);
	
	child = fork();
	if (child < 0)
		perror("fork: ");
	if (child == 0)
	{
		printf("je suis la 2\n");
		routine_child(shell, cmd, env_tab);
	}
	int status = 0;
	waitpid(child, &status, 0);
	return (child);
	//return (0);
}
