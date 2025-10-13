/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 13:52:12 by aoesterl          #+#    #+#             */
/*   Updated: 2025/10/13 23:56:18 by aoesterl         ###   ########.fr       */
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

static t_list	*ft_lstlast(t_list *lst)
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

int fill_in_lst(t_list **lst, char *content, int type, int flag_quote)
{ 
	t_list *node;
	node = ft_lstnew(content);
	node->type = type;
	node->quotes= flag_quote;
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
		{
			printf("NODE:\n%s\n", lst->content);
			printf("type: %d\nquotes: %d\n\n", lst->type, lst->quotes);
		}
		else
			write_str("(null)\n\n");
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

// 	char *a = ft_ft_strndup("arthur", 6);
// 	char *b = ft_ft_strndup("oscar", 5);
// 	char *c = ft_ft_strndup("papa",  4); 
// 	char *d = NULL;
// 	fill_in_lst(&lst, a);
// 	fill_in_lst(&lst, b);
// 	fill_in_lst(&lst, c);
// 	fill_in_lst(&lst, d);
// 	print_str_lst(lst);
// 	ft_free_lst(lst);
// }