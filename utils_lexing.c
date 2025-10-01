/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lexing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 13:58:46 by aoesterl          #+#    #+#             */
/*   Updated: 2025/09/30 17:15:54 by aoesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_separator (char c)
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


/**
 * @brief 
 * @param is_separator voir si un caractere est un "espace"
 * 
 */

 
// int main ()
// { 
// 	printf("%d\n", is_separator('h'));
// 	printf("%d\n", is_separator('\0')); 
// 	printf("%d\n", is_separator('	'));
// 	printf("%d\n", is_separator(' '));
// 	printf("%d\n", is_separator('\v'));
// 	printf("%d\n", is_separator('?'));
// }