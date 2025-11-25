/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Part4_2expand_quotes.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelattr <jdelattr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 14:56:01 by aoesterl          #+#    #+#             */
/*   Updated: 2025/11/25 16:35:59 by jdelattr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_single_quotes(t_cb *lst_buffer, char *str)
{
	int	i;

	i = 0;
	if (cb_append_char(lst_buffer, str[i]) == ERROR)
		return (ERROR);
	i++;
	while (str[i] != '\0' && str[i] != '\'')
	{
		if (cb_append_char(lst_buffer, str[i]) == ERROR)
			return (ERROR);
		i++;
	}
	if (str[i] == '\'')
	{
		if (cb_append_char(lst_buffer, str[i]))
			return (ERROR);
		i++;
	}
	return (i);
}

int	in_double_quotes(t_shell *shell, t_cb *lst_buffer, char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && str[i] != '\"')
	{
		if (str[i] == '$')
			i += handle_dollar(shell, lst_buffer, &str[i]);
		else
		{
			if (cb_append_char(lst_buffer, str[i]) == ERROR)
				return (ERROR);
			i++;
		}
	}
	return (i);
}

int	handle_double_quotes(t_shell *shell, t_cb *lst_buffer, char *str)
{
	int	i;
	int	check_failed;

	i = 0;
	if (cb_append_char(lst_buffer, str[i]) == ERROR)
		return (ERROR);
	i++;
	check_failed = in_double_quotes(shell, lst_buffer, &str[i]);
	if (check_failed == ERROR)
		return (ERROR);
	i += check_failed;
	if (str[i] == '\"')
	{
		if (cb_append_char(lst_buffer, str[i]) == ERROR)
			return (ERROR);
		i++;
	}
	return (i);
}
