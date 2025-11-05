/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_libft1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 13:51:58 by aoesterl          #+#    #+#             */
/*   Updated: 2025/11/05 18:20:27 by aoesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char *ft_strndup(char *str, int size)
{
	int i;
	char *p;
	
	i = 0;
	if(str == NULL)
		return(NULL);
	p = malloc(sizeof(char) * size + 1);
	if( p == NULL)
		return(NULL);
	while(i < size)
	{ 
		p[i] = str[i];
		i++;
	}
	p[i] = '\0';
	return(p);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] != '\0' && s1[i] == s2[i] && i < n - 1)
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] != '\0' && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void ft_strcat(char *src, char *dest)
{
	int i;
	int j;
	if(src == NULL || dest == NULL)
		return;
	j = 0; 
	i = 0;
	while(dest[i] != '\0')
		i++;
	while(src[j] != '\0')
	{ 
		dest[i] = src[j];
		j++;
		i++; 
	}
	dest[i] = '\0';
}