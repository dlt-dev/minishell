/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Part8_execution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelattr <jdelattr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 16:27:16 by jdelattr          #+#    #+#             */
/*   Updated: 2025/11/11 22:04:22 by jdelattr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


/////////////////////////////////////
/// @fonctions fork_process.c /// 
////////////////////////////////////

// cas plsrs commandes

/////////////////////////////////////
/// @fonctions open_and_find_redir.c /// 
////////////////////////////////////

/////////////////////////////////////
/// @fonctions built_in.c /// 
////////////////////////////////////



int check_cmd_redir(t_exec *current, t_redir *redir)
{
	int fd_in;
	int fd_out;


	fd_in = -1;
	fd_out = -1;

	while (redir != NULL)
	{
		if (redir->redir_type == INFILE)
		{
			fd_in = open(redir->filename, O_RDONLY);
			if (fd_in < 0)
			{
				printf("%s : no such file or directory\n", redir->filename );//No such file or directory
				return (ERROR);
			}
			current->fd_in = fd_in;
		}
		
		else if (redir->redir_type == OUTFILE)
		{
			fd_out = open(redir->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd_out < 0)
			{
				printf("%s : impossible to access\n", redir->filename );//No such file or directory
				return (ERROR);
			}
			current->fd_out = fd_out;
		}
		
		else if (redir->redir_type == HEREDOC)
		{
			fd_in = handle_heredoc(redir->filename);
			if (fd_out < 0)
			{
				printf("error : impossible to find your heredoc\n");//No such file or directory
				return (ERROR);
			}
			current->fd_in = fd_in;
		}
		else if (redir->redir_type == OUTFILE_APPEND)
		{
			fd_out = open(redir->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (fd_in < 0)
			{
				printf("%s : impossible to access\n", redir->filename );//No such file or directory
				return (ERROR);
			}
			current->fd_out = fd_out;
		}
		redir = redir->next;
		
	}
	return (0);

}

int check_all_redir(t_shell *shell) // pour chaques nodes cmd, je check toutes les redirs et trouve in et out
{
	t_exec *current;
	current = shell->cmd_lst;
	while (current != NULL)
	{
		check_cmd_redir(current, current->redir);
		current = current->next;
	}
	return (0);
}


void test_print_fd(t_exec *cmd_list)
{
	int i = 0;
	while (cmd_list != NULL)
	{
		printf("cmd[%d] ->> cmd fd_in = %d | fd_out = %d\n",i, cmd_list->fd_in, cmd_list->fd_out);
		i++;
		cmd_list = cmd_list->next;
	}

}

int	manage_execution(t_shell *shell, t_valist *env)// , char **cmds
{
	//ac = nb de cmds
	(void) env;
	int i;
	i = 0;
	t_exec *cmd_list = shell->cmd_lst;
	//t_exec *current = cmd_list;


	check_all_redir(shell);
	test_print_fd(cmd_list);


	if (cmd_list == NULL)
	{
		return (0); // pas de commande - liste vide
		printf("pas de commande");
	}

/* 	if (check_all_redir(shell) != 0)
		return (1); */

	else if (cmd_list->next == NULL && is_built_in(cmd_list->cmds[0]) != 0) // une seul commande et builtin
	{
		printf("built_in type = %d\n", is_built_in(cmd_list->cmds[0]));
		execute_built_in(shell, is_built_in(cmd_list->cmds[0]), cmd_list->cmds, env);//, cmd_list->cmds); + PASSER ENV ? OU SHELL DIRECT
		
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
