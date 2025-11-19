/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refonte_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelattr <jdelattr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 17:10:20 by jdelattr          #+#    #+#             */
/*   Updated: 2025/11/19 17:13:12 by jdelattr         ###   ########.fr       */
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


int routine_pipe(t_shell *shell,t_exec *current, char **cmd, t_valist *env, int pipe_fd[2])
{
	// !! il me faut le fd in et ou de LA cmd
	char	*my_cmd_path;
	char	**env_tab_exe;
	int	prev_fd = shell->prev_fd;

	env_tab_exe = env_list_to_envp(env);

 	if (access(cmd[0], X_OK) == 0)
		execve(cmd[0], cmd, env_tab_exe);
	
	my_cmd_path = find_my_cmd_path(cmd[0], env_tab_exe);
	if (!my_cmd_path || my_cmd_path[0] == '\0')
	{
		ft_free_tab(env_tab_exe);
		//close(fd_out);
		//close(fd_in);
		path_not_found();
	}

	// IN
	if (current->fd_in != STDIN_FILENO)
	{
		dup2(current->fd_in, STDIN_FILENO);
		close(current->fd_in);
	}
	else if (prev_fd != -1)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
	// OUT
	if (current->fd_out != STDOUT_FILENO)
	{
		dup2(current->fd_out, STDOUT_FILENO);
		close(current->fd_out);
	}
/* 	else if (!current->next) // si pb pour les redirs de la derniere commmande .
	{
		
	} */
	else if (current->next) 
	{
		dup2(pipe_fd[1], STDOUT_FILENO);
	}

	close(pipe_fd[0]);
	close(pipe_fd[1]);
	
	execve(my_cmd_path, cmd, env_tab_exe);
	perror("execve");
	exit(1);

}

int	routine_builtin_pipe(t_shell *shell, t_exec *current, char **cmd, t_valist *env, int pipe_fd[2])
{
	int	prev_fd;

	prev_fd = shell->prev_fd;
	// IN
	if (current->fd_in != STDIN_FILENO)
	{
		dup2(current->fd_in, STDIN_FILENO);
		close(current->fd_in);
	}
	else if (prev_fd != -1)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
	// OUT
	if (current->fd_out != STDOUT_FILENO)
	{
		dup2(current->fd_out, STDOUT_FILENO);
		close(current->fd_out);
	}
	else if (current->next) 
	{
		dup2(pipe_fd[1], STDOUT_FILENO);
	}

	close(pipe_fd[0]);
	close(pipe_fd[1]);
	
	execute_built_in(shell, is_built_in(cmd[0]), cmd , env);
	printf("j'ai execute mon builtin\n");
	exit(1);//fin du fork()
}

int exec_fork_pipe(t_shell *shell,t_exec *current, char **cmd, t_valist *env, int pipe_fd[2])
{
	pid_t child;

	// check si j'ai affaire a un built in
	// lance routine_built_in() si c'est le cas

	child = fork();
	
	if (child < 0)
		return (perror("fork: "), ERROR);
	if(child > 0)
	{ 
		close(pipe_fd[0]);
		return(child);
	}
	if (child == 0)
	{
		if (is_built_in(current->cmds[0]) != 0) // cas built in
		{
			printf("fork builtin routine\n");
			routine_builtin_pipe(shell, current, cmd, env, pipe_fd);
		}
		routine_pipe(shell, current, cmd, env, pipe_fd); // routine execve()
	}
	close(pipe_fd[0]);
	//waitpid(child, 0, 0);
	return (child);
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