/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Part6_delete_quotes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 14:33:51 by aoesterl          #+#    #+#             */
/*   Updated: 2025/10/31 16:59:57 by aoesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"





int buffer_delete_quotes(t_cb lst_buffer, char *str)
{ 
	int i;
	char flag_quotes;

	flag_quotes = 0;
	i = 0;
	while(str[i] != '\0')
	{ 
		if(str[i] == "\"" || str[i] == '\'')
		{ 
			flag_quotes = str[i];
			i++;
			while(str[i] != flag_quotes && str[i] != '\0')
			{ 
				if(cb_append_char(&lst_buffer, str[i]) == ERROR)
					return(ERROR);
				i++;
			}
			if(str[i] == flag_quotes)
				i++;
		} 
		else
			if(cb_append_char(&lst_buffer, str[i]) == ERROR)
				return(ERROR);
	}
	return(0);
}

char *delete_quotes_str(t_list *node)
{
	char *new_str;
	t_cb lst_buffer;
	
	new_str = NULL;
	if(init_chunk_buffer(&lst_buffer, 10, 2) == ERROR)
		return(NULL);
	if(buffer_delete_quotes(lst_buffer, node->content) == ERROR)
		return(free_chunk_buffer(&lst_buffer), NULL);
	new_str = fusion_all_chunk(&lst_buffer);
	if(new_str == NULL)
		return(NULL);
	return(new_str);
}

t_list *delete_quotes_node(t_list *node)
{ 
	char *new_str;
	t_list *new_node;
	
	new_str = delete_quotes_str(node);
	if(new_str == NULL)
		return(NULL);
	new_node = ft_lst_new(new_str);
	if(new_node == NULL)
		return(free(new_str), NULL);
	ft_memcpy(&new_node->flag, &node->flag, sizeof(t_flag));
	return(new_node);
}

int delete_quotes(t_shell *shell, t_list *lst)
{
	t_list *new_node;
	t_list *prev_node;
	
	prev_node = NULL;
	if(lst == NULL)
		return(0);
		
	while(lst != NULL)
	{
		if(lst->flag.quote == QUOTE && lst->flag.word_type != DELIMITOR)
		{ 
			tmp = delete_quotes_node(lst);
			if(tmp == NULL)
				return(ERROR);
			node_exchange(&shell->lst, curr_node, prev_node, tmp )

		}
		lst = lst->next;	
	}
}