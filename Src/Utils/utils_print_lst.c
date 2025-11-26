/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_print_lst.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelattr <jdelattr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 16:26:50 by aoesterl          #+#    #+#             */
/*   Updated: 2025/11/26 13:38:17 by jdelattr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_var_lst(t_valist *var)
{
	if (var == NULL)
		return ;
	while (var != NULL)
	{
		if (var->name != NULL && var->value != NULL)
		{
			printf("NODE\n");
			printf("VAR NAME: %s\n", var->name);
			printf("VAR LENGHT: %d\n", var->len_name);
			printf("VAR VALUE: %s\n\n", var->value);
		}
		else
			write_str("(null)\n\n");
		var = var->next;
	}
}

static void	print_flag_lst(t_list *node)
{
	if (node == NULL)
		return ;
	printf("type: %d\n", node->flag.type);
	printf("quote: %d\n", node->flag.quote);
	printf("dollar: %d\n", node->flag.dollar);
	printf("pipe: %d\n", node->flag.pipe);
	printf("redir: %d\n", node->flag.redir);
	printf("redir_type: %d\n", node->flag.redir_type);
	printf("word_type: %d\n\n", node->flag.word_type);
}

void	print_str_lst(t_list *lst)
{
	if (lst == NULL)
		return ;
	while (lst != NULL)
	{
		if (lst->content != NULL)
		{
			printf("NODE:\n%s\n", lst->content);
			print_flag_lst(lst);
		}
		else
			write_str("(null)\n\n");
		lst = lst->next;
	}
}

void	printf_buffer(t_cb lst_buffer)
{
	if (lst_buffer.head == NULL || lst_buffer.tail == NULL)
		write_str("buffer nill");
	while (lst_buffer.head != NULL)
	{
		printf("NODE:\n");
		printf("str: %s\n", lst_buffer.head->buffer);
		printf("length: %lu\n", lst_buffer.head->length);
		printf("capacity: %lu\n\n", lst_buffer.head->capacity);
		lst_buffer.head = lst_buffer.head->next;
	}
}
