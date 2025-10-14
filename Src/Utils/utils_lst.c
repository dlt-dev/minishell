/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 13:52:12 by aoesterl          #+#    #+#             */
/*   Updated: 2025/10/14 18:17:18 by aoesterl         ###   ########.fr       */
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

int fill_in_lst(t_list **lst, char *content, int type)
{ 
	t_list *node;
	node = ft_lstnew(content);
	node->flag = (t_flag){0};
	node->flag.type = type;
	if(node == NULL)
		return(ERROR);
	ft_lstadd_back(lst, node);
	return(0);	
}
//GOODJOB

static void print_flag_lst(t_list *node)
{ 
	if(node == NULL)
		return;
	printf("type: %d\n", node->flag.type);
	printf("quote: %d\n", node->flag.quote);
	printf("dollar: %d\n", node->flag.dollar);
	printf("redir: %d\n", node->flag.redir);
	printf("pipe: %d\n", node->flag.pipe);
	printf("affec_var: %d\n", node->flag.affec_var);
	printf("error: %d\n\n", node->flag.error);
}

void print_str_lst(t_list *lst)
{ 
	if(lst == NULL)
		return;
	while(lst != NULL)
	{
		if(lst->content != NULL)
		{
			printf("NODE:\n%s\n", lst->content);
			print_flag_lst(lst);
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