/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelattr <jdelattr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 14:16:57 by jdelattr          #+#    #+#             */
/*   Updated: 2025/11/14 16:46:28 by jdelattr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_putstr(char *s)
{
	write(1, s, ft_strlen(s));
}

char	*ft_strcpy(char *dst, const char *src)
{
	size_t	i;

	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	maxlen;
	size_t	sublen;
	char	*sub;

	if (!s)
		return (NULL);
	maxlen = ft_strlen(s);
	if (start >= maxlen)
		return (ft_strdup(""));
	if (start + len > maxlen)
		sublen = maxlen - start;
	else
		sublen = len;
	sub = malloc(sizeof(char) * (sublen + 1));
	if (sub == NULL)
		return (NULL);
	ft_memcpy(sub, s + start, sublen);
	sub[sublen] = '\0';
	return (sub);
}
