/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_export2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 17:06:38 by aoesterl          #+#    #+#             */
/*   Updated: 2025/11/10 18:23:18 by aoesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_a_valid_name(char* str)
{
	int i;
	int flag_name;
	
	flag_name = 0;
	i = 0;
	if ((str[0] < 'A' || str[0] > 'Z') && (str[0] < 'a' || str[0] > 'z')
		&& (str[0] != '_'))
		flag_name = 1;
	while(str[i] != '=' && str[i] != '\0')
	{
		if ((str[i] < '0' || str[i] > '9') && (str[i] < 'A' || str[i] > 'Z')
			&& (str[i] < 'a' || str[i] > 'z') && (str[i] != '_'))
			flag_name = 1;
		i++;
	}
	if(flag_name == 1)
		return(ERROR);
	return(0);
}

int is_an_affectation(char *str, int *len_name)
{ 
	int i;

	*len_name = length_name(str);
	i = 0;
	if(is_a_valid_name(str) == ERROR) // not a valid identifier
	{ 
		printf("minishell: export: \'%s\': not a valid identifier\n", str);
		return(ERROR);
	}
	while(i < *len_name)
		i++;
	if(str[i] == '=')
		return(IS); // est une affectation;
	return(IS_NOT); // n'est pas une affecation;
}
