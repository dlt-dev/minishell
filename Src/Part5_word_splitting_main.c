/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Part5_word_splitting_main.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 18:24:23 by aoesterl          #+#    #+#             */
/*   Updated: 2025/10/27 19:37:31 by aoesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list *split_in_lst(char **tab, t_list *curr_node)
{
	t_list *lst;
	t_list *tmp;
	int i;

	i = 0;
	lst = NULL;
	while(tab[i] != NULL)
	{
		tmp = ft_lstnew(tab[i]);
		if(tmp == NULL)
			return(ft_free_lst(&lst), NULL);
		memcpy(&tmp->flag, &curr_node->flag, sizeof(t_flag));
		ft_lstadd_back(&lst, tmp);
		i++;
	}
	return(lst);
}

int lst_splitted(t_list *curr_node, t_list **ins_lst)
{
	int count_word;
	char **tab;

	count_word = count_word_hdle_quotes(curr_node->content);
	if(count_word > 1)
	{
		tab = word_splitting(curr_node->content, count_word);
		if(tab == NULL)
			return(ERROR);
		*ins_lst = split_in_lst(tab, curr_node);
		if(ins_lst == NULL)
			return(ft_free_split(&tab), ERROR);
		return(CONTINUE);
	}
	return(0);
}

void jump_insert_lst(t_shell *shell, t_list **curr_node, t_list **prev_node, t_list *ins_lst)
{
	int i;
	
	i = insert_multi_node(*curr_node, ins_lst);
	del_one_relink(&shell->lst, *curr_node, *prev_node);
	*curr_node = ins_lst;
	while(i > 0)
	{
		*prev_node = *curr_node;
		*curr_node = (*curr_node)->next; 
		i--;
	}

}

int split_param(t_shell *shell, t_list *curr_node, t_list *prev_node)
{
	t_list *ins_lst;
	int step;
	
	ins_lst = NULL;
	if(curr_node == NULL)
		return(0);
	while(curr_node != NULL)
	{
		if(curr_node->flag.cmd == CMD)
		{
			step = lst_splitted(curr_node, &ins_lst);
			if(step == ERROR)
				return(ERROR);
			else if(step == CONTINUE)
				jump_insert_lst(shell, &curr_node, &prev_node, ins_lst);
			else
			{
				prev_node = curr_node;
				curr_node = curr_node->next;
			}
		}
		else
		{
			prev_node = curr_node;
			curr_node = curr_node->next;
			
		}
	}
	return(0);	
}
