/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Part7_cmd_struct.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelattr <jdelattr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 17:05:43 by jdelattr          #+#    #+#             */
/*   Updated: 2025/11/02 19:00:56 by jdelattr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*redir_name(int type) // TEST PRINT
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

void	print_cmd_list(t_exec *head) // TEST PRINT
{
	int i;
	int idx;
	t_redir *redir;
	t_exec *current;

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
				printf("  redir: %s  ->  %s\n",
					redir_name(redir->redir_type), redir->filename);
			else
				printf("  redir: %s  ->  (null)\n",
					redir_name(redir->redir_type));
			redir = redir->next;
		}
		current = current->next;
	}
}

t_exec	*create_new_command(void)
{
	t_exec	*command;

	command = malloc(sizeof(t_exec));
	if (!command)
		return (NULL);
	command->cmds = NULL;
	command->redir = NULL;
	command->next = NULL;
	return (command);
}

int	add_arg_command(t_exec *current, char *tok_content)
{
	int		i;
	int		j;
	char	**new_args;

	i = 0;
	j = 0;
	if (!current || !tok_content)
		return (1);
	if (current->cmds)
		while (current->cmds[i])
			i++;
	new_args = malloc(sizeof(char *) * (i + 2));
	if (!new_args)
		return (1);
	while (j < i)
	{
		new_args[j] = current->cmds[j];
		j++;
	}
	new_args[i] = ft_strdup(tok_content);
	new_args[i + 1] = NULL;
	free(current->cmds);
	current->cmds = new_args;
	return (0);
}

int	is_valid_redir(t_list *token_next)
{
	if (!token_next) // fin de liste
		return (0);
	if (token_next->flag.type != WORD)
		return (0);
	return (1);
}

int	is_valid_pipe(t_list *token_next)
{
	if (!token_next) // fin de liste
		return (0);
	if (token_next->flag.pipe == PIPE)
		return (0);
	return (1);
}

// faire une fonction manage redir et manage pipe pour etre a la norme :)
int	logical_struct(t_shell *shell, t_list *token)
{
	t_exec	*head;
	t_exec	*current;

	if (token && token->flag.pipe == PIPE)
		return (print_syntax_error(NULL, shell, "|"), 0);
	head = create_new_command();
	current = head;
	while (token)
	{
		if (token->flag.redir == REDIR && token->next && is_valid_redir(token->next))
		{
			redir_management(current, token, token->flag.redir_type);
			token = token->next;
		}
		else if (token->flag.type == WORD)
			add_arg_command(current, token->content);
		else if (token->flag.pipe == PIPE && token->next && is_valid_pipe(token->next))
		{
			//current = (current->next = create_new_command()); // moins claire mais pour la norme
			current->next = create_new_command();
			current = current->next;
		}
		else
			return (print_syntax_error(head, shell, token->content), 0);
		token = token->next;
	}
	shell->cmd_lst = head;
	return (0);
}
