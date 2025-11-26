/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Part7_main_tree_struct.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 15:18:43 by aoesterl          #+#    #+#             */
/*   Updated: 2025/11/26 17:55:09 by aoesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_redir(t_list *token_next)
{
	if (!token_next)
		return (0);
	if (token_next->flag.type != WORD)
		return (0);
	return (1);
}

int	is_valid_pipe(t_list *token_next)
{
	if (!token_next)
		return (0);
	if (token_next->flag.pipe == PIPE)
		return (0);
	return (1);
}

t_exec	*create_new_command(void)
{
	t_exec	*command;

	
	command = malloc(sizeof(t_exec));
	if (!command)
		return (NULL);
	command->cmds = NULL;
	command->redir = NULL;
	command->fd_in = STDIN_FILENO;
	command->fd_out = STDOUT_FILENO;
	command->next = NULL;
	return (command);
}

int	loop_create_tree(t_shell *shell, t_exec *current, t_list *tk)
{
	while (tk != NULL)
	{
		if (tk->flag.redir == REDIR && tk->next && is_valid_redir(tk->next))
		{
			if (redir_management(current, tk, tk->flag.redir_type) == ERROR)
				return (ERROR);
			tk = tk->next;
		}
		else if (tk->flag.type == WORD)
		{
			if (add_arg_command(current, tk->content) == ERROR)
				return (ERROR);
		}
		else if (tk->flag.pipe == PIPE && tk->next && is_valid_pipe(tk->next))
		{
			current->next = create_new_command();
			current = current->next;
			if (current == NULL)
				return (ERROR);
		}
		else
			return (print_syntax_error(shell, tk->content), SYNTAXE_ERR);
		tk = tk->next;
	}
	return (0);
}

int	logical_struct(t_shell *shell, t_exec *current, t_list *token)
{
	int	value;

	if (token == NULL)
		return (0);
	if (token && token->flag.pipe == PIPE)
		return (print_syntax_error(shell, "|"), 0);
	shell->cmd_lst = create_new_command();
	if (shell->cmd_lst == NULL)
		return (ERROR);
	current = shell->cmd_lst;
	value = loop_create_tree(shell, current, token);
	if (value == SYNTAXE_ERR)
		return (free_all(shell), 0);
	if (value == ERROR)
		return (ERROR);
	return (0);
}
