/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Part4_1expand_main.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 12:06:17 by aoesterl          #+#    #+#             */
/*   Updated: 2025/11/27 12:33:24 by aoesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_meanings(t_shell *shell, t_cb *lst_buffer, char *str)
{
	int	i;
	int	check_failed;

	i = 0;
	check_failed = 0;
	if (str[i] == '\'')
		check_failed = handle_single_quotes(lst_buffer, &str[i]);
	else if (str[i] == '\"')
		check_failed = handle_double_quotes(shell, lst_buffer, &str[i]);
	else if (str[i] == '$')
		check_failed = handle_dollar(shell, lst_buffer, &str[i]);
	if (check_failed == ERROR)
		return (ERROR);
	i += check_failed;
	return (i);
}

static int	fill_expand_in_buffer(t_shell *shell, t_cb *lst_buffer, char *str)
{
	int	i;
	int	check_failed;

	i = 0;
	while (str[i] != '\0')
	{
		check_failed = handle_meanings(shell, lst_buffer, &str[i]);
		if (check_failed == ERROR)
			return (ERROR);
		else if (check_failed == 0)
		{
			if (cb_append_char(lst_buffer, str[i]) == ERROR)
				return (ERROR);
			i++;
		}
		i += check_failed;
	}
	return (0);
}

char	*create_expand_str(t_shell *shell, char *str)
{
	char	*new_str;
	t_cb	lst_buffer;

	new_str = NULL;
	if (init_chunk_buffer(&lst_buffer, 10, 2) == ERROR)
		return (NULL);
	if (fill_expand_in_buffer(shell, &lst_buffer, str) == ERROR)
		return (NULL);
	new_str = fusion_all_chunk(&lst_buffer);
	free_chunk_buffer(&lst_buffer);
	if (new_str == NULL)
		return (NULL);
	return (new_str);
}

static t_list	*create_expand_node(t_shell *shell, t_list *curr_node)
{
	char	*new_str;
	t_list	*new_node;

	new_str = create_expand_str(shell, curr_node->content);
	if (new_str == NULL)
		return (NULL);
	new_node = ft_lstnew(new_str);
	if (new_node == NULL)
		return (free(new_str), NULL);
	ft_memcpy(&new_node->flag, &curr_node->flag, sizeof(t_flag));
	return (new_node);
}

int	expand_shell_param(t_shell *shell, t_list *curr_node)
{
	t_list	*new_node;
	t_list	*prev_node;

	prev_node = NULL;
	if (curr_node == NULL)
		return (0);
	while (curr_node != NULL)
	{
		if (curr_node->flag.dollar == DOLLAR)
		{
			if (curr_node->flag.word_type != DELIMITOR)
			{
				new_node = create_expand_node(shell, curr_node);
				if (new_node == NULL)
					return (ERROR);
				node_exchange(&shell->lst, curr_node, prev_node, new_node);
				curr_node = new_node;
			}
		}
		prev_node = curr_node;
		curr_node = curr_node->next;
	}
	return (0);
}
