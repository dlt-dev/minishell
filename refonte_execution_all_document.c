/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refonte_execution_all_document.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelattr <jdelattr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 17:10:20 by jdelattr          #+#    #+#             */
/*   Updated: 2025/11/19 17:20:53 by jdelattr         ###   ########.fr       */
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


