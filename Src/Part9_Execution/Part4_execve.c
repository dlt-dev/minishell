/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Part4_execve.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 12:36:39 by aoesterl          #+#    #+#             */
/*   Updated: 2025/12/03 17:18:55 by aoesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	failed_exec_message(char *cmd, char *message)
{
	int len;
	char *error;

	len = ft_strlen("minishell: ") + ft_strlen(cmd) + ft_strlen(message) + 1;
	error = malloc(sizeof(char) * len);
	ft_memset(error, '\0', len);
	if(error == NULL)
		return;
	ft_strcat("minishell: ", error);
	ft_strcat(cmd, error);
	ft_strcat(message, error);
	write_str_fd(error, 2);
	free(error);
}

int	exec_env_path(char **env_tab_exe, char **cmd)
{
	int		check;
	char	*my_cmd_path;

	check = CMD_NOT_FOUND;
	my_cmd_path = find_my_cmd_path(cmd[0], env_tab_exe, &check);
	if (check == CMD_NO_PERMISSION)
	{
		free(my_cmd_path);
		failed_exec_message(cmd[0], ": Permission denied\n");
		return (CMD_NO_PERMISSION);
	}
	else if (my_cmd_path == NULL)
		return (failed_exec_message(cmd[0], ": Command not found\n"),
			CMD_NOT_FOUND);
	else
	{
		if (execve(my_cmd_path, cmd, env_tab_exe) == ERROR)
			return (free(my_cmd_path),
				failed_exec_message(cmd[0], ": Command not found\n"), CMD_NOT_FOUND);
	}
	return (0);
}

int	exec_relativ_path(char **env_tab_exe, char **cmd)
{
	int			check;
	struct stat	st;

	check = CMD_NOT_FOUND;
	check = exist_and_access(cmd[0], &st, &check);
	if (S_ISDIR(st.st_mode) != 0)
		return (failed_exec_message(cmd[0], ": Is a directory\n"),
			IS_A_DIR);
	if (check == CMD_NOT_FOUND)
		return (failed_exec_message(cmd[0], ": Command not found\n"),
			CMD_NOT_FOUND);
	if (check == CMD_NO_PERMISSION)
		return (failed_exec_message(cmd[0], ": Permission denied\n"),
			CMD_NO_PERMISSION);
	if (check == 0)
	{
		if (execve(cmd[0], cmd, env_tab_exe) == ERROR)
			return (failed_exec_message(cmd[0], ": Command not found\n"), CMD_NOT_FOUND);
		
	}
	return (0);
}

int	do_execve(char **cmd, t_valist *env)
{
	char	**env_tab_exe;
	int		check;
	
	if(cmd == NULL)
		return(0);
	env_tab_exe = env_list_to_envp(env);
	if (env_tab_exe == NULL)
		return (GEN_ERRNO);
	if (ft_strchr(cmd[0], '/') != NULL)
		check = exec_relativ_path(env_tab_exe, cmd);
	else
		check = exec_env_path(env_tab_exe, cmd);
	return (ft_free_tab(env_tab_exe), check);
}
