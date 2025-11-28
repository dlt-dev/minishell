/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Part4_expand_main_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelattr <jdelattr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 18:47:45 by jdelattr          #+#    #+#             */
/*   Updated: 2025/11/28 21:33:01 by jdelattr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_empty(t_list *curr_node)
{
	char	*content;
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	if (!curr_node)
		return (1);
	content = curr_node->content;
	if (!content)
		return (1);
	if (content[i] == '\0')
		return (1);
	while (content[i])
	{
		if (content[i] == ' ')
			count++;
		i++;
	}
	if (count == ft_strlen(content))
		return (1);
	return (0);
}

int	main_expand(t_shell *shell, t_list *lst_node)
{
	t_list	*curr_node;
	t_list	*prev_node;

	prev_node = NULL;
	curr_node = lst_node;
	if (curr_node == NULL)
		return (0);
	if (expand_shell_param(shell, shell->lst) == ERROR)
		return (ERROR);
	if (curr_node->next == NULL && curr_node->flag.dollar == DOLLAR)
	{
		shell->lst = NULL;
		return (0);
	}
	while (curr_node)
	{
		if (is_empty(curr_node) == 1)
			del_one_relink(&lst_node, curr_node, prev_node);
		else
			prev_node = curr_node;
		curr_node = curr_node->next;
	}
	shell->lst = lst_node;
	return (0);
}
