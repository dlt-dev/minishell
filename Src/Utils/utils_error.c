/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 19:01:40 by aoesterl          #+#    #+#             */
/*   Updated: 2025/11/26 18:06:59 by aoesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error_message(char *fonction, char *arg)
{
	char	*error;
	char	*minishell;

	minishell = "minishell: ";
	error = strerror(errno);
	write(2, minishell, ft_strlen(minishell));
	if (fonction != NULL)
	{
		write(2, fonction, ft_strlen(fonction));
		write(2, ": ", 2);
	}
	if (arg != NULL)
	{
		write(2, arg, ft_strlen(arg));
		write(2, ": ", 2);
	}
	write(2, error, ft_strlen(error));
	write(2, "\n", 1);
}
