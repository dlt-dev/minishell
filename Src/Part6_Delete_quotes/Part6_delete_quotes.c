/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Part6_delete_quotes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelattr <jdelattr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 14:33:51 by aoesterl          #+#    #+#             */
/*   Updated: 2025/11/26 17:26:34 by jdelattr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	delete_quotes(t_shell *shell, t_list *lst)
{
	t_list	*new_node;
	t_list	*prev_node;
	int		check_failed;

	prev_node = NULL;
	if (lst == NULL)
		return (0);
	while (lst != NULL)
	{
		if (lst->flag.quote == QUOTE)
		{
			new_node = NULL;
			check_failed = chck_dlt_quotes(shell, &new_node, prev_node,
					lst);
			if (check_failed == SYNTAXE_ERR)
				return (free_all(shell), 0);
			if (check_failed == ERROR)
				return (ERROR);
			if (new_node != NULL)
				lst = new_node;
		}
		prev_node = lst;
		lst = lst->next;
	}
	return (0);
}
