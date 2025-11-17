/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Part8_execution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 16:27:16 by jdelattr          #+#    #+#             */
/*   Updated: 2025/11/15 17:33:04 by aoesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/////////////////////////////////////
/// @fonctions fork_process.c ///
////////////////////////////////////

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

int	manage_execution(t_shell *shell, t_valist *env) // , char **cmds
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
	
	/* 	if (check_all_redir(shell) != 0)
			return (1); */

	else if (cmd_list->next == NULL && cmd_list->cmds && cmd_list->cmds[0]
		&& is_built_in(cmd_list->cmds[0]) != 0)
	{
		printf("built_in type = %d\n", is_built_in(cmd_list->cmds[0]));
		execute_built_in(shell, is_built_in(cmd_list->cmds[0]), cmd_list->cmds, env); //, cmd_list->cmds); + PASSER ENV ? OU SHELL DIRECT
	}

	/* 	else // j'ai plrs commandes et des pipes (fork() les process)
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
		}*/
	return (0);
}
