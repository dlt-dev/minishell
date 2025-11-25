/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Part7_redir_struct.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelattr <jdelattr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 15:13:58 by aoesterl          #+#    #+#             */
/*   Updated: 2025/11/25 21:21:44 by jdelattr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redir	*create_new_redir(char *filename, int type)
{
	t_redir	*new;

	new = malloc(sizeof(t_redir));
	if (new == NULL)
		return (NULL);
	new->redir_type = type;
	new->filename = ft_strdup(filename);
	if (filename == NULL)
		return (free(new), NULL);
	new->next = NULL;
	return (new);
}

void	add_redir_command(t_exec *current, t_redir *redir)
{
	t_redir	*tmp;

	tmp = current->redir;
	if (current->redir == NULL)
	{
		current->redir = redir;
		return ;
	}
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = redir;
}

int	redir_management(t_exec *current, t_list *token, int type)
{
	t_redir	*new_redir;

	new_redir = create_new_redir(token->next->content, type);
	if (new_redir == NULL)
		return (ERROR);
	add_redir_command(current, new_redir);
	return (0);
}
