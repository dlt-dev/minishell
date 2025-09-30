/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 13:52:12 by aoesterl          #+#    #+#             */
/*   Updated: 2025/09/30 17:19:11 by aoesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*node;

	node = (t_list *)malloc(sizeof(t_list));
	if (node == NULL)
		return (NULL);
	node->content = content;
	node->next = NULL;
	return (node);
}
//GOODJOB

t_list	*ft_lstlast(t_list *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
	{
		lst = lst->next;
	}
	return (lst);
}
//GOODJOB

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (lst == NULL)
		return;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	last = ft_lstlast(*lst);
	last->next = new;
}
//GOODJOB

int fill_in_lst(t_list **lst, char *content)
{ 
	t_list *node;
	node = ft_lstnew(content);
	if(node == NULL)
		return(ERROR);
	ft_lstadd_back(lst, node);
	return(0);	
}
//GOODJOB

void print_str_lst(t_list *lst)
{ 
	if(lst == NULL)
		return;
	while(lst != NULL)
	{
		if(lst->content != NULL)
			write(1, lst->content, ft_strlen(lst->content));
		else
			write(1, "(null)", 6);
		write(1, "\n", 1);
		lst = lst->next;
	}
}
//GOODJOB

/**
 * @param print_str_lst print chaque element de la chaine;
 * @param fill_in_lst creer un node et le met en back de la liste
 * @param main pour tester si tu veux
 */
 
// int main()
// {
// 	t_list *lst;
// 	lst = NULL;
// 	char *a = "arthur";
// 	char *b = "oscar";
// 	char *c = "papa";
// 	char *d = NULL;
// 	fill_in_lst(&lst, a);
// 	fill_in_lst(&lst, b);
// 	fill_in_lst(&lst, c);
// 	fill_in_lst(&lst, d);
// 	printf_str_lst(lst);
// }