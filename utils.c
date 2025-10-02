/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelattr <jdelattr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 13:51:58 by aoesterl          #+#    #+#             */
/*   Updated: 2025/10/01 19:16:30 by jdelattr         ###   ########.fr       */
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
//GOODJOB

char	*ft_strdup(char *s)
{
	size_t	lenght;
	char	*m;
	int		i;

	i = 0;
	lenght = ft_strlen(s);
	m = malloc(sizeof(char) * (lenght + 1));
	if (m == NULL)
		return (NULL);
	while (s[i])
	{
		m[i] = s[i];
		i++;
	}
	m[i] = '\0';
	return (m);
}

