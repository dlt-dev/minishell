/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refonte_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 17:10:20 by jdelattr          #+#    #+#             */
/*   Updated: 2025/11/19 18:06:57 by aoesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_lstexec_size(t_exec *lst)
{
	int	count;

	count = 0;
	while (lst != NULL)
	{
		count++;
		lst = lst->next;
	}
	return (count);
}

int	path_not_found(void)
{
	ft_putstr("\033[31mpath not found\n\033[0m");
	exit(127); // return ou perror
}

char	**split_tab_paths(char **envp)
{
	int		i;
	char	**paths;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	if (!envp[i])
		return (NULL);
	paths = ft_split(envp[i] + 5, ':');
	if (!paths)
		return (NULL);
	return (paths);
}

char	*find_my_cmd_path(char *my_cmd, char **envp)
{
	int		i;
	char	*my_path;
	char	**paths;

	my_path = NULL;
	paths = split_tab_paths(envp);
	i = 0;
	while (paths[i])
	{
		my_path = malloc(ft_strlen(paths[i]) + 1 + ft_strlen(my_cmd) + 1);
		if (!my_path)
			return (NULL);
		my_path = ft_strcpy(my_path, paths[i]);
		ft_strcat("/", my_path);
		ft_strcat(my_cmd, my_path);
		if (access(my_path, X_OK) == 0)
		{
			ft_free_tab(paths);
			return (my_path);
		}
		free(my_path);
		i++;
	}
	ft_free_tab(paths);
	return (NULL);
}





int	manage_execution(t_shell *shell, t_valist *env) // nombre de commande , char **cmds
{
	int i;
	i = 0;
	t_exec *cmd_list = shell->cmd_lst;
	t_exec *current = cmd_list;
	int command_nb = ft_lstexec_size(cmd_list);
	printf("commande_nb = %d\n", command_nb);
	//int	prev_fd = -1;
	//pid_t	pid;
	int pipe_fd[2];
	
	//if (!cmd_list->cmds) // si la liste est vide (segfault :())
	//	return (0);
	printf("prev_fd = %d\n", shell->prev_fd);

	if (check_all_redir(shell) == ERROR) // CHECK REDIR ET FIND LES FD SI BESOIN
		return (ERROR);

	test_print_fd(cmd_list); // TEST PRINT

	if (command_nb == 1) // CAS DE LA C OMMANDE UNIQUE
	{
		printf("builtin / cmd unique\n");
		if (cmd_list->cmds[0] && (is_built_in(cmd_list->cmds[0]) != 0)) // BUILT IN
		{
			if (execute_built_in(shell, is_built_in(cmd_list->cmds[0]), cmd_list->cmds, env) == ERROR)
				return (ERROR);
		}
		else if (cmd_list->cmds[0] && (is_built_in(cmd_list->cmds[0]) == 0)) // EXECVE
		{
			if (exec_fork_one(shell, cmd_list->cmds, env) == ERROR)
				return (ERROR);
		}
	}
	else if (command_nb > 1) // CAS COMMANDE MULTPLES (PIPES)
	{
		pid_t pid; 
		printf("pipe routine\n");
		while (current)
		{
			if (pipe(pipe_fd) < 0)
				return (perror("pipe"), ERROR);
			printf("execute command [%d]\n", i);
			pid = exec_fork_pipe(shell, current, current->cmds, env, pipe_fd);
			if (pid == ERROR)
				return (ERROR);
			current = current->next;
			i++;
			if(shell->prev_fd != -1)
				close(shell->prev_fd);
			shell->prev_fd = pipe_fd[0];
			
		}
		//waitpid(pid, 0, 0); // attends TOUT les processus - doit lancer wait(evec stutus et pid du dernier enfant)
/* 		while (waitpid(-1, 0, 0) != ERROR)
		{
			continue ;
		} */
		//waitpid(-1, 0, 0);


	}
	return (0);
}