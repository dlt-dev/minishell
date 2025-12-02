/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lst2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 23:15:44 by aoesterl          #+#    #+#             */
/*   Updated: 2025/12/02 19:01:38 by aoesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	insert_after_node(t_list *curr_node, t_list *new_node)
{
	if (curr_node == NULL || new_node == NULL)
		return ;
	if (curr_node->next == NULL)
		curr_node->next = new_node;
	else
	{
		new_node->next = curr_node->next;
		curr_node->next = new_node;
	}
}

void	del_one_relink(t_list **lst, t_list *curr_node, t_list *prev_node)
{
	if (!lst || !*lst || !curr_node)
		return ;
	if (curr_node == *lst)
		*lst = curr_node->next;
	else
		prev_node->next = curr_node->next;
	lst_del_one(curr_node);
}

int	insert_multi_node(t_list *curr_node, t_list *ins_lst)
{
	t_list	*tmp;
	int		i;

	tmp = ins_lst;
	if (curr_node == NULL || ins_lst == NULL)
		return (0);
	i = ft_lst_len(ins_lst);
	if (curr_node->next == NULL)
		curr_node->next = ins_lst;
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = curr_node->next;
		curr_node->next = ins_lst;
	}
	return (i);
}

int	ft_lst_len(t_list *lst)
{
	int	i;

	if (lst == NULL)
		return (0);
	i = 0;
	while (lst != NULL)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}
