/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Part8_execution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 16:27:16 by jdelattr          #+#    #+#             */
/*   Updated: 2025/11/18 02:48:19 by aoesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/////////////////////////////////////
/// @fonctions fork_process.c ///
////////////////////////////////////

void	print_char_tab(char **tab)
{
	int i = 0;

	if (!tab)
	{
		printf("(null)\n");
		return;
	}
	printf("mon char **\n");
	while (tab[i])
	{
		printf("%s\n", tab[i]);
		i++;
	}
}

void	test_print_fd(t_exec *cmd_list) // TEST
{
	int	i;

	i = 0;
	while (cmd_list != NULL)
	{
		printf("cmd[%d] ->> cmd fd_in = %d | fd_out = %d\n", i, cmd_list->fd_in,
			cmd_list->fd_out);
		i++;
		cmd_list = cmd_list->next;
	}
}

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


/* void	check_error_one(int fd1, char **cmd1, char**av, int fd_pipe[2])
{
	if (fd1 < 0)
	{
		ft_free_tab(cmd1);
		perror(av[1]);
		close(fd_pipe[1]);
		exit(1);
	}
	close(fd_pipe[0]);
	if (!cmd1[0] || cmd1[0][0] == '\0')
	{
		ft_free_tab(cmd1);
		close(fd_pipe[1]);
		close(fd1);
		cmd_not_found();
	}
} */

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

int	path_not_found(void)
{
	ft_putstr("\033[31mpath not found\n\033[0m");
	exit(127);//return ou perror
}

/* char	**split_tab_paths(char **env)
{
	//int		i;
	char	**paths;

	//i = 0;
	if (!env)
		return (NULL);
	while (env->next && ft_strncmp(env->name, "PATH", 4) != 0)//(envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
		env = env->next;

	paths = ft_split(env->value, ':');
	if (!paths)
		return (NULL);
	return (paths);
} */


char	**split_tab_paths(char **envp)
{
	int		i;
	char	**paths;

	i = 0;
	printf("je suis dans le split\n");
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	if (!envp[i])
		return (NULL);
	paths = ft_split(envp[i] + 5, ':');
	print_char_tab(paths);
	if (!paths)
		return (NULL);
	return (paths);
}


/* char	*find_my_cmd_path(char *my_cmd, char **env)
{
	int		i;
	char	*my_path;
	char	**paths;

	my_path = NULL;
	paths = split_tab_paths(env);
	i = 0;
	while (paths[i])
	{
		my_path = malloc(ft_strlen(paths[i]) + 1 + ft_strlen(my_cmd) + 1);
		if (!my_path)
			return (NULL);

		ft_strcpy(my_path, paths[i]);//copie paths 1 2 3 ... dans my_path
		ft_strcat(my_path, "/");//cat /
		ft_strcat(my_path, my_cmd);// cat my_cmd a la suite
		if (access(my_path, X_OK) == 0)//SI JE TROUVE UN CHEMIN JE RETOURNE LE BON
		{
			ft_free_tab(paths);
			return (my_path);
		}
		free(my_path);
		i++;
	}
	ft_free_tab(paths);
	return (NULL);
} */

char	*find_my_cmd_path(char *my_cmd, char **envp)
{
	int		i;
	char	*my_path;
	char	**paths;

	my_path = NULL;
	paths = split_tab_paths(envp);
	i = 0;
	if (!paths)
		printf("c'est ici j'ai ");

	while (paths[i])
	{
		my_path = malloc((ft_strlen(paths[i]) + 1 + ft_strlen(my_cmd) + 1) * sizeof(char));
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



int	ft_lstvalist_size(t_valist *lst)
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

char **env_list_to_envp(t_valist *env_list)
{
	int count = ft_lstvalist_size(env_list);

	char **env = malloc(sizeof(char *) * (count + 1));

	if (!env)
		return NULL;

	int i = 0;
	while (env_list)
	{
		int len_name = strlen(env_list->name);
		int len_val = strlen(env_list->value);

		int total = len_name + 1 + len_val;

		env[i] = malloc(total + 1);

		if (!env[i])
			return NULL; // FREE ?

		ft_memcpy(env[i], env_list->name, len_name);
		env[i][len_name] = '=';
		ft_memcpy(env[i] + len_name + 1, env_list->value, len_val);

		env[i][total] = '\0';

		env_list = env_list->next;
		i++;
	}
	env[i] = NULL;
	return env;
}

int	routine_child(t_shell *shell, char **cmd, t_valist *env)
{
	int		fd_in;
	int		fd_out;
	char	*my_cmd_path;
	char	**env_tab_exe = env_list_to_envp(env);
	//print_char_tab(env_tab_exe);


	//fd in et out
	printf("je suis la 3\n");
	fd_in = shell->cmd_lst->fd_in; //open(shell.cmd_lst->fd_in, O_RDONLY);
	fd_out = shell->cmd_lst->fd_out;
	//check_error_one(fd1, cmd1, av, fd_pipe); NORMALEMENT DEJA CHECK avant
	printf("je suis la 4\n");
	//print_char_tab(cmd);
	my_cmd_path = find_my_cmd_path(cmd[0], env_tab_exe);
	
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
	execve(my_cmd_path, cmd, env_tab_exe);
	perror("execve");

	// free la memoir ??
	exit(1);
	//return (0);
}

int	exec_fork_one(t_shell *shell, char **cmd, t_valist *env)
{
	pid_t	child;

	child = fork();
	if (child < 0)
		perror("fork: ");
	if (child == 0)
	{
		printf("je suis la 2\n");
		routine_child(shell, cmd, env);
		fprintf(stderr, "je suis la 20\n");
		
	}
	int status = 0;
	waitpid(child, &status, 0);

	return (child);
	//return (0);
}



int	manage_execution(t_shell *shell, t_valist *env) // nombre de commande , char **cmds
{
	// ac = nb de cmds
	(void)env;
	t_exec *cmd_list = shell->cmd_lst;
	t_exec *current = cmd_list;
	int command_nb = ft_lstexec_size(cmd_list);
	pid_t child;
/* 	if (!cmd_list->cmds) // si la liste est vide
		return (0); */

	if (check_all_redir(shell) == ERROR)
		return (ERROR);
	
	test_print_fd(cmd_list); // TEST

	//printf("avant conversion");
	//char **env_tab = env_list_to_envp(env);
	//printf("avant print");
	//print_char_tab(env_tab);

	if (command_nb == 1)
	{
		if (cmd_list->cmds[0] && (is_built_in(cmd_list->cmds[0]) != 0))
		{
			if (execute_built_in(shell, is_built_in(cmd_list->cmds[0]), cmd_list->cmds, env) == ERROR)
				return (ERROR);
		}
		if (cmd_list->cmds[0] && (is_built_in(cmd_list->cmds[0]) == 0))
		{
			printf("je suis la 1\n");
			child = exec_fork_one(shell, cmd_list->cmds, env);
			waitpid(child, 0, 0);
/* 			if (exec_fork_one(shell, cmd_list->cmds, env) != 0)
				return (ERROR); */
		}
	}
	else if (command_nb > 1)
	{
		//cree tous les pipes
		while (current->next != NULL)
		{
			//ICI JE TROUVE LES BONNES REDIR POUR APPELER PIPEX

			//pipex.cmd_left = current->cmds;
			//pipex.cmd_right = current->next->cmds;

			//pipex(&shell, env);

			//get_left_cmd();
			//get_right_cmd();

			//execute_cmd(cmd_list, env);
		}
	}
	return (0);
}

/* int	manage_execution(t_shell *shell, t_valist *env) // , char **cmds
{
	// ac = nb de cmds
	(void)env;
	t_exec *cmd_list = shell->cmd_lst;
	// t_exec *current = cmd_list;

	check_all_redir(shell);
	test_print_fd(cmd_list);

	if (cmd_list == NULL)
	{
		return (0); // pas de commande - liste vide
		printf("pas de commande");
	}
	
		if (check_all_redir(shell) != 0)
			return (1);

	else if (cmd_list->next == NULL && cmd_list->cmds && cmd_list->cmds[0]
		&& is_built_in(cmd_list->cmds[0]) != 0)
	{
		printf("built_in type = %d\n", is_built_in(cmd_list->cmds[0]));
		execute_built_in(shell, is_built_in(cmd_list->cmds[0]), cmd_list->cmds, env); //, cmd_list->cmds); + PASSER ENV ? OU SHELL DIRECT
	}

		else // j'ai plrs commandes et des pipes (fork() les process)
		{
			while (current->next != NULL)
			{
				//ICI JE TROUVE LES BONNES REDIR POUR APPELER PIPEX

				pipex.cmd_left = current->cmds;
				pipex.cmd_right = current->next->cmds;

				pipex(&shell, env);

				//get_left_cmd();
				//get_right_cmd();

				//execute_cmd(cmd_list, env);
			}
		}
	return (0);
} */



/* 	if (count == 1)
	{
		if (is_built_in())
		{
			//execute built in
		}
		if (!is_built_in())
		{
			//fork la commande unique
		}
	}
	else if (count > 1)
	{
		//agis sur les paires de commandes
		// creee le pipe et applique les redirections
		//
		
	}
	return (ERROR); */