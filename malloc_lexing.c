/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_lexing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelattr <jdelattr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 14:22:03 by aoesterl          #+#    #+#             */
/*   Updated: 2025/10/01 19:07:01 by jdelattr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
// GOODJOB


/**
 * @brief 
 * @param ft_ft_strndup : malloc une chaine de caractere de 
 * longueur size;
 */