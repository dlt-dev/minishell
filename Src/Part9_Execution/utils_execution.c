/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_execution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 13:24:17 by aoesterl          #+#    #+#             */
/*   Updated: 2025/11/28 14:00:32 by aoesterl         ###   ########.fr       */
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
	exit(127);
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
	if (paths == NULL)
		return (NULL);
	i = 0;
	while (paths[i] != NULL)
	{
		my_path = malloc(ft_strlen(paths[i]) + 1 + ft_strlen(my_cmd) + 1);
		if (!my_path)
			break ;
		my_path = ft_strcpy(my_path, paths[i]);
		ft_strcat("/", my_path);
		ft_strcat(my_cmd, my_path);
		*check = exist_and_access(my_path);
		if (*check == CMD_NO_PERMISSION || *check == 0)
			return (ft_free_tab(paths), my_path);
		free(my_path);
		i++;
	}
	ft_free_tab(paths);
	return (NULL);
}
