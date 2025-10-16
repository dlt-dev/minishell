/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lenght.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 16:11:06 by aoesterl          #+#    #+#             */
/*   Updated: 2025/10/16 17:06:26 by aoesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	length_name(char *name)
{
	int	i;

	i = 0;
	if ((name[0] < 'A' || name[0] > 'Z') && (name[0] < 'a' || name[0] > 'z')
		&& (name[0] != '_'))
		return (0);
	while (name[i] != '\0')
	{
		if ((name[i] < '0' || name[i] > '9') && (name[i] < 'A' || name[i] > 'Z')
			&& (name[i] < 'a' || name[i] > 'z') && (name[i] != '_'))
			break ;
		i++;
	}
	return (i);
}