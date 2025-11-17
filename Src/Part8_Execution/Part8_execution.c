/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Part8_execution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelattr <jdelattr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 16:27:16 by jdelattr          #+#    #+#             */
/*   Updated: 2025/11/17 18:18:49 by jdelattr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/////////////////////////////////////
/// @fonctions fork_process.c ///
////////////////////////////////////

void	print_char_tab(char **tab) //TEST
{
	int	i;

	i = 0;
	if (!tab)
	{
		printf("(null)\n");
		return ;
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
	int i;

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
	exit(127); // return ou perror
}

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



int	manage_execution(t_shell *shell, t_valist *env)
{
	int		i;
	t_exec	*cmd_list;
	t_exec	*current;
	int		command_nb;
	pid_t	child;

	// ac = nb de cmds
	(void)env;
	i = 0;
	cmd_list = shell->cmd_lst;
	current = cmd_list;
	command_nb = ft_lstexec_size(cmd_list);
	/* 	if (!cmd_list->cmds) // si la liste est vide
			return (0); */
	if (check_all_redir(shell) == ERROR)
		return (ERROR);
	test_print_fd(cmd_list); // TEST
	// printf("avant conversion");
	// char **env_tab = env_list_to_envp(env);
	// printf("avant print");
	// print_char_tab(env_tab);
	if (command_nb == 1)
	{
		if (cmd_list->cmds[0] && (is_built_in(cmd_list->cmds[0]) != 0))
		{
			if (execute_built_in(shell, is_built_in(cmd_list->cmds[0]),
					cmd_list->cmds, env) == ERROR)
				return (ERROR);
		}
		if (cmd_list->cmds[0] && (is_built_in(cmd_list->cmds[0]) == 0))
		{
			printf("je suis la 1\n");
			child = exec_fork_one(shell, cmd_list->cmds, env, command_nb);
			waitpid(child, 0, 0);
			/*			if (exec_fork_one(shell, cmd_list->cmds, env) != 0)
							return (ERROR); cas ou l'execution se termine mal*/
		}
	}
	else if (command_nb > 1)
	{
		// cree tous les pipes
		while (current->next != NULL)
		{
			// ICI JE TROUVE LES BONNES REDIR POUR APPELER PIPEX
			// pipex.cmd_left = current->cmds;
			// pipex.cmd_right = current->next->cmds;
			// pipex(&shell, env);
			// get_left_cmd();
			// get_right_cmd();
			// execute_cmd(cmd_list, env);
		}
	}
	return (0);
}
