/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 15:40:27 by aoesterl          #+#    #+#             */
/*   Updated: 2025/10/22 19:34:27 by aoesterl         ###   ########.fr       */
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
	else
		prev_node->next = curr_node->next;
	lst_del_one(curr_node);
}

int main()
{
	int i;
	t_list *prev;
	t_list *lst;
	t_list *tmp;

	i = 0;
	lst = NULL;
	prev = NULL;
	
	char *a = ft_strndup("arthur", 6);
	char *b = ft_strndup("oscar", 5);
	char *c = ft_strndup("papa",  4);
	char *d = ft_strndup("joelle",  4);
	char *e = ft_strndup("dieu",  4);
	t_list *new = ft_lstnew(ft_strndup("michel", 6));
	fill_in_lst(&lst, a, 0);
	fill_in_lst(&lst, b, 0);
	fill_in_lst(&lst, c, 0);
	fill_in_lst(&lst, d, 0);
	fill_in_lst(&lst, e, 0);
	tmp = lst;
	while(i < 2)
	{
		prev = tmp;
		tmp = tmp->next;
		i++;
	}
	add_new_node(tmp, new);
	del_one_relink(&lst, tmp, prev);
	print_str_lst(lst);
	ft_free_lst(&lst);
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