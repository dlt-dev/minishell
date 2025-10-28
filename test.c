/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 15:40:27 by aoesterl          #+#    #+#             */
/*   Updated: 2025/10/28 18:11:47 by aoesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Header/minishell.h"
#include "unistd.h"
#include "stdio.h"
#include "stdlib.h"

// void insert_after_node(t_list *curr_node, t_list* new_node)
// {
// 	if(curr_node == NULL || new_node == NULL)
// 		return;
// 	if(curr_node->next == NULL)
// 		curr_node->next = new_node;
// 	else
// 	{
// 		new_node->next = curr_node->next;
// 		curr_node->next = new_node;	
// 	}
// }

// void del_one_relink(t_list **lst, t_list *curr_node, t_list* prev_node)
// {
// 	if(*lst == NULL || curr_node == NULL)
// 		return;
// 	if(curr_node == *lst)
// 		*lst = curr_node->next;
// 	else if(prev_node->next != NULL)
// 		prev_node->next = curr_node->next;
// 	else
// 		return;
// 	lst_del_one(curr_node);
// }

// int insert_multi_node(t_list *curr_node, t_list *ins_lst)
// {
//     t_list *tmp;
// 	int i;

// 	i = 0;
//     tmp = ins_lst;
//     if(curr_node == NULL || ins_lst == NULL)
//         return(0);
//     if(curr_node->next == NULL)
//         curr_node->next = ins_lst;
//     else
//     {
//         while(tmp->next != NULL)
// 		{
// 			tmp =tmp->next;
// 			i++;
// 		}
//         tmp->next = curr_node->next;
//         curr_node->next = ins_lst;
//     }
// 	return(i);
// }

// int ft_lst_len(t_list *lst)
// {
//     int  i;
//     if(lst == NULL)
//         return(0);
        
//     i = 0;
//     while(lst != NULL)
//     {
//         lst = lst->next;
//         i++;
//     }
//     return(i);
// }

int main()
{
    int i;

    i = 0;
	t_list *lst;
    t_list *lst2;
    t_list *tmp;
    t_list *tmp1;
	lst = NULL;
    lst2 = NULL;
	char *a = ft_strndup("arthur", 6);
	char *b = ft_strndup("oscar", 5);
	char *c = ft_strndup("papa",  4);
    char *d = ft_strndup("maman",  5);
    char *ok1 = ft_strndup("test1", 5);
	char *ok2 = ft_strndup("test2", 5);
	char *ok3 = ft_strndup("test3", 5);
	fill_in_lst(&lst, a, WORD);
	fill_in_lst(&lst, b, WORD);
	fill_in_lst(&lst, c, WORD);
    fill_in_lst(&lst, d, WORD);
    
    fill_in_lst(&lst2, ok1, WORD);
	fill_in_lst(&lst2, ok2, WORD);
	fill_in_lst(&lst2, ok3, WORD);
    lst = NULL;
    tmp = lst;
    while(i < 2)
    {
        tmp1 = tmp;
        tmp = tmp->next;
        i++;
    }
    printf("%d\n", ft_lst_len(lst2));
    insert_multi_node(tmp, lst2);
    del_one_relink(&lst, tmp, tmp1);
	// print_str_lst(lst);
	ft_free_lst(&lst);
}
