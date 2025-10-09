/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lexing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 13:58:46 by aoesterl          #+#    #+#             */
/*   Updated: 2025/10/09 11:57:34 by aoesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_str(char c, char *sep)
{ 
	int i;
	
	i = 0;
	while(sep[i] != '\0') 
	{ 
		if(c == sep[i])
			return(IS);
		i++; 
	}
	return(IS_NOT);
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

/**
 * @brief 
 * @param ft_ft_strndup : malloc une chaine de caractere de 
 * longueur size;
 * @param is_str: regarde si le caractere fais partie de la chaine envoyer
 * en parametre de la fonction is_str
 */