/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   restest_redir_struct.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 19:29:33 by aoesterl          #+#    #+#             */
/*   Updated: 2025/11/12 20:01:02 by aoesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

t_redir	*create_new_redir(char *filename, int type) // si plusieurs redir a la suite
{
	t_redir	*new;

	new = malloc(sizeof(t_redir));
	if (new == NULL)
		return (NULL);
	new->redir_type = type;
	new->filename = ft_strdup(filename);
	new->next = NULL;
	return (new);
}

void	add_redir_command(t_exec *current, t_redir *redir)
{
	t_redir *tmp;

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

// assigne le type de redir et file le filename dans la nod commande correspondante
int	redir_management(t_exec *current, t_list *token, int type)
{
	t_redir	*new_redir;

	new_redir = create_new_redir(token->next->content, type);
	if(new_redir == NULL)
		return(ERROR);
	add_redir_command(current, new_redir);
	return(0);
}
/**
 * @brief @param redir_management va creer la lsite chainee de redirection
 * @param create_new_redir va creer le node 
 * @param add_redir_command add back le node 
 */