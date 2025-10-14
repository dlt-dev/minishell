/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 15:40:27 by aoesterl          #+#    #+#             */
/*   Updated: 2025/10/14 18:43:26 by aoesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Header/minishell.h"
#include "unistd.h"
#include "stdio.h"
#include "stdlib.h"

// #define YELL_PS "\033[33;1m"
// #define BLUE_PS "\033[34;1m"



int check_close_quote(char *str)
{
	int i;
	char c;
	
	i = 0;
	c = 0;
	while(str[i] != '\0')
	{
		if(str[i] == '\'' || str[i] == '\"')
		{ 
			c = str[i];
			while(str[i] != '\0' && str[i] != c)
				i++;
			if(str[i] == '\0')
				return(ERROR);
		}
		i++;
	}
	return(0);
}

int main (int argc, char **argv)
{
	(void)argc;
	if(check_close_quote(argv[1]) == ERROR)
		return(printf("ERROR"),0);
	printf("Success"); 
}