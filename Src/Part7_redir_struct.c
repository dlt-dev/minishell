/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Part7_redir_struct.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelattr <jdelattr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 15:59:13 by jdelattr          #+#    #+#             */
/*   Updated: 2025/11/02 16:40:59 by jdelattr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redir	*create_new_redir(char *filename, int type) // si plusieurs redir a la suite
{
	t_redir	*new;

	new = malloc(sizeof(t_redir));
	if (!new)
		return (NULL);
	new->redir_type = type;
	new->filename = ft_strdup(filename);
	new->next = NULL;
	return (new);
}

void	add_redir_command(t_exec *current, t_redir *redir)
{
	t_redir	*tmp;

	tmp = NULL;
	if (!current || !redir)
		return ;
	if (!current->redir)
	{
		current->redir = redir;
		return ;
	}
	tmp = current->redir;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = redir;
}

// assigne le type de redir et file le filename dans la nod commande correspondante
void	redir_management(t_exec *current, t_list *token, int type)
{
	t_list	*next_token;
	t_redir	*new_redir;

	if (!current || !token)
		return ;
	next_token = token->next;
	new_redir = create_new_redir(next_token->content, type);
	add_redir_command(current, new_redir);
}
