/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_execution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelattr <jdelattr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 13:24:17 by aoesterl          #+#    #+#             */
/*   Updated: 2025/11/25 20:35:26 by jdelattr         ###   ########.fr       */
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

int	exist_and_access(char *my_path)
{
	struct stat	st;

	if (stat(my_path, &st) == 0)
	{
		if (access(my_path, X_OK) == 0)
			return (0);
		return (CMD_NO_PERMISSION);
	}
	return (CMD_NOT_FOUND);
}

char	*find_my_cmd_path(char *my_cmd, char **envp, int *check)
{
	int		i;
	char	*my_path;
	char	**paths;

	paths = split_tab_paths(envp);
	i = -1;
	while (paths[++i] != NULL)
	{
		my_path = malloc(ft_strlen(paths[i]) + 1 + ft_strlen(my_cmd) + 1);
		if (!my_path)
			return (NULL);
		my_path = ft_strcpy(my_path, paths[i]);
		(ft_strcat("/", my_path), ft_strcat(my_cmd, my_path));
		*check = exist_and_access(my_path);
		if (*check == CMD_NO_PERMISSION || *check == 0)
			return (ft_free_tab(paths), my_path);
		free(my_path);
	}
	return (ft_free_tab(paths), NULL);
}
/* char	*find_my_cmd_path(char *my_cmd, char **envp, int *check)
{
	int		i;
	char	*my_path;
	char	**paths;

	paths = split_tab_paths(envp);
	i = 0;
	while (paths[i] != NULL)
	{
		my_path = malloc(ft_strlen(paths[i]) + 1 + ft_strlen(my_cmd) + 1);
		if (!my_path)
			return (NULL);
		my_path = ft_strcpy(my_path, paths[i]);
		ft_strcat("/", my_path);
		ft_strcat(my_cmd, my_path);
		*check = exist_and_access(my_path);
		if (*check == CMD_NO_PERMISSION)
			return (ft_free_tab(paths), my_path);
		else if (*check == 0)
			return (ft_free_tab(paths), my_path);
		else
		{
			free(my_path);
			i++;
		}
	}
	ft_free_tab(paths);
	return (NULL);
} */