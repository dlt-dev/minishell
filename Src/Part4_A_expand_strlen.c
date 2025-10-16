/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Part4_A_expand_strlen.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 15:15:26 by aoesterl          #+#    #+#             */
/*   Updated: 2025/10/17 00:38:58 by aoesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int count_var(t_valist *var,  char *str, int len_name)
{
	int count;

	count = 0;
	if(var == NULL || str == NULL)
		return(0);
	while (var != NULL)
	{
		if (ft_strncmp(str, var->name, var->len_name) == 0)
			if(len_name == var->len_name)
			{
				count = ft_strlen(var->value);
				break;
			}
		var = var->next;
	}
	return(count);
}

int	lenght_var(t_valist *env, t_valist *local, char *str, int *i)
{
	int count;
	int len_name;

	count = 0;
	len_name = length_name(str);
	*i += len_name;
	if (len_name == 0)
		return (1);
	count += count_var(env, str, len_name);
	if(count == 0)
		count+= count_var(local, str, len_name);
	return (count);
}

int	length_single(char *str, int *i)
{
	int	j;

	j = 1;
	(*i)++;
	while (str[j] != '\0' && str[j] != '\'')
	{
		j++;
		(*i)++;
	}
	if(str[j] == '\'')
	{
		(*i)++;
		j++;		
	}
	return (j);
}

int	count_expansion(t_shell *shell, char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'')
			count += length_single(&str[i], &i);
		else if (str[i] == '$')
		{
			i++;
			if(str[i] == '?')
			{
				count += len_number(shell->exit_status);
				i++;
			}
			else
			count += length_var(shell->var.env, shell->var.local, &str[i], &i);
		}
		else
		{
			count++;
			i++;
		}
	}
	return (count);
}

int	expand_param(t_shell *shell, t_list *lst)
{
	int i;
	if (lst == NULL)
		return (ERROR);
	while (lst != NULL)
	{
		if (lst->flag.dollar == DOLLAR)
		{
			i = count_expansion(shell, lst->content);
			printf("node :\n%s\nsize du la chaine finale %d\n", lst->content,
				i);
			printf("taille de %s: %lu\n", getenv("USER"),
				strlen(getenv("USER")));
		}
		lst = lst->next;
	}
	return (0);
}
