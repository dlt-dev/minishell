/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_va_lst.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 19:10:04 by aoesterl          #+#    #+#             */
/*   Updated: 2025/10/15 19:43:08 by aoesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_valist *var_new(char *name, char *value)
{
	t_valist *node;

	node = malloc(sizeof(t_valist));
	if (node == NULL)
		return (NULL);
	node->name = name;
	node->value = value;
	node->next = NULL;
	return (node);
}

t_valist *var_last(t_valist *var)
{ 
	if(var == NULL)
		return(NULL);
	while(var->next != NULL)
		var = var->next;
	return(var);
}

void var_addback(t_valist **var, t_valist *new)
{ 
	t_valist *last;
	
	if(var == NULL)
		return;
	if(*var == NULL)
	{ 
		*var = new;
		return;
	}
	last = var_last(*var);
	last->next = new;	
}

int var_in_lst(t_valist **var, char *name, char *value)
{ 
	t_valist *node;
	node = var_new(name, value);
	if(node == NULL)
		return(ERROR);
	var_addback(var, node);
	return(0);
}