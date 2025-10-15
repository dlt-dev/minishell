/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_va_lst.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 19:10:04 by aoesterl          #+#    #+#             */
/*   Updated: 2025/10/16 00:26:02 by aoesterl         ###   ########.fr       */
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

void ft_free_var(t_valist **var)
{
	t_valist *tmp;
	if(var == NULL || *var == NULL)
		return;
	tmp = *var;
	while(*var != NULL)
	{
		tmp = (*var)->next;
		free((*var)->name);
		free((*var)->value);
		free(*var);
		*var = tmp;
	}
}

void print_var_lst(t_valist *var)
{ 
	if(var == NULL)
		return;
	while(var != NULL)
	{
		if(var->name != NULL && var->value != NULL)
		{
			printf("NODE\n");
			printf("VAR NAME: %s\n", var->name);
			printf("VAR VALUE: %s\n\n", var->value);
		}
		else
			write_str("(null)\n\n");
			
		var = var->next;
	}
}