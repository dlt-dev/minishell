/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lst2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 23:15:44 by aoesterl          #+#    #+#             */
/*   Updated: 2025/10/23 18:02:43 by aoesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static void switch_first_node(t_list **lst, t_list *curr_node, t_list *new_node)
{
    if(curr_node->next != NULL)
        new_node->next = curr_node->next;
    lst_del_one(curr_node);
    *lst = new_node;   
}

static void switch_last_node(t_list *curr_node, t_list *prev_node, t_list *new_node)
{
    prev_node->next = new_node;
    lst_del_one(curr_node);
}

static void switch_middle_node(t_list *curr_node, t_list *prev_node, t_list*new_node)
{
    prev_node->next = new_node;
    new_node->next = curr_node->next;
    lst_del_one(curr_node);
}

void node_exchange(t_list **lst, t_list *curr_node, t_list *prev_node, t_list *new_node)
{
    
    if(curr_node == NULL || *lst == NULL)
        return;
    if(*lst == curr_node)
        switch_first_node(lst, curr_node, new_node);
    else if(curr_node->next == NULL)
        switch_last_node(curr_node, prev_node, new_node);
    else 
        switch_middle_node(curr_node, prev_node, new_node);
}


void insert_after_node(t_list *curr_node, t_list* new_node)
{
	if(curr_node == NULL || new_node == NULL)
		return;
	if(curr_node->next == NULL)
		curr_node->next = new_node;
	else
	{
		new_node->next = curr_node->next;
		curr_node->next = new_node;	
	}
}

void del_one_relink(t_list **lst, t_list *curr_node, t_list* prev_node)
{
	if(*lst == NULL || curr_node == NULL)
		return;
	if(curr_node == *lst)
		*lst = curr_node->next;
	else if(prev_node->next != NULL)
		prev_node->next = curr_node->next;
	else
		return;
	lst_del_one(curr_node);
}