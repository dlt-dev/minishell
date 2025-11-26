/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_va_lst2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelattr <jdelattr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 13:44:22 by jdelattr          #+#    #+#             */
/*   Updated: 2025/11/26 14:57:47 by jdelattr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_valist	*var_new(char *name, char *value)
{
	t_valist	*node;

	node = malloc(sizeof(t_valist));
	if (node == NULL)
		return (NULL);
	node->name = name;
	node->value = value;
	node->len_name = ft_strlen(node->name);
	node->next = NULL;
	return (node);
}

t_valist	*var_last(t_valist *var)
{
	if (var == NULL)
		return (NULL);
	while (var->next != NULL)
		var = var->next;
	return (var);
}
