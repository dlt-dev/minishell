/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part4_execve.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 12:36:39 by aoesterl          #+#    #+#             */
/*   Updated: 2025/11/28 14:15:04 by aoesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strchr(char *str, char c)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (NULL);
	while (str[i] != '\0')
	{
		if (str[i] == c)
			return (&str[i]);
		i++;
	}
	return (NULL);
}

int	exec_env_path(char **env_tab_exe, char **cmd)
{
	int		check;
	char	*my_cmd_path;

	my_cmd_path = find_my_cmd_path(cmd[0], env_tab_exe, &check);
	if (my_cmd_path == NULL)
		return (CMD_NOT_FOUND);
	else if (check == CMD_NO_PERMISSION)
		return (free(my_cmd_path), CMD_NO_PERMISSION);
	else
	{
		if (execve(my_cmd_path, cmd, env_tab_exe) == ERROR)
			return (free(my_cmd_path), GEN_ERRNO);
	}
	return (0);
}

int	exec_relativ_path(char **env_tab_exe, char **cmd)
{
	int	check;

	check = exist_and_access(cmd[0]);
	if (check == 0)
	{
		if (execve(cmd[0], cmd, env_tab_exe) == ERROR)
			return (GEN_ERRNO);
	}
	return (check);
}

int	do_execve(char **cmd, t_valist *env)
{
	char	**env_tab_exe;
	int		check;

	env_tab_exe = env_list_to_envp(env);
	if (env_tab_exe == NULL)
		return (GEN_ERRNO);
	if (ft_strchr(cmd[0], '/') != NULL)
		check = exec_relativ_path(env_tab_exe, cmd);
	else
		check = exec_env_path(env_tab_exe, cmd);
	return (ft_free_tab(env_tab_exe), check);
}
