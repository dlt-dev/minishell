/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_va_lst.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelattr <jdelattr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 19:10:04 by aoesterl          #+#    #+#             */
/*   Updated: 2025/11/26 13:45:08 by jdelattr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	var_addback(t_valist **var, t_valist *new)
{
	t_valist	*last;

	if (var == NULL)
		return ;
	if (*var == NULL)
	{
		*var = new;
		return ;
	}
	last = var_last(*var);
	last->next = new;
}

int	var_in_lst(t_valist **var, char *name, char *value)
{
	t_valist	*node;

	node = var_new(name, value);
	if (node == NULL)
		return (ERROR);
	var_addback(var, node);
	return (0);
}

void	ft_free_var(t_valist **var)
{
	t_valist	*tmp;

	if (var == NULL || *var == NULL)
		return ;
	tmp = *var;
	while (*var != NULL)
	{
		tmp = (*var)->next;
		free((*var)->name);
		free((*var)->value);
		free(*var);
		*var = tmp;
	}
}

void	lst_del_valist(t_valist *node)
{
	if (node == NULL)
		return ;
	if (node->name != NULL)
		free(node->name);
	if (node->value)
		free(node->value);
	free(node);
}

void	del_one_valist(t_valist **lst, t_valist *curr_node, t_valist *prev_node)
{
	if (*lst == NULL || curr_node == NULL)
		return ;
	if (curr_node == *lst)
		*lst = curr_node->next;
	else if (prev_node->next != NULL)
		prev_node->next = curr_node->next;
	else
		return ;
	lst_del_valist(curr_node);
}
