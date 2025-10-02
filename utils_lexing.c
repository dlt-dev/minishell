/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lexing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelattr <jdelattr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 13:58:46 by aoesterl          #+#    #+#             */
/*   Updated: 2025/10/01 18:48:34 by jdelattr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_spaces(char c)
{  
	int i;
	char *sep;
	
	i = 0;
	sep = " \t\n\v\f\r";
	while(sep[i] != '\0') 
	{ 
		if(c == sep[i])
			return(IS);
		i++; 
	}
	return(IS_NOT);
}
//GOODJOB

int is_separator(char c)
{ 

	int i;
	char *sep;

	i = 0;
	sep = " \t\n\v\f\r<>$|\'\""; // quotes ?
	while (sep[i] != '\0')
	{
		if (c == sep[i])
			return (IS);
		i++;
	}
	return (IS_NOT);
}

int is_metachar(char c)
{ 

	int i;
	char *sep;

	i = 0;
	sep = "<>$|"; // quotes ?
	while (sep[i] != '\0')
	{
		if (c == sep[i])
			return (IS);
		i++;
	}
	return (IS_NOT);
}

int is_quote(char c)
{ 

	int i;
	char *sep;

	i = 0;
	sep = "\'\""; // quotes ?
	while (sep[i] != '\0')
	{
		if (c == sep[i])
			return (IS);
		i++;
	}
	return (IS_NOT);
}


/**
 * @brief 
 * @param is_spaces voir si un caractere est un "espace"
 * 
 */

 
// int main ()
// { 
// 	printf("%d\n", is_spaces('h'));
// 	printf("%d\n", is_spaces('\0')); 
// 	printf("%d\n", is_spaces('	'));
// 	printf("%d\n", is_spaces(' '));
// 	printf("%d\n", is_spaces('\v'));
// 	printf("%d\n", is_spaces('?'));
// }