/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part4_execve.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelattr <jdelattr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 12:36:39 by aoesterl          #+#    #+#             */
/*   Updated: 2025/11/24 16:48:10 by jdelattr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



int do_execve(t_shell *shell, char **cmd, t_valist *env)
{
	(void ) shell;
    char	*my_cmd_path;
	char	**env_tab_exe;
	int check; 

	env_tab_exe = env_list_to_envp(env);
	if(env_tab_exe == NULL)
        return(GEN_ERRNO);
	check = 0;
	check = exist_and_access(cmd[0]);
	if(check == CMD_NO_PERMISSION)
		return(ft_free_tab(env_tab_exe), CMD_NO_PERMISSION);
	if(check == 0)
	{
		if(execve(cmd[0], cmd, env_tab_exe) == ERROR)
			return(ft_free_tab(env_tab_exe), GEN_ERRNO);
	}
	my_cmd_path = find_my_cmd_path(cmd[0], env_tab_exe, &check);
	if (my_cmd_path == NULL)
		return(ft_free_tab(env_tab_exe), CMD_NOT_FOUND);
	else if (check == CMD_NO_PERMISSION)
		return(ft_free_tab(env_tab_exe), free(my_cmd_path), CMD_NO_PERMISSION);
	else
	{
    	if(execve(my_cmd_path, cmd, env_tab_exe) == ERROR)
			return(ft_free_tab(env_tab_exe), free(my_cmd_path), GEN_ERRNO);
	}
	return (0);
}

// stat permet de sqvoir si la commande existe ou non : si stqat echoue : cmmqnde not found
// si stat reussi ca veut dire que le fichier xiste et on peut effectuer les permissions
// sur le fichier avec access 

// donc si stat rate 127
// si access rate  126