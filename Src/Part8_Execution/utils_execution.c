/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_execution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 13:24:17 by aoesterl          #+#    #+#             */
/*   Updated: 2025/11/26 20:59:30 by aoesterl         ###   ########.fr       */
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

char *find_my_cmd_path(char *my_cmd, char **envp, int *check)
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
			break;
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
		*check = exist_and_access(my_path);// 	char	**env_tab_exe;
// 	int check; 

// 	env_tab_exe = env_list_to_envp(env);
// 	if(env_tab_exe == NULL)
//         return(GEN_ERRNO);
// 	check = 0;
// 	check = exist_and_access(cmd[0]);
// 	if(check == CMD_NO_PERMISSION)
// 		return(ft_free_tab(env_tab_exe), CMD_NO_PERMISSION);
// 	if(check == 0)
// 	{
// 		if(execve(cmd[0], cmd, env_tab_exe) == ERROR)
// 			return(ft_free_tab(env_tab_exe), GEN_ERRNO);
// 	}
// 	my_cmd_path = find_my_cmd_path(cmd[0], env_tab_exe, &check);
// 	if (my_cmd_path == NULL)
// 		return(ft_free_tab(env_tab_exe), CMD_NOT_FOUND);
// 	else if (check == CMD_NO_PERMISSION)
// 		return(ft_free_tab(env_tab_exe), free(my_cmd_path), CMD_NO_PERMISSION);
// 	else
// 	{
//     	if(execve(my_cmd_path, cmd, env_tab_exe) == ERROR)
// 			return(ft_free_tab(env_tab_exe), free(my_cmd_path), GEN_ERRNO);
// 	}
// 	return (0);
// }

// stat permet de sqvoir si la commande existe ou non : si stqat echoue : cmmqnde not found
// si stat reussi ca veut dire que le fichier xiste et on peut effectuer les permissions
// sur le fichier avec access 

// donc si stat rate 127
// si access rate  126

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
