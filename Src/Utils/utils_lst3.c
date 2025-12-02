/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lst3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 13:32:43 by jdelattr          #+#    #+#             */
/*   Updated: 2025/12/02 19:17:55 by aoesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	switch_first_node(t_list **lst, t_list *curr_node, t_list *new_node)
{
	if (curr_node->next != NULL)
		new_node->next = curr_node->next;
	*lst = new_node;
	lst_del_one(curr_node);
}

void	switch_last_node(t_list *curr_node, t_list *prev_node,
		t_list *new_node)
{
	prev_node->next = new_node;
	lst_del_one(curr_node);
}

void	switch_middle_node(t_list *curr_node, t_list *prev_node,
		t_list *new_node)
{
	prev_node->next = new_node;
	new_node->next = curr_node->next;
	lst_del_one(curr_node);
}

void	node_exchange(t_list **lst, t_list *curr_node, t_list *prev_node,
		t_list *new_node)
{
	if (curr_node == NULL || *lst == NULL)
		return ;
	if (*lst == curr_node)
		switch_first_node(lst, curr_node, new_node);
	else if (curr_node->next == NULL)
		switch_last_node(curr_node, prev_node, new_node);
	else
		switch_middle_node(curr_node, prev_node, new_node);
}