/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PartX_print_tree.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelattr <jdelattr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 15:59:42 by aoesterl          #+#    #+#             */
/*   Updated: 2025/12/02 16:19:28 by jdelattr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*redir_name(int type)
{
	if (type == 11)
		return ("INFILE  (<)");
	if (type == 12)
		return ("OUTFILE (>)");
	if (type == 10)
		return ("HEREDOC  (<<)");
	if (type == 13)
		return ("OUTFILE_APPEND (>>)");
	return ("UNKNOWN");
}

void	print_cmd_list(t_exec *head)
{
	int		i;
	int		idx;
	t_redir	*redir;
	t_exec	*current;

	if (!head)
	{
		printf("print_cmd_list: no commands\n");
		return ;
	}
	idx = 0;
	current = head;
	while (current)
	{
		printf("Command [%d]:\n", idx++);
		if (current->cmds && current->cmds[0])
		{
			i = 0;
			while (current->cmds[i])
			{
				printf("  argv[%d]: %s\n", i, current->cmds[i]);
				i++;
			}
		}
		else
			printf("  (no args)\n");
		redir = current->redir;
		while (redir)
		{
			if (redir->filename)
				printf("  redir: %s  ->  %s\n", redir_name(redir->redir_type),
					redir->filename);
			else
				printf("  redir: %s  ->  (null)\n",
					redir_name(redir->redir_type));
			redir = redir->next;
		}
		current = current->next;
	}
}
