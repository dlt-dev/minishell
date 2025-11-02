/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Part7_syntax_error.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelattr <jdelattr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 12:11:09 by jdelattr          #+#    #+#             */
/*   Updated: 2025/11/02 18:41:58 by jdelattr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void free_tab(char **cmds)
{
	int i;

	if (!cmds)
		return ;
	i = 0;
	while (cmds[i])
	{
		free(cmds[i]);
		i++;
	}
	printf("je suis dans free_tab()\n");
	free(cmds);
}

void free_exec_lst(t_exec *cmd)
{
	t_exec *tmp;
	t_redir *redir_tmp;

	tmp = NULL;
	redir_tmp = NULL;
	while (cmd)
	{
		tmp = cmd->next;
		while (cmd->redir)
		{
			redir_tmp = cmd->redir->next;
			free(cmd->redir->filename);
			free(cmd->redir);
			cmd->redir = redir_tmp; // redir suivante
		}
		free_tab(cmd->cmds);
		free(cmd);
		cmd = tmp; // je passe head a la node suivante
		printf("je suis dans free_exec()\n");
	}
}

void	print_syntax_error(t_exec *head, t_shell *shell, char *tok_content)
{
	printf("syntax error near unexpected token '%s'\n", tok_content);
	shell->exit_status = 127;
	if (head)
	{
		free_exec_lst(head);
		printf("je suis dans print_syntaxe_err()\n");
	}
}
