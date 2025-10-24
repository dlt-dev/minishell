/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Part4_3expand_dollar.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 14:32:11 by aoesterl          #+#    #+#             */
/*   Updated: 2025/10/21 16:39:37 by aoesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int find_shell_var(t_valist *var, t_cb* lst_buffer, char *str, int len_name)
{
	if(var == NULL)
		return(IS_NOT);
	while (var != NULL)
	{
		if (ft_strncmp(str, var->name, var->len_name) == 0)
        {
			if(len_name == var->len_name)
			{
				if(cb_append_str(lst_buffer, var->value) == ERROR)
                    return(ERROR);
				return(IS);
			}
        }
		var = var->next;
	}
	return(IS_NOT);
}

static int expand_env_or_local(t_shell *shell, t_cb* lst_buffer, int len_name, char *str)
{
	int check_failed;
	
	check_failed = find_shell_var(shell->var.env, lst_buffer, str, len_name);
    if(check_failed == ERROR)
        return(ERROR);
	else if(check_failed == IS_NOT)
	{ 
		check_failed = find_shell_var(shell->var.local, lst_buffer, str, len_name);
		if(check_failed == ERROR)
			return(ERROR);
	}
	return(0);
}

static int	expand_var(t_shell *shell, t_cb* lst_buffer, char *str)
{
	int i;
	int len_name;
	
	i = 0;
	len_name = length_name(str);
	i += len_name;
	if (len_name == 0)
	{ 
		if(cb_append_char(lst_buffer, '$') == ERROR)
			return(ERROR);
		return(i);
	}
	if(expand_env_or_local(shell, lst_buffer, len_name, str) == ERROR)
		return(ERROR);
	return (i);
}

int handle_dollar(t_shell* shell, t_cb* lst_buffer, char *str)
{
    int i;
	int check_failed;
	
    i = 0;
	i++;
	if(str[i] == '?')
	{
		i++;
		// count += len_number(shell->exit_status); //
	}
	check_failed = expand_var(shell, lst_buffer, &str[i]);
	if(check_failed == ERROR)
		return(ERROR);
	i += check_failed;
	return(i);
}

/**
 * @brief @param expand_var
 * 
 * 3 cas sont a distinguer dans le cas d'une expansion de variable:
 * - Si le $ est suivi d'un nom de variable qui n'existe pas (ex : $prout).
 * le $prout disparait dans la nouvelle chaine et il n'y a pas de caractere en plus.
 * Donc pas d'append_char;
 * - Si le $ est directement suivi d'un caractere qui n'est pas admis dans un "name",
 * le $ est considere comme tout seul et ne fait pas d'expansion. on garde donc le $,
 * Donc append_char = '$';
 * - Si le nom de variable est valide, le $name est remplace par sa valeur.
 * Donc append_str = value de la variable (name=value).
 * 
 * @return int 
 */