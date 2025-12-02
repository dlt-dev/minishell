/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Part4_utils_execution.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 13:24:17 by aoesterl          #+#    #+#             */
/*   Updated: 2025/12/02 03:34:50 by aoesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exist_and_access(char *my_path, struct stat *st, int *check)
{
	*st = (struct stat){0};
	if (stat(my_path, st) == 0)
	{
		if (access(my_path, X_OK) == 0)
		{
			*check = 0;
			return (0);
		}
		*check = CMD_NO_PERMISSION;
		return (CMD_NO_PERMISSION);
	}
	return (CMD_NOT_FOUND);
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

char	*find_my_cmd_path(char *my_cmd, char **envp, int *check)
{
	int			i;
	char		*my_path;
	char		**paths;
	struct stat	st;

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
		exist_and_access(my_path, &st, check);
		if (*check == 0)
			return (ft_free_tab(paths), my_path);
		free(my_path);
		i++;
	}
	ft_free_tab(paths);
	return (NULL);
}
