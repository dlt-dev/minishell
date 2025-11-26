/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Part6_delete_quotes_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelattr <jdelattr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 16:47:12 by jdelattr          #+#    #+#             */
/*   Updated: 2025/11/25 20:40:33 by jdelattr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	checker_close_quotes(char *str)
{
	int		i;
	char	flag_quotes;

	flag_quotes = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\"' || str[i] == '\'')
		{
			flag_quotes = str[i];
			i++;
			while (str[i] != flag_quotes && str[i] != '\0')
				i++;
			if (str[i] == flag_quotes)
			{
				i++;
				flag_quotes = 0;
			}
		}
		else
			i++;
	}
	if (flag_quotes == '\'' || flag_quotes == '\"')
		return (ERROR);
	return (0);
}

// On espere que la refactorisation n'a pas tout foire...
int	buffer_delete_quotes(t_cb *lst_buffer, char *str)
{
	int		i;
	char	flag_quotes;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\"' || str[i] == '\'')
		{
			flag_quotes = str[i++];
			while (str[i] != flag_quotes && str[i] != '\0')
			{
				if (cb_append_char(lst_buffer, str[i++]) == ERROR)
					return (ERROR);
			}
			if (str[i] == flag_quotes)
				i++;
		}
		else if (cb_append_char(lst_buffer, str[i++]) == ERROR)
			return (ERROR);
	}
	return (0);
}

// Ancienne qui fonctionne mais longue
// int	buffer_delete_quotes(t_cb *lst_buffer, char *str)
// {
// 	int		i;
// 	char	flag_quotes;

// 	i = 0;
// 	while (str[i] != '\0')
// 	{
// 		if (str[i] == '\"' || str[i] == '\'')
// 		{
// 			flag_quotes = str[i++];
// 			while (str[i] != flag_quotes && str[i] != '\0')
// 			{
// 				if (cb_append_char(lst_buffer, str[i]) == ERROR)
// 					return (ERROR);
// 				i++;
// 			}
// 			if (str[i] == flag_quotes)
// 				i++;
// 		}
// 		else
// 		{
// 			if (cb_append_char(lst_buffer, str[i]) == ERROR)
// 				return (ERROR);
// 			i++;
// 		}
// 	}
// 	return (0);
// }

char	*delete_quotes_str(t_list *node)
{
	char	*new_str;
	t_cb	lst_buffer;

	new_str = NULL;
	if (init_chunk_buffer(&lst_buffer, 10, 2) == ERROR)
		return (NULL);
	if (buffer_delete_quotes(&lst_buffer, node->content) == ERROR)
		return (free_chunk_buffer(&lst_buffer), NULL);
	new_str = fusion_all_chunk(&lst_buffer);
	if (new_str == NULL)
		return (NULL);
	return (new_str);
}

t_list	*delete_quotes_node(t_list *node)
{
	char	*new_str;
	t_list	*new_node;

	new_str = delete_quotes_str(node);
	if (new_str == NULL)
		return (NULL);
	new_node = ft_lstnew(new_str);
	if (new_node == NULL)
		return (free(new_str), NULL);
	ft_memcpy(&new_node->flag, &node->flag, sizeof(t_flag));
	return (new_node);
}

int	chck_dlt_quotes(t_shell *shell, t_list **new_n, t_list *prev_n, t_list *lst)
{
	if (checker_close_quotes(lst->content) == ERROR)
	{
		printf(GREEN "OUUPS, les quotes étaient ouvertes," RESET);
		printf(GREEN " j'ai tout free.\n" RESET);
		return (free_all(shell), SYNTAXE_ERR);
	}
	if (lst->flag.word_type != DELIMITOR)
	{
		*new_n = delete_quotes_node(lst);
		if (new_n == NULL)
			return (ERROR);
		node_exchange(&shell->lst, lst, prev_n, *new_n);
	}
	return (0);
}
