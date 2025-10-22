/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 15:40:27 by aoesterl          #+#    #+#             */
/*   Updated: 2025/10/22 18:31:23 by aoesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Header/minishell.h"
#include "unistd.h"
#include "stdio.h"
#include "stdlib.h"


void add_new_node(t_list *curr_node, t_list* new_node)
{
	if(curr_node == NULL || new_node == NULL)
		return;
	if(curr_node->next == NULL)
		curr_node->next = new_node;
	new_node->next = curr_node->next;
	curr_node->next = new_node;	
}

void del_one_relink(t_list **lst, t_list *curr_node, t_list* prev_node)
{
	if(*lst == NULL || curr_node == NULL)
		return;
	if(curr_node == *lst)
	{
		if(curr_node->next != NULL)
			*lst = curr_node->next;
		lst_del_one(curr_node);
	}
	else if(curr)
	
}


// int main()
// {
// 	char **str;
// 	int i;
// 	char *p = "abc def ghi \'arthur  oscar\' def";
// 	int size = count_word_handle_quotes(p);
	
// 	i = 0;
// 	str = word_splitting(p, size);
// 	while(str[i] != NULL)
// 	{
// 		printf("chaine : %s\n\n", str[i]);
// 		i++;
// 	}
// }