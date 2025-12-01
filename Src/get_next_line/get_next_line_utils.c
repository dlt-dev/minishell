/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 18:53:51 by aoesterl          #+#    #+#             */
/*   Updated: 2025/12/01 01:39:22 by aoesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*gnl_strdup(char *str)
{
	char	*p;
	size_t	i;

	i = 0;
	if (str == NULL)
		return (NULL);
	p = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (p == NULL)
		return (NULL);
	while (str[i] != '\0')
	{
		p[i] = str[i];
		i++;
	}
	p[i] = '\0';
	if (p[0] == '\0')
		return (free(p), NULL);
	return (p);
}

char	*strjoin(char *s1, char *s2)
{
	char	*p;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (s1 == NULL && s2 == NULL)
		return (NULL);
	if (s1 == NULL)
		return (gnl_strdup(s2));
	if (s2 == NULL)
		return (gnl_strdup(s1));
	p = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (p == NULL)
		return (NULL);
	while (s1[i])
	{
		p[i] = s1[i];
		i++;
	}
	while (s2[j])
		p[i++] = s2[j++];
	p[i] = '\0';
	return (p);
}

// int main ()
// {
// 	char *hu = "Arthur aime \n patates\n";
// 	char *heap;
// 	char *newline;
// 	int i = 0;

// 	newline = NULL;
// 	heap = malloc(sizeof(char) * (ft_strlen(hu) + 1));
// 	if (heap == NULL)
// 		return (0);
// 	while (hu[i])
// 	{
// 		heap[i] = hu[i];
// 		i++;
// 	}
// 	heap[i] = '\0';
// 	verifyheap(&heap, &newline);
// 	printf("%s\n", heap);
// 	printf("%s\n", newline);
// 	// char *a = strdup("Arthur");
// 	// printf("%s", a);
// 	// char *a = strjoin("Bonjour ","Arthur");
// 	// printf("%s", a);
// 	// char *a = cutnewline("Arthur\noscar\n");
// 	// printf("%s", a);
// 	free(heap);
// 	free(newline);
// 	return(0);
// }
